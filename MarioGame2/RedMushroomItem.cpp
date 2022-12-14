#include "RedMushroomItem.h"
#include "QuestionBrick.h"
#include "Mario.h"
#include "debug.h"

#include "Goomba.h"

void CRedMushroomItem::Render() {
	this->score->Render();

	if (this->state != RED_MUSHROOM_ITEM_STATE_DISAPPEAR)
		CAnimations::GetInstance()->Get(ID_ANI_ITEM_RED_MUSHROOM)->Render(x, y);
}

void CRedMushroomItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vy += ay * dt;
	vx += ax * dt;

	if (this->score->GetState() == SCORE_STATE_IDLE)
		this->score->SetPosition(this->x, this->y);

	if (this->state == RED_MUSHROOM_ITEM_STATE_POP_UP && this->y + RED_MUSHROOM_ITEM_BBOX_HEIGHT <= startY)
		this->SetState(RED_MUSHROOM_ITEM_STATE_RUNNING);

	if (this->state == RED_MUSHROOM_ITEM_STATE_DISAPPEAR)
		this->SetPosition(this->startX, this->startY);

	if (this->state == RED_MUSHROOM_ITEM_STATE_DISAPPEAR && this->score->GetState() == SCORE_STATE_DISAPPEAR) {
		this->Delete();
		return;
	}

	this->score->Update(dt, coObjects);

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CRedMushroomItem::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x - RED_MUSHROOM_ITEM_BBOX_WIDTH / 2;
	t = y - RED_MUSHROOM_ITEM_BBOX_HEIGHT / 2;
	r = l + RED_MUSHROOM_ITEM_BBOX_WIDTH;
	b = t + RED_MUSHROOM_ITEM_BBOX_HEIGHT;
}

void CRedMushroomItem::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CRedMushroomItem::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<CMario*>(e->obj)) {
		CMario* mario = dynamic_cast<CMario*>(e->obj);

		if (this->state == RED_MUSHROOM_ITEM_STATE_RUNNING) {
			this->SetState(RED_MUSHROOM_ITEM_STATE_DISAPPEAR);
			this->score->SetStartX(this->x);
			this->score->SetStartY(this->y);
			this->score->SetState(SCORE_STATE_POP_UP);
			mario->SetLevel(MARIO_LEVEL_BIG);
		}
	}

	if (e->ny != 0) vy = 0;
	else if (e->nx != 0) vx = -vx; 
}

void CRedMushroomItem::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case RED_MUSHROOM_ITEM_STATE_IDLE:
	case RED_MUSHROOM_ITEM_STATE_DISAPPEAR:
		ax = 0.0f;
		ay = 0.0f;
		break;
	case RED_MUSHROOM_ITEM_STATE_POP_UP:
		vy = -RED_MUSHROOM_ITEM_POP_UP_SPEED;
		break;
	case RED_MUSHROOM_ITEM_STATE_RUNNING:
		ax = 0.0f;
		ay = RED_MUSHROOM_ITEM_GRAVITY;
		vx = RED_MUSHROOM_ITEM_RUN_SPEED;
		vy = 0.0f;
		break;
	}
}
