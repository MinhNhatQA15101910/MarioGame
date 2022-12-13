#pragma once

#include "GameObject.h"
#include "Mario.h"

#define COLOR_BOX_BBOX_WIDTH 16
#define COLOR_BOX_BBOX_HEIGHT 16

class CColorBox : public CGameObject {
private:
	CMario* player;

	int objectType;

	int isBlocking;

	int spriteId;

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	// int IsCollidable() { return 1; }
	int IsBlocking() { return this->isBlocking; }

public:
	CColorBox(float x, float y, int object_type, int sprite_id) : CGameObject(x, y, object_type) {
		this->spriteId = sprite_id;
		this->objectType = object_type;

		player = new CMario();
		this->isBlocking = 0;
	}

	void setPlayer(CMario* mario) {
		player = mario;
	}
};