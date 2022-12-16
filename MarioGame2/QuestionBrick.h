#pragma once

#include "AssetIDs.h"
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#include "CoinItem.h"
#include "RedMushroomItem.h"
#include "GreenMushroomItem.h"

#define ITEM_TYPE_COIN 1
#define ITEM_TYPE_RED_MUSHROOM 2
#define ITEM_TYPE_GREEN_MUSHROOM 3

#define QUESTION_BOX_STATE_FULL 1
#define QUESTION_BOX_STATE_EMPTY 2

#define ID_ANI_QUESTION_BOX_FULL 280000
#define ID_ANI_QUESTION_BOX_EMPTY 280001

#define QUESTION_BRICK_WIDTH 16
#define QUESTION_BRICK_BBOX_WIDTH 16
#define QUESTION_BRICK_BBOX_HEIGHT 16

class CQuestionBrick : public CGameObject {
	int itemType;

	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);

public:
	CQuestionBrick(float x, float y, int object_type, int item_type) : CGameObject(x, y, object_type) { this->itemType = item_type; }
	virtual void SetState(int state);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	int GetItemType() { return itemType; }
};