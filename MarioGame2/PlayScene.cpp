#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Tile.h"
#include "QuestionBrick.h"
#include "CoinItem.h"
#include "RedMushroomItem.h"
#include "GreenMushroomItem.h"
#include "LeafItem.h"
#include "ColorBox.h"
#include "RedFirePlant.h"
#include "GreenFirePlant.h"
#include "GreenPlant.h"
#include "FireBall.h"
#include "Score.h"
#include "RedKoopa.h"

#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < (int)tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y, OBJECT_TYPE_MARIO);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y, OBJECT_TYPE_GOOMBA); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(x, y, OBJECT_TYPE_BRICK); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y, OBJECT_TYPE_COIN); break;
	case OBJECT_TYPE_RED_FIRE_PLANT: obj = new CRedFirePlant(x, y, OBJECT_TYPE_RED_FIRE_PLANT); break;
	case OBJECT_TYPE_GREEN_FIRE_PLANT: obj = new CGreenFirePlant(x, y, OBJECT_TYPE_GREEN_FIRE_PLANT); break;
	case OBJECT_TYPE_GREEN_PLANT: obj = new CGreenPlant(x, y, OBJECT_TYPE_GREEN_PLANT); break;	 
	case OBJECT_TYPE_RED_KOOPA: obj = new CRedKoopa(x, y, OBJECT_TYPE_RED_KOOPA); break;
	case OBJECT_TYPE_QUESTION_BRICK:
	{
		int item_type = atoi(tokens[3].c_str());

		obj = new CQuestionBrick(x, y, OBJECT_TYPE_QUESTION_BRICK, item_type);

		switch (item_type) {
		case ITEM_TYPE_COIN:
			obj->SetSubObj(new CCoinItem(x, y, OBJECT_TYPE_ITEM, item_type));
			break;
		case ITEM_TYPE_RED_MUSHROOM:
			obj->SetSubObj(new CRedMushroomItem(x, y, OBJECT_TYPE_ITEM, item_type));
			break;
		case ITEM_TYPE_GREEN_MUSHROOM:
			obj->SetSubObj(new CGreenMushroomItem(x, y, OBJECT_TYPE_ITEM, item_type));
			break;
		case ITEM_TYPE_LEAF:
			obj->SetSubObj(new CLeafItem(x, y, OBJECT_TYPE_ITEM, item_type));
			break;
		case ITEM_TYPE_RED_MUSHROOM_LEAF:
			obj->SetSubObj(new CRedMushroomItem(x, y, OBJECT_TYPE_ITEM, item_type));
			obj->SetSubObj2(new CLeafItem(x, y, OBJECT_TYPE_ITEM, item_type));
			break;
		}

		break; 
	}
	case OBJECT_TYPE_COLOR_BOX: 
	{
		int sprite_id = atoi(tokens[3].c_str());

		obj = new CColorBox(x, y, OBJECT_TYPE_COLOR_BOX, sprite_id);

		break;
	}

	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y, OBJECT_TYPE_PLATFORM,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_TILE: 
	{
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CTile(
			x, y, OBJECT_TYPE_TILE,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(OBJECT_TYPE_PORTAL, x, y, r, b, scene_id);
	}
	break;


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	if (obj != NULL) {
		if (obj->GetSubObj() != NULL) {
			obj->GetSubObj()->SetPosition(x, y);
			objects.push_back(obj->GetSubObj());
		}

		if (obj->GetSubObj2() != NULL) {
			obj->GetSubObj2()->SetPosition(x, y);
			objects.push_back(obj->GetSubObj2());
		}

		obj->SetPosition(x, y);
		objects.push_back(obj);
	}
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	SetPlayerToObjects();
	SetObjectsToObjects();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < (int)objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < (int)objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;

	if (cx <= 0) cx = 0;
	else if (cx >= RIGHT_EDGE - SCREEN_WIDTH) cx = RIGHT_EDGE - SCREEN_WIDTH;

	if (cy <= TOP_EDGE + Y_OFFSET) cy = TOP_EDGE;
	else if (cy > TOP_EDGE && cy < CAM_Y_MIDDLE) cy -= Y_OFFSET;
	else cy = CAM_Y_IDLE;
	

	CGame::GetInstance()->SetCamPos(cx, cy /*cy*/);

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (int i = 0; i < (int)objects.size(); i++)
		objects[i]->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < (int)objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

void CPlayScene::SetPlayerToObjects() {
	for (LPGAMEOBJECT obj : objects) {
		if (obj == NULL) continue;

		if (obj->GetObjectType() == OBJECT_TYPE_COLOR_BOX) {
			CColorBox* cb = dynamic_cast<CColorBox*>(obj);
			cb->SetPlayer(this->player);
		}
		else if (obj->GetObjectType() == OBJECT_TYPE_RED_FIRE_PLANT) {
			CRedFirePlant* rfp = dynamic_cast<CRedFirePlant*>(obj);
			rfp->SetPlayer(this->player);
		}
		else if (obj->GetObjectType() == OBJECT_TYPE_GREEN_FIRE_PLANT) {
			CGreenFirePlant* gfp = dynamic_cast<CGreenFirePlant*>(obj);
			gfp->SetPlayer(this->player);
		}
	}
}

void CPlayScene::SetObjectsToObjects() {
	for (LPGAMEOBJECT obj : objects) {
		if (obj == NULL) continue;

		if (obj->GetObjectType() == OBJECT_TYPE_COLOR_BOX) {
			CColorBox* cb = dynamic_cast<CColorBox*>(obj);
			for (LPGAMEOBJECT obj2 : objects) {
				if (obj2->GetObjectType() == OBJECT_TYPE_ITEM && dynamic_cast<CRedMushroomItem*>(obj2)) {
					CRedMushroomItem* rmi = dynamic_cast<CRedMushroomItem*>(obj2);
					cb->setRedMushroomItem(rmi);				
				}
				else if (obj2->GetObjectType() == OBJECT_TYPE_RED_KOOPA) {
					CRedKoopa* redKoopa = dynamic_cast<CRedKoopa*>(obj2);
					cb->SetRedKoopa(redKoopa);
				}
			}
		}
	}
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}