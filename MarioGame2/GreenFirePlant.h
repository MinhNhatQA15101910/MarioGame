#pragma once

#include "GameObject.h"
#include "Mario.h"
#include "FireBall.h"

#define GREEN_FIRE_PLANT_POP_UP_SPEED 0.04f

#define GREEN_FIRE_PLANT_BBOX_WIDTH 16
#define GREEN_FIRE_PLANT_BBOX_HEIGHT 24

#define GREEN_FIRE_PLANT_WIDTH 16
#define GREEN_FIRE_PLANT_HEIGHT 20

#define GREEN_FIRE_PLANT_SWITCH_ANI_X 8
#define GREEN_FIRE_PLANT_SWITCH_ANI_Y 8

#define GREEN_FIRE_PLANT_FIREBALL_OFFSET_X 0
#define GREEN_FIRE_PLANT_FIREBALL_OFFSET_Y -28

#define GREEN_FIRE_PLANT_IDLE_TIMEOUT 1000

#define GREEN_FIRE_PLANT_STATE_POP_UP 100
#define GREEN_FIRE_PLANT_STATE_POP_DOWN 200
#define GREEN_FIRE_PLANT_STATE_IDLE 300
#define GREEN_FIRE_PLANT_STATE_ATTACK 400

#define ID_ANI_GREEN_FIRE_PLANT_POP_UP_LEFT_DOWN 330000
#define ID_ANI_GREEN_FIRE_PLANT_POP_UP_LEFT_UP 330001
#define ID_ANI_GREEN_FIRE_PLANT_POP_UP_RIGHT_DOWN 330002
#define ID_ANI_GREEN_FIRE_PLANT_POP_UP_RIGHT_UP 330003
#define ID_ANI_GREEN_FIRE_PLANT_ATTACK_LEFT_DOWN 330004
#define ID_ANI_GREEN_FIRE_PLANT_ATTACK_LEFT_UP 330005
#define ID_ANI_GREEN_FIRE_PLANT_ATTACK_RIGHT_DOWN 330006
#define ID_ANI_GREEN_FIRE_PLANT_ATTACK_RIGHT_UP 330007

class CGreenFirePlant : public CGameObject {
	CMario* player;
	CFireBall* fireball;

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
	CGreenFirePlant();
	CGreenFirePlant(float x, float y, int object_type);

	void SetPlayer(CMario* mario) { this->player = mario; this->fireball->SetPlayer(mario); }
	void SetState(int state);
};