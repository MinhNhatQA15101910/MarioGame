#pragma once

#include "GameObject.h"
#include "HudInfo.h"
#include "Font.h"

#define ANI_ID_HUD 380000

#define HUD_BBOX_WIDTH 288
#define HUD_BBOX_HEIGHT 48

#define HUD_OFFSET_X 143
#define HUD_OFFSET_Y 210

#define MARIO_RUNNING_SPEED 0.3f
#define MARIO_FLY_SPEED 0.12f

class HUD : public CGameObject {
	int speed;
	int flyable;
	int coin;
	int life;
	int score;
	int time;

	HudInfo* hudInfo;

	ULONGLONG time_start;

	std::vector<CFont*> properties;

public:
	HUD(float x, float y, int speed, int flyable, int coin, int life, int score, int time, int bonus_item_1, int bonus_item_2, int bonus_item_3, HudInfo* info = NULL);
	
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }

	void AddProperty(CFont* font) { this->properties.push_back(font); }
	void SetFlyable(int flyable) { this->flyable = flyable; }
	void SetCoin(int coin) { this->coin = coin; }
	void SetLife(int life) { this->life = life; }
	void SetScore(int score) { this->score = score; }
	void SetBonusItem(int item);

};

