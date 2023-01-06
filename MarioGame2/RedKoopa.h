#pragma once

#include "GameObject.h"
#include "Score.h"

#define INVISIBLE_BLOCK_BBOX_WIDTH 4
#define INVISIBLE_BLOCK_BBOX_HEIGHT 4

#define INVISIBLE_BLOCK_WIDTH 4
#define INVISIBLE_BLOCK_HEIGHT 4

#define INVISIBLE_BLOCK_STATE_MOVING_LEFT 100
#define INVISIBLE_BLOCK_STATE_MOVING_RIGHT 200

class CInvisibleBlock : public CGameObject {
	float start_x;
	float start_y;

	float ax;
	float ay;

public:
	CInvisibleBlock();
	CInvisibleBlock(float x, float y, int object_type);

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	bool IsFalling() { return this->y > this->start_y; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	void SetState(int state);
};

#define RED_KOOPA_GRAVITY 0.002f
#define RED_KOOPA_WALKING_SPEED 0.03f
#define RED_KOOPA_RUNNING_SPEED 0.3f

#define RED_KOOPA_BBOX_WIDTH 16
#define RED_KOOPA_BBOX_HEIGHT 25
#define RED_KOOPA_BBOX_HEIGHT_SHELL 16

#define RED_KOOPA_WIDTH 16
#define RED_KOOPA_HEIGHT 25
#define RED_KOOPA_HEIGHT_SHELL 16

#define RED_KOOPA_STATE_WALKING_LEFT 100
#define RED_KOOPA_STATE_WALKING_RIGHT 200
#define RED_KOOPA_STATE_RUNNING_LEFT 300
#define RED_KOOPA_STATE_RUNNING_RIGHT 400
#define RED_KOOPA_STATE_SHELL 500

#define ID_ANI_RED_KOOPA_WALKING_LEFT 370000
#define ID_ANI_RED_KOOPA_WALKING_RIGHT 370001
#define ID_ANI_RED_KOOPA_SHELL 370002
#define ID_ANI_RED_KOOPA_RUNNING 370003

class CRedKoopa : public CGameObject {
	CInvisibleBlock* invBlock;
	// CScore* score;
	
	float ax;
	float ay;

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	int IsCollidable() { return 1; }
	int IsBlocking() { return 0; }
	
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

public:
	CRedKoopa();
	CRedKoopa(float x, float y, int object_type);

	void SetState(int state);
};

