#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_START_X 8.0f
#define MARIO_END_X 2740.0f

#define MARIO_SMALL_WIDTH 13
#define MARIO_SMALL_HEIGHT 15

#define MARIO_BIG_WIDTH 13
#define MARIO_BIG_HEIGHT 27

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f
#define MARIO_CARRY_SPEED 0.2f
#define MARIO_FLY_SPEED 0.12f
#define MARIO_LANDING_SPEED 0.03f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f
#define MARIO_ACCEL_FLY_X   0.0003f

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f

#define MARIO_GRAVITY			0.002f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_MAP -100
#define MARIO_STATE_MAP_TRANS -101

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_KICK_RIGHT 700
#define MARIO_STATE_KICK_LEFT 800

#define MARIO_STATE_CARRY_RELEASE 900

#define MARIO_STATE_FLY 1000

#define MARIO_STATE_LANDING 1100

#define MARIO_STATE_HIT 1200


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

// MARIO TANOOKI
#define ID_ANI_MARIO_TANOOKI_IDLE_RIGHT 1700
#define ID_ANI_MARIO_TANOOKI_IDLE_LEFT 1701

#define ID_ANI_MARIO_TANOOKI_WALKING_RIGHT 1800
#define ID_ANI_MARIO_TANOOKI_WALKING_LEFT 1801

#define ID_ANI_MARIO_TANOOKI_RUNNING_RIGHT 1900
#define ID_ANI_MARIO_TANOOKI_RUNNING_LEFT 1901

#define ID_ANI_MARIO_TANOOKI_JUMP_WALK_RIGHT 2000
#define ID_ANI_MARIO_TANOOKI_JUMP_WALK_LEFT 2001

#define ID_ANI_MARIO_TANOOKI_JUMP_RUN_RIGHT 2100
#define ID_ANI_MARIO_TANOOKI_JUMP_RUN_LEFT 2101

#define ID_ANI_MARIO_TANOOKI_SIT_RIGHT 2200
#define ID_ANI_MARIO_TANOOKI_SIT_LEFT 2201

#define ID_ANI_MARIO_TANOOKI_BRACE_RIGHT 2300
#define ID_ANI_MARIO_TANOOKI_BRACE_LEFT 2301

#define ID_ANI_MARIO_TANOOKI_LANDING_RIGHT	2400
#define ID_ANI_MARIO_TANOOKI_LANDING_LEFT	2401

#define ID_ANI_MARIO_TANOOKI_KICK_RIGHT	2500
#define ID_ANI_MARIO_TANOOKI_KICK_LEFT	2501

#define ID_ANI_MARIO_TANOOKI_CARRY_RIGHT_IDLE	2700
#define ID_ANI_MARIO_TANOOKI_CARRY_LEFT_IDLE	2701
#define ID_ANI_MARIO_TANOOKI_CARRY_RIGHT	2600
#define ID_ANI_MARIO_TANOOKI_CARRY_LEFT	2601

#define ID_ANI_MARIO_TANOOKI_HIT_RIGHT	2800
#define ID_ANI_MARIO_TANOOKI_HIT_LEFT	2801

#define ID_ANI_MARIO_TANOOKI_MAP	2900

#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_TANOOKI 3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_TANOOKI_BBOX_WIDTH 14
#define MARIO_TANOOKI_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_MAP_SIZE 15

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_KICKABLE_TIME 100
#define MARIO_HITTABLE_TIME 500
#define MARIO_P_TIME 4000

#define MARIO_ATTACK_ZONE 8

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 

	int level;
	int live;

	int dir = 1;
	int untouchable;
	int kickable;
	int hittable;

	ULONGLONG untouchable_start;
	ULONGLONG kickable_start;
	ULONGLONG flyable_start;
	ULONGLONG hittable_start;
	BOOLEAN isOnPlatform;

	int coin;
	int score;

	// Mario action
	BOOLEAN isCarrying = false;
	BOOLEAN isFlying = false;
	BOOLEAN flyable = false;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e);
	void OnCollisionWithRedMushroomItem(LPCOLLISIONEVENT e);
	void OnCollisionWithGreenMushroomItem(LPCOLLISIONEVENT e);
	void OnCollisionWithLeafItem(LPCOLLISIONEVENT e);
	void OnCollisionWithRedFirePlant(LPCOLLISIONEVENT e);
	void OnCollisionWithGreenFirePlant(LPCOLLISIONEVENT e);
	void OnCollisionWithGreenPlant(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdTanooki();

public:
	CMario() {}

	CMario(float x, float y, int object_type) : CGameObject(x, y, object_type)
	{
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;

		live = 4;
		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		kickable = 0;
		hittable = 0;
		kickable_start = -1;
		flyable_start = -1;
		hittable_start = -1;
		isOnPlatform = false;
		coin = 0;
		score = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE);
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }
	int GetWidth() {
		if (level == MARIO_LEVEL_SMALL) return MARIO_SMALL_WIDTH;

		return MARIO_BIG_WIDTH;
	}
	int GetHeight() { if (level == MARIO_LEVEL_SMALL) return MARIO_SMALL_HEIGHT; return MARIO_BIG_HEIGHT; }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartKickable() { kickable = 1; kickable_start = GetTickCount64(); }
	void StartHittable() { hittable = 1; hittable_start = GetTickCount64(); }
	void StartFlying() { isFlying = true; flyable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void GetPositionCenter(float& x, float& y) {
		x = this->x + GetWidth() / 2;
		y = this->y + GetHeight() / 2;
	}
	int GetUntouchable() { return this->untouchable; }
	int GetLevel() { return this->level; }
};