#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define GREEN_MUSHROOM_ITEM_WITDH 16
#define GREEN_MUSHROOM_ITEM_HEIGHT 16

#define GREEN_MUSHROOM_ITEM_BBOX_WIDTH 16
#define GREEN_MUSHROOM_ITEM_BBOX_HEIGHT 12

#define GREEN_MUSHROOM_ITEM_GRAVITY 0.0002f

#define GREEN_MUSHROOM_ITEM_POP_UP_SPEED 0.03f
#define GREEN_MUSHROOM_ITEM_RUN_SPEED 0.06f

#define GREEN_MUSHROOM_ITEM_STATE_IDLE 30
#define GREEN_MUSHROOM_ITEM_STATE_POP_UP 31
#define GREEN_MUSHROOM_ITEM_STATE_RUNNING 32

#define ID_ANI_ITEM_GREEN_MUSHROOM 300000

class CGreenMushroomItem : public CGameObject {
	float ax;
	float ay;

	float startX, startY;

	int itemType;

public:
	CGreenMushroomItem() {
		itemType = 0;
		this->startX = this->startY = 0.0f;
		ax = 0.0f;
		ay = 0.0f;
	}

	CGreenMushroomItem(float x, float y, int object_type, int item_type) : CGameObject(x, y, object_type) {
		this->itemType = item_type;
		this->startX = x;
		this->startY = y;
		ax = 0.0f;
		ay = 0.0f;
		SetState(GREEN_MUSHROOM_ITEM_STATE_IDLE);
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 1; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetState(int state);
};

