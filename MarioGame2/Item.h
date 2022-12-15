#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ITEM_WIDTH 10
#define ITEM_HEIGHT 16
#define ITEM_BBOX_WIDTH 10
#define ITEM_BBOX_HEIGHT 16

#define ITEM_TYPE_COIN 1

#define COIN_JUMP_SPEED_Y 0.5f

#define GRAVITY 0.002f

#define COIN_STATE_IDLE 10
#define COIN_STATE_JUMP 11

#define ID_ANI_ITEM_COIN 270000

class CItem : public CGameObject {
	float ax;
	float ay;

	float startX, startY;

	int itemType;

	bool coinJump;

public:
	CItem() { 
		itemType = 0; 
		this->startX = this->startY = 0.0f;
		ax = 0.0f;
		ay = 0.0f;
		this->coinJump = false;
	}
	CItem(float x, float y, int object_type, int item_type) : CGameObject(x, y, object_type) { 
		this->itemType = item_type; 
		this->startX = x;
		this->startY = y;
		ax = 0.0f;
		ay = 0.0f;
		this->coinJump = false;
		SetState(COIN_STATE_IDLE);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	bool IsCoinJump() { return this->coinJump; }

	void SetState(int state);
	int GetState() { return state; }
};