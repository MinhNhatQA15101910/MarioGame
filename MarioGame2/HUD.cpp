#include "HUD.h"
#include "Mario.h"

HUD::HUD(float x, float y, int speed, int flyable, int coin, int life, int score, int time, int bonus_item_1, int bonus_item_2, int bonus_item_3, HudInfo* info) {
	if (info == NULL) {
		this->speed = speed;
		this->flyable = flyable;
		this->coin = coin;
		this->life = life;
		this->score = score;
		this->time = time;
		this->properties = {};

		this->time_start = GetTickCount64();
	}
	else {
		this->speed = 0;
		this->flyable = 0;
		this->coin = info->GetCoin();
		this->life = info->GetLife();
		this->score = info->GetScore();
		this->time = time;
		this->hudInfo = info;
		this->properties = {};

		this->time_start = GetTickCount64();
	}
}

void HUD::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	//float cx, cy;
	//CGame::GetInstance()->GetCamPos(cx, cy);

	//this->SetPosition(cx + HUD_OFFSET_X, cy + HUD_OFFSET_Y);

	//float player_speed_x = 0.0f, player_speed_y = 0.0f;
	//CMario* mario = CGame::GetInstance()->GetCurrentScene()->GetPlayer();
	//// if (mario->GetState)
}

void HUD::Render()
{
}

void HUD::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
}

void HUD::SetBonusItem(int item)
{
}
