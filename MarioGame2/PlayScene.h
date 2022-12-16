#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
//#include "Koopas.h"

#define SCREEN_WIDTH 288
#define SCREEN_HEIGHT 272

#define LEFT_EDGE 0
#define RIGHT_EDGE 2800
#define TOP_EDGE -240
#define LEFT_PUSH 1

#define CAM_Y_MIDDLE 48
#define CAM_Y_IDLE 0

#define Y_OFFSET 48

class CPlayScene : public CScene
{
protected:
	// A play scene has to have player, right? 
	CMario* player;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	virtual void SetPlayerToObjects();
	virtual void SetObjectsToObjects();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

