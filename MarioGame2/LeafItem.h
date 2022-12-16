#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define LEAF_ITEM_WIDTH 16
#define LEAF_ITEM_HEIGHT 14

#define LEAF_ITEM_BBOX_WIDTH 16
#define LEAF_ITEM_BBOX_HEIGHT 12

#define LEAF_ITEM_ACCEL_X 0.0002f

#define LEAF_ITEM_SPEED_X 0.025f
#define LEAF_ITEM_SPEED_Y 0.03f

#define LEAF_ITEM_POP_UP_SPEED 0.03f

#define LEAF_MOVEMENT_LENGTH 32.0f
#define TOP_LENGTH 32.0f

#define LEAF_ITEM_STATE_IDLE 40
#define LEAF_ITEM_STATE_POP_UP 41
#define LEAF_ITEM_STATE_FALLING_LEFT 42
#define LEAF_ITEM_STATE_FALLING_RIGHT 43

#define ID_ANI_LEAF_ITEM_LEFT 310000
#define ID_ANI_LEAF_ITEM_RIGHT 310001

class CLeafItem : public CGameObject {
	float ax;
	float ay;

	int itemType;

	float left_edge;
	float right_edge;
	float top_edge;

public:
	CLeafItem() {
		this->itemType = 0;
		this->ax = this->ay = 0.0f;
		this->left_edge = this->right_edge = 0.0f;
		this->top_edge = 0.0f;
	}

	CLeafItem(float x, float y, int object_type, int item_type) : CGameObject(x, y, object_type) {
		this->itemType = item_type;
		this->ax = 0.0f;
		this->ay = 0.0f;
		this->left_edge = this->x;
		this->right_edge = this->x + LEAF_MOVEMENT_LENGTH;
		this->top_edge = this->y - TOP_LENGTH;
		SetState(LEAF_ITEM_STATE_IDLE);
	}

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
	int IsCollidable() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetState(int state);
};