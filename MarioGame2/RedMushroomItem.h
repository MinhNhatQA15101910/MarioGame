#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Score.h"
#include "AssetIDs.h"

#define RED_MUSHROOM_ITEM_WITDH 16
#define RED_MUSHROOM_ITEM_HEIGHT 16

#define RED_MUSHROOM_ITEM_BBOX_WIDTH 16
#define RED_MUSHROOM_ITEM_BBOX_HEIGHT 12

#define RED_MUSHROOM_ITEM_GRAVITY 0.001f

#define RED_MUSHROOM_ITEM_POP_UP_SPEED 0.03f
#define RED_MUSHROOM_ITEM_RUN_SPEED 0.06f

#define RED_MUSHROOM_ITEM_STATE_IDLE 20
#define RED_MUSHROOM_ITEM_STATE_POP_UP 21
#define RED_MUSHROOM_ITEM_STATE_RUNNING 22
#define RED_MUSHROOM_ITEM_STATE_DISAPPEAR 23

#define ID_ANI_ITEM_RED_MUSHROOM 290000

class CRedMushroomItem : public CGameObject {
	CScore* score;
	
	float ax;
	float ay;

	float startX, startY;

	int itemType;

public:
	CRedMushroomItem() {
		this->score = new CScore();

		itemType = 0;
		this->startX = this->startY = 0.0f;
		ax = 0.0f;
		ay = 0.0f;
	}

	CRedMushroomItem(float x, float y, int object_type, int item_type) : CGameObject(x, y, object_type) {
		this->score = new CScore(x, y, OBJECT_TYPE_SCORE, 1000);
		
		this->itemType = item_type;
		this->startX = x;
		this->startY = y;
		ax = 0.0f;
		ay = 0.0f;
		SetState(RED_MUSHROOM_ITEM_STATE_IDLE);
	}
	
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	CScore* GetScore() { return this->score; }
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetState(int state);
};

