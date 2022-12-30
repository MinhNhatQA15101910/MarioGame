#pragma once

#include "GameObject.h"
#include "Mario.h"

#define FIREBALL_BBOX_WIDTH 8
#define FIREBALL_BBOX_HEIGHT 8

#define FIREBALL_WIDTH 8
#define FIREBALL_HEIGHT 8

#define FIREBALL_MOVING_SPEED 0.06f

#define FIREBALL_STATE_IDLE 100
#define FIREBALL_STATE_ATTACK 200

#define ID_ANI_FIREBALL_ATTACK 340000

class CFireBall : public CGameObject {
	float start_x;
	float start_y;
	
	CMario* player;
	
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	void OnNoCollision(DWORD dt);

	void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CFireBall();
	CFireBall(float x, float y, int object_type);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	
	void SetPlayer(CMario* mario) { this->player = mario; }
	void SetState(int state);
};