#include "LeafItem.h"
#include "debug.h"

#include "QuestionBrick.h"
#include "Platform.h"

void CLeafItem::Render() {
	int ani = ID_ANI_LEAF_ITEM_LEFT;
	if (state == LEAF_ITEM_STATE_FALLING_RIGHT)
		ani = ID_ANI_LEAF_ITEM_RIGHT;

	CAnimations::GetInstance()->Get(ani)->Render(x, y);
}

void CLeafItem::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	vx += ax * dt;
	vy += ay * dt;

	if (this->y < this->top_edge && this->state == LEAF_ITEM_STATE_POP_UP)
		SetState(this->state = LEAF_ITEM_STATE_FALLING_RIGHT);

	if (this->x > this->right_edge && this->state == LEAF_ITEM_STATE_FALLING_RIGHT)
		SetState(LEAF_ITEM_STATE_FALLING_LEFT);
	else if (this->x < this->left_edge && this->state == LEAF_ITEM_STATE_FALLING_LEFT)
		SetState(LEAF_ITEM_STATE_FALLING_RIGHT);

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLeafItem::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x - LEAF_ITEM_BBOX_WIDTH / 2;
	t = y - LEAF_ITEM_BBOX_HEIGHT / 2;
	r = l + LEAF_ITEM_BBOX_WIDTH;
	b = t + LEAF_ITEM_BBOX_HEIGHT;
}

void CLeafItem::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CLeafItem::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (e->obj->IsBlocking()) return;
	if (dynamic_cast<CQuestionBrick*>(e->obj)) return;
	if (dynamic_cast<CPlatform*>(e->obj)) return;
}

void CLeafItem::SetState(int state) {
	DebugOut(L"Leaf Change State: %d\n", state);

	CGameObject::SetState(state);
	switch (state) {
	case LEAF_ITEM_STATE_IDLE:
		vx = 0.0f;
		vy = 0.0f;
		ax = 0.0f;
		ay = 0.0f;
		break;
	case LEAF_ITEM_STATE_POP_UP:
		vx = 0.0f;
		vy = -LEAF_ITEM_POP_UP_SPEED;
		ax = 0.0f;
		ay = 0.0f;
		break;
	case LEAF_ITEM_STATE_FALLING_LEFT:
		vx = -LEAF_ITEM_SPEED_X;
		ax = -ax;
		break;
	case LEAF_ITEM_STATE_FALLING_RIGHT:
		vx = LEAF_ITEM_SPEED_X;
		vy = LEAF_ITEM_SPEED_Y;
		ax = LEAF_ITEM_ACCEL_X;
		break;
	}
}
