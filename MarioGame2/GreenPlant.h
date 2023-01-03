#pragma once

#include "GameObject.h"

#define GREEN_PLANT_POP_UP_SPEED 0.04f

#define GREEN_PLANT_BBOX_WIDTH 16
#define GREEN_PLANT_BBOX_HEIGHT 24

#define GREEN_PLANT_WIDTH 16
#define GREEN_PLANT_HEIGHT 20

#define GREEN_PLANT_IDLE_TIMEOUT 800

#define GREEN_PLANT_STATE_IDLE_TOP 100
#define GREEN_PLANT_STATE_IDLE_BOTTOM 200
#define GREEN_PLANT_STATE_POP_UP 300
#define GREEN_PLANT_STATE_POP_DOWN 400

#define ID_ANI_GREEN_PLANT 350000

class CGreenPlant : public CGameObject {
	float start_x;
	float start_y;
	
	ULONGLONG idle_start;

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CGreenPlant();
	CGreenPlant(float x, float y, int object_type);

	void SetState(int state);
};

