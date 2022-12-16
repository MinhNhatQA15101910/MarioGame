#include "GreenMushroomItem.h"
#include "QuestionBrick.h"
#include "Mario.h"

#include "Goomba.h"

void CGreenMushroomItem::Render() {
	CAnimations::GetInstance()->Get(ID_ANI_ITEM_GREEN_MUSHROOM)->Render(x, y);
}

void CGreenMushroomItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CGreenMushroomItem::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x - GREEN_MUSHROOM_ITEM_BBOX_WIDTH / 2;
	t = y - GREEN_MUSHROOM_ITEM_BBOX_HEIGHT / 2;
	r = l + GREEN_MUSHROOM_ITEM_BBOX_WIDTH;
	b = t + GREEN_MUSHROOM_ITEM_BBOX_HEIGHT;
}

void CGreenMushroomItem::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CGreenMushroomItem::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CMario*>(e->obj)) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<CQuestionBrick*>(e->obj) && state != GREEN_MUSHROOM_ITEM_STATE_RUNNING) return;

	if (e->ny != 0) vy = 0;
	else if (e->nx != 0) vx = -vx;
}

void CGreenMushroomItem::SetState(int state) {
	DebugOut(L"Green Mushroom Item change state!\n");

	CGameObject::SetState(state);
	switch (state) {
	case GREEN_MUSHROOM_ITEM_STATE_IDLE:
		ax = 0.0f;
		ay = 0.0f;
		break;
	case GREEN_MUSHROOM_ITEM_STATE_POP_UP:
		vy = -GREEN_MUSHROOM_ITEM_POP_UP_SPEED;
		break;
	case GREEN_MUSHROOM_ITEM_STATE_RUNNING:
		ax = 0.0f;
		ay = GREEN_MUSHROOM_ITEM_GRAVITY;
		vx = GREEN_MUSHROOM_ITEM_RUN_SPEED;
		vy = 0.0f;
		break;
	}
}
