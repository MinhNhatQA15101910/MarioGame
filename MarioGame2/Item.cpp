#include "Item.h"

void CItem::Render() {
	CAnimations::GetInstance()->Get(ID_ANI_ITEM_COIN)->Render(x, y);
}

void CItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vx += ax * dt;
	vy += ay * dt;

	if (y < startY - ITEM_HEIGHT) coinJump = true;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CItem::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x - ITEM_BBOX_WIDTH / 2;
	t = y - ITEM_BBOX_HEIGHT / 2;
	r = l + ITEM_BBOX_WIDTH;
	b = t + ITEM_BBOX_HEIGHT;
}

void CItem::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CItem::OnCollisionWith(LPCOLLISIONEVENT e){
	
}

void CItem::SetState(int state) {
	CGameObject::SetState(state);

	switch (state) {
	case COIN_STATE_IDLE:
		ax = 0.0f;
		ay = 0.0f;
		break;
	case COIN_STATE_JUMP:
		vy = -COIN_JUMP_SPEED_Y;
		ay = GRAVITY;
		break;
	}
}
