#include "GreenPlant.h"

void CGreenPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - GREEN_PLANT_BBOX_WIDTH / 2;
	top = y - GREEN_PLANT_BBOX_HEIGHT / 2;
	right = left + GREEN_PLANT_BBOX_WIDTH;
	bottom = top + GREEN_PLANT_BBOX_HEIGHT;
}

void CGreenPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if ((state == GREEN_PLANT_STATE_IDLE_TOP) && (GetTickCount64() - idle_start > GREEN_PLANT_IDLE_TIMEOUT))
		SetState(GREEN_PLANT_STATE_POP_DOWN);

	if ((state == GREEN_PLANT_STATE_POP_DOWN) && (this->y >= this->start_y))
		SetState(GREEN_PLANT_STATE_IDLE_BOTTOM);

	if ((state == GREEN_PLANT_STATE_IDLE_BOTTOM) && (GetTickCount64() - idle_start > GREEN_PLANT_IDLE_TIMEOUT))
		SetState(GREEN_PLANT_STATE_POP_UP);

	if ((state == GREEN_PLANT_STATE_POP_UP) && (this->y <= this->start_y - GREEN_PLANT_HEIGHT))
		SetState(GREEN_PLANT_STATE_IDLE_TOP);

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CGreenPlant::Render() {
	CAnimations::GetInstance()->Get(ID_ANI_GREEN_PLANT)->Render(x, y);

	this->RenderBoundingBox();
}

void CGreenPlant::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CGreenPlant::OnCollisionWith(LPCOLLISIONEVENT e) {

}

CGreenPlant::CGreenPlant() {
	this->start_x = 0.0f;
	this->start_y = 0.0f;
	this->idle_start = -1;
}

CGreenPlant::CGreenPlant(float x, float y, int object_type) {
	this->start_x = x;
	this->start_y = y;
	this->idle_start = -1;

	this->SetState(GREEN_PLANT_STATE_IDLE_BOTTOM);
}

void CGreenPlant::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case GREEN_PLANT_STATE_POP_UP:
		vx = 0.0f;
		vy = -GREEN_PLANT_POP_UP_SPEED;
		break;
	case GREEN_PLANT_STATE_POP_DOWN:
		vx = 0.0f;
		vy = GREEN_PLANT_POP_UP_SPEED;
		break;
	case GREEN_PLANT_STATE_IDLE_BOTTOM:
	case GREEN_PLANT_STATE_IDLE_TOP:
		this->idle_start = GetTickCount64();
		this->vx = 0.0f;
		this->vy = 0.0f;
		break;
	}
}
