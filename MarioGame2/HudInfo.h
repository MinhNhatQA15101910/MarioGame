#pragma once

class HudInfo {
	int level;
	int coin;
	int life;
	int score;
	int bonusItem1;
	int bonusItem2;
	int bonusItem3;

public:
	HudInfo();
	HudInfo(int coin, int life, int score, int bonus_item_1, int bonus_item_2, int bonus_item_3, int level);
	
	int GetCoin() { return this->coin; }
	int GetLife() { return this->life; }
	int GetScore() { return this->score; }
	int GetBonusItem1() { return this->bonusItem1; }
	int GetBonusItem2() { return this->bonusItem2; }
	int GetBonusItem3() { return this->bonusItem3; }
	int GetLevel() { return this->level; }
};