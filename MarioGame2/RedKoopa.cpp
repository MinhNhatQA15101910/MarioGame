#include "RedKoopa.h"
#include "AssetIDs.h"
#include "ColorBox.h"
#include "debug.h"

CInvisibleBlock::CInvisibleBlock() {
	this->start_x = 0.0f;
	this->start_y = 0.0f;
}

CInvisibleBlock::CInvisibleBlock(float x, float y, int object_type) : CGameObject(x, y, object_type) {
	this->start_x = x;
	this->start_y = y;
}

void CInvisibleBlock::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - INVISIBLE_BLOCK_BBOX_WIDTH / 2;
	top = y - INVISIBLE_BLOCK_BBOX_HEIGHT / 2;
	right = left + INVISIBLE_BLOCK_BBOX_WIDTH;
	bottom = top + INVISIBLE_BLOCK_BBOX_HEIGHT;
}

void CInvisibleBlock::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CInvisibleBlock::OnCollisionWith(LPCOLLISIONEVENT e) {

}

void CInvisibleBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CInvisibleBlock::Render() {
	this->RenderBoundingBox();
}

void CRedKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if (this->state == RED_KOOPA_STATE_WALKING_LEFT || this->state == RED_KOOPA_STATE_WALKING_RIGHT) {
		left = x - RED_KOOPA_BBOX_WIDTH / 2;
		top = y - RED_KOOPA_BBOX_HEIGHT / 2;
		right = left + RED_KOOPA_BBOX_WIDTH;
		bottom = top + RED_KOOPA_BBOX_HEIGHT;
	}
	else {
		left = x - RED_KOOPA_BBOX_WIDTH / 2;
		top = y - RED_KOOPA_BBOX_HEIGHT_SHELL / 2;
		right = left + RED_KOOPA_BBOX_WIDTH;
		bottom = top + RED_KOOPA_BBOX_HEIGHT_SHELL;
	}
}

void CRedKoopa::OnNoCollision(DWORD dt) {
	this->x += this->vx * dt;
	this->y += this->vy * dt;
}

void CRedKoopa::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0) this->vy = 0.0f;
	else if (e->nx != 0) {
		if (this->state == RED_KOOPA_STATE_WALKING_RIGHT) this->SetState(RED_KOOPA_STATE_WALKING_LEFT);
		else if (this->state == RED_KOOPA_STATE_WALKING_LEFT) this->SetState(RED_KOOPA_STATE_WALKING_RIGHT);
		else if (this->state == RED_KOOPA_STATE_RUNNING_RIGHT) this->SetState(RED_KOOPA_STATE_RUNNING_LEFT);
		else if (this->state == RED_KOOPA_STATE_WALKING_LEFT) this->SetState(RED_KOOPA_STATE_WALKING_RIGHT);
	}
}

void CRedKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	this->vx += this->ax * dt;
	this->vy += this->ay * dt;

	if (this->state == RED_KOOPA_STATE_WALKING_LEFT)
		this->invBlock->SetPosition(this->x - INVISIBLE_BLOCK_WIDTH, this->y + RED_KOOPA_HEIGHT - INVISIBLE_BLOCK_HEIGHT);

	if (this->state == RED_KOOPA_STATE_WALKING_RIGHT)
		this->invBlock->SetPosition(this->x + RED_KOOPA_WIDTH + INVISIBLE_BLOCK_WIDTH, this->y + RED_KOOPA_HEIGHT - INVISIBLE_BLOCK_HEIGHT);

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CRedKoopa::Render() {
	int aniId = ID_ANI_RED_KOOPA_WALKING_LEFT;
	if (this->state == RED_KOOPA_STATE_WALKING_RIGHT)
		aniId = ID_ANI_RED_KOOPA_WALKING_RIGHT;
	else if (this->state == RED_KOOPA_STATE_SHELL)
		aniId = ID_ANI_RED_KOOPA_SHELL;
	else if (this->state == RED_KOOPA_STATE_RUNNING_LEFT)
		aniId = ID_ANI_RED_KOOPA_RUNNING;
	else if (this->state == RED_KOOPA_STATE_RUNNING_RIGHT)
		aniId = ID_ANI_RED_KOOPA_RUNNING;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	this->RenderBoundingBox();

	this->invBlock->Render();
}

CRedKoopa::CRedKoopa() {
	this->invBlock = new CInvisibleBlock();
	
	this->ax = 0.0f;
	this->ay = 0.0f;
}

CRedKoopa::CRedKoopa(float x, float y, int object_type) : CGameObject(x, y, object_type) {
	this->invBlock = new CInvisibleBlock(
		x - INVISIBLE_BLOCK_WIDTH, 
		y + RED_KOOPA_HEIGHT - INVISIBLE_BLOCK_HEIGHT,
		OBJECT_TYPE_INVISIBLE_BLOCK
	);
	
	this->ax = 0.0f;
	this->ay = 0.0f;

	this->SetState(RED_KOOPA_STATE_WALKING_LEFT);
}

void CRedKoopa::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case RED_KOOPA_STATE_WALKING_LEFT:
		this->ax = 0.0f;
		this->ay = RED_KOOPA_GRAVITY;
		this->vx = -RED_KOOPA_WALKING_SPEED;
		this->vy = 0.0f;
		break;
	case RED_KOOPA_STATE_WALKING_RIGHT:
		this->ax = 0.0f;
		this->ay = RED_KOOPA_GRAVITY;
		this->vx = RED_KOOPA_WALKING_SPEED;
		this->vy = 0.0f;
		break;
	case RED_KOOPA_STATE_SHELL:
		this->ax = 0.0f;
		this->ay = RED_KOOPA_GRAVITY;
		this->vx = 0.0f;
		this->vy = 0.0f;
		break;
	case RED_KOOPA_STATE_RUNNING_LEFT:
		this->ax = 0.0f;
		this->ay = RED_KOOPA_GRAVITY;
		this->vx = -RED_KOOPA_RUNNING_SPEED;
		this->vy = 0.0f;
		break;
	case RED_KOOPA_STATE_RUNNING_RIGHT:
		this->ax = 0.0f;
		this->ay = RED_KOOPA_GRAVITY;
		this->vx = RED_KOOPA_RUNNING_SPEED;
		this->vy = 0.0f;
		break;
	}
}
