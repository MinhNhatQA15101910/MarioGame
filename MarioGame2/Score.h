#pragma once

#include "GameObject.h"

#define SCORE_BBOX_WIDTH 12
#define SCORE_BBOX_HEIGHT 8

#define SCORE_WIDTH 12
#define SCORE_HEIGHT 8

#define SCORE_SPEED 0.08f

#define ID_SPRITE_SCORE_100 360100
#define ID_SPRITE_SCORE_200 360200
#define ID_SPRITE_SCORE_400 360400
#define ID_SPRITE_SCORE_800 360800
#define ID_SPRITE_SCORE_1000 361000
#define ID_SPRITE_SCORE_2000 362000
#define ID_SPRITE_SCORE_4000 364000
#define ID_SPRITE_SCORE_8000 368000
#define ID_SPRITE_SCORE_1UP 369000

#define SCORE_STATE_IDLE 100
#define SCORE_STATE_POP_UP 200
#define SCORE_STATE_DISAPPEAR 300

class CScore : public CGameObject {
	int score;

	float start_x, start_y;

public:
	CScore();
	CScore(float x, float y, int object_type, int score);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsBlocking() { return 0; }

	void SetStartX(float start_x) { this->start_x = start_x; }
	void SetStartY(float start_y) { this->start_y = start_y; }

	void SetState(int state);
};

