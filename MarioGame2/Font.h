#pragma once

#include "GameObject.h"

#define ANI_ID_0 360100
#define ANI_ID_1 360200
#define ANI_ID_2 360300
#define ANI_ID_3 360400
#define ANI_ID_4 360500
#define ANI_ID_5 360600
#define ANI_ID_6 360700
#define ANI_ID_7 360800
#define ANI_ID_8 360900
#define ANI_ID_9 361000

#define ANI_ID_SPEED 361100
#define ANI_ID_FLYABLE 361200

#define ANI_ID_MUSHROOM 361300
#define ANI_ID_FLOWER 361400
#define ANI_ID_STAR 361500

#define FONT_BBOX_WIDTH 8
#define FONT_BBOX_HEIGHT 7

#define ITEM_SIZE 16

class CFont : public CGameObject {
	int type; // 0->9: numbers, 10: speed, 11: flyable, 12: mushroom, 13: flower, 14: star
	bool visible;

public:
	CFont(float x, float y, int object_type, int type);
	
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int GetType() { return this->type; }

	void SetVisible(bool visible) { this->visible = visible; }
	void SetType(int type) { this->type = type; }
};