#pragma once

#include "GameObject.h"
#include "Mario.h"
#include "FireBall.h"

#define RED_FIRE_PLANT_POP_UP_SPEED 0.04f

#define RED_FIRE_PLANT_BBOX_WIDTH 16
#define RED_FIRE_PLANT_BBOX_HEIGHT 32

#define RED_FIRE_PLANT_WIDTH 16
#define RED_FIRE_PLANT_HEIGHT 28

#define SWITCH_ANI_X 8
#define SWITCH_ANI_Y 8

#define FIREBALL_OFFSET_X 0
#define FIREBALL_OFFSET_Y -38

#define RED_FIRE_PLANT_IDLE_TIMEOUT 1000

#define RED_FIRE_PLANT_STATE_POP_UP 100
#define RED_FIRE_PLANT_STATE_POP_DOWN 200
#define RED_FIRE_PLANT_STATE_IDLE 300
#define RED_FIRE_PLANT_STATE_ATTACK 400

#define ID_ANI_RED_FIRE_PLANT_POP_UP_LEFT_DOWN 320000
#define ID_ANI_RED_FIRE_PLANT_POP_UP_LEFT_UP 320001
#define ID_ANI_RED_FIRE_PLANT_POP_UP_RIGHT_DOWN 320002
#define ID_ANI_RED_FIRE_PLANT_POP_UP_RIGHT_UP 320003
#define ID_ANI_RED_FIRE_PLANT_ATTACK_LEFT_DOWN 320004
#define ID_ANI_RED_FIRE_PLANT_ATTACK_LEFT_UP 320005
#define ID_ANI_RED_FIRE_PLANT_ATTACK_RIGHT_DOWN 320006
#define ID_ANI_RED_FIRE_PLANT_ATTACK_RIGHT_UP 320007

class CRedFirePlant : public CGameObject {
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
	CRedFirePlant();
	CRedFirePlant(float x, float y, int object_type);

	void SetPlayer(CMario* mario) { this->player = mario; this->fireball->SetPlayer(mario); }
	void SetState(int state);
};