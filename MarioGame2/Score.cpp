#include "Score.h"

CScore::CScore() {
	this->score = 0;

	this->start_x = 0.0f;
	this->start_y = 0.0f;
}

CScore::CScore(float x, float y, int object_type, int score) : CGameObject(x, y, object_type) {
	this->score = score;

	this->start_x = x;
	this->start_y = y;

	this->SetState(SCORE_STATE_IDLE);
}

void CScore::Render() {
	if (this->state == SCORE_STATE_POP_UP) {
		switch (this->score) {
		case 100:
			CSprites::GetInstance()->Get(ID_SPRITE_SCORE_100)->Draw(x, y);
			break;
		case 200:
			CSprites::GetInstance()->Get(ID_SPRITE_SCORE_200)->Draw(x, y);
			break;
		case 400:
			CSprites::GetInstance()->Get(ID_SPRITE_SCORE_400)->Draw(x, y);
			break;
		case 800:
			CSprites::GetInstance()->Get(ID_SPRITE_SCORE_800)->Draw(x, y);
			break;
		case 1000:
			CSprites::GetInstance()->Get(ID_SPRITE_SCORE_1000)->Draw(x, y);
			break;
		case 2000:
			CSprites::GetInstance()->Get(ID_SPRITE_SCORE_2000)->Draw(x, y);
			break;
		case 4000:
			CSprites::GetInstance()->Get(ID_SPRITE_SCORE_4000)->Draw(x, y);
			break;
		case 8000:
			CSprites::GetInstance()->Get(ID_SPRITE_SCORE_8000)->Draw(x, y);
			break;
		case 1:
			CSprites::GetInstance()->Get(ID_SPRITE_SCORE_1UP)->Draw(x, y);
			break;
		}
	}
	

	// this->RenderBoundingBox();
}

void CScore::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	
	if ((this->state == SCORE_STATE_POP_UP) && (this->y < this->start_y - 5 * SCORE_HEIGHT)) 
		this->SetState(SCORE_STATE_DISAPPEAR);
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CScore::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - SCORE_BBOX_WIDTH / 2;
	top = y - SCORE_BBOX_HEIGHT / 2;
	right = left + SCORE_BBOX_WIDTH;
	bottom = top + SCORE_BBOX_WIDTH;
}

void CScore::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CScore::OnCollisionWith(LPCOLLISIONEVENT e) {

}

void CScore::SetState(int state) {
	CGameObject::SetState(state);

	switch (state) {
	case SCORE_STATE_IDLE:
		this->vx = 0.0f;
		this->vy = 0.0f;
		break;
	case SCORE_STATE_POP_UP:
		this->vx = 0.0f;
		this->vy = -SCORE_SPEED;
		break;
	}
}
