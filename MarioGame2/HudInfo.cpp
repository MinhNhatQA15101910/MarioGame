#include "HudInfo.h"

HudInfo::HudInfo() {
	this->coin = 0;
	this->life = 0;
	this->score = 0;
	this->bonusItem1 = 0;
	this->bonusItem2 = 0;
	this->bonusItem3 = 0;
	this->level = 0;
}

HudInfo::HudInfo(int coin, int life, int score, int bonus_item_1, int bonus_item_2, int bonus_item_3, int level) {
	this->coin = coin;
	this->life = life;
	this->score = score;
	this->bonusItem1 = bonus_item_1;
	this->bonusItem2 = bonus_item_2;
	this->bonusItem3 = bonus_item_3;
	this->level = level;
}