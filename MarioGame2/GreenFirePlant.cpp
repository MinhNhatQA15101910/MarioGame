#include "GreenFirePlant.h"
#include "AssetIDs.h"

void CGreenFirePlant::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - GREEN_FIRE_PLANT_BBOX_WIDTH / 2;
	top = y - GREEN_FIRE_PLANT_BBOX_HEIGHT / 2;
	right = left + GREEN_FIRE_PLANT_BBOX_WIDTH;
	bottom = top + GREEN_FIRE_PLANT_BBOX_HEIGHT;
}

void CGreenFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if ((state == GREEN_FIRE_PLANT_STATE_IDLE) && (GetTickCount64() - idle_start > GREEN_FIRE_PLANT_IDLE_TIMEOUT))
		SetState(GREEN_FIRE_PLANT_STATE_POP_UP);

	if ((state == GREEN_FIRE_PLANT_STATE_POP_UP) && (this->y <= this->start_y - GREEN_FIRE_PLANT_HEIGHT))
		SetState(GREEN_FIRE_PLANT_STATE_ATTACK);

	if ((state == GREEN_FIRE_PLANT_STATE_ATTACK) && (GetTickCount64() - idle_start > GREEN_FIRE_PLANT_IDLE_TIMEOUT))
		SetState(GREEN_FIRE_PLANT_STATE_POP_DOWN);

	if ((state == GREEN_FIRE_PLANT_STATE_POP_DOWN) && (this->y >= this->start_y))
		SetState(GREEN_FIRE_PLANT_STATE_IDLE);

	this->fireball->Update(dt, coObjects);

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CGreenFirePlant::Render() {
	int aniId = ID_ANI_GREEN_FIRE_PLANT_ATTACK_LEFT_DOWN;

	float px, py;
	player->GetPositionCenter(px, py);

	switch (state) {
	case GREEN_FIRE_PLANT_STATE_IDLE:
	case GREEN_FIRE_PLANT_STATE_ATTACK:
		if ((py > this->y + GREEN_FIRE_PLANT_SWITCH_ANI_Y) && (px <= this->x + GREEN_FIRE_PLANT_SWITCH_ANI_X))
			aniId = ID_ANI_GREEN_FIRE_PLANT_ATTACK_LEFT_DOWN;
		else if ((py <= this->y + GREEN_FIRE_PLANT_SWITCH_ANI_Y) && (px <= this->x + GREEN_FIRE_PLANT_SWITCH_ANI_X))
			aniId = ID_ANI_GREEN_FIRE_PLANT_ATTACK_LEFT_UP;
		else if ((py > this->y + GREEN_FIRE_PLANT_SWITCH_ANI_Y) && (px > this->x + GREEN_FIRE_PLANT_SWITCH_ANI_X))
			aniId = ID_ANI_GREEN_FIRE_PLANT_ATTACK_RIGHT_DOWN;
		else if ((py <= this->y + GREEN_FIRE_PLANT_SWITCH_ANI_Y) && (px > this->x + GREEN_FIRE_PLANT_SWITCH_ANI_X))
			aniId = ID_ANI_GREEN_FIRE_PLANT_ATTACK_RIGHT_UP;
		break;
	case GREEN_FIRE_PLANT_STATE_POP_UP:
	case GREEN_FIRE_PLANT_STATE_POP_DOWN:
		if ((py > this->y + GREEN_FIRE_PLANT_SWITCH_ANI_Y) && (px <= this->x + GREEN_FIRE_PLANT_SWITCH_ANI_X))
			aniId = ID_ANI_GREEN_FIRE_PLANT_POP_UP_LEFT_DOWN;
		else if ((py <= this->y + GREEN_FIRE_PLANT_SWITCH_ANI_Y) && (px <= this->x + GREEN_FIRE_PLANT_SWITCH_ANI_X))
			aniId = ID_ANI_GREEN_FIRE_PLANT_POP_UP_LEFT_UP;
		else if ((py > this->y + GREEN_FIRE_PLANT_SWITCH_ANI_Y) && (px > this->x + GREEN_FIRE_PLANT_SWITCH_ANI_X))
			aniId = ID_ANI_GREEN_FIRE_PLANT_POP_UP_RIGHT_DOWN;
		else if ((py <= this->y + GREEN_FIRE_PLANT_SWITCH_ANI_Y) && (px > this->x + GREEN_FIRE_PLANT_SWITCH_ANI_X))
			aniId = ID_ANI_GREEN_FIRE_PLANT_POP_UP_RIGHT_UP;
		break;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	this->fireball->Render();
}

void CGreenFirePlant::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CGreenFirePlant::OnCollisionWith(LPCOLLISIONEVENT e) {

}

CGreenFirePlant::CGreenFirePlant() {
	this->player = new CMario();
	this->fireball = new CFireBall();

	this->start_x = 0.0f;
	this->start_y = 0.0f;
	this->idle_start = -1;
}

CGreenFirePlant::CGreenFirePlant(float x, float y, int object_type) : CGameObject(x, y, object_type) {
	this->player = new CMario();
	this->fireball = new CFireBall(x + GREEN_FIRE_PLANT_FIREBALL_OFFSET_X, y + GREEN_FIRE_PLANT_FIREBALL_OFFSET_Y, OBJECT_TYPE_FIREBALL);

	this->start_x = x;
	this->start_y = y;
	this->idle_start = -1;

	this->SetState(GREEN_FIRE_PLANT_STATE_IDLE);
}

void CGreenFirePlant::SetState(int state) {
	DebugOut(L"State Change: %d\n", state);

	CGameObject::SetState(state);
	switch (state) {
	case GREEN_FIRE_PLANT_STATE_POP_UP:
		vx = 0.0f;
		vy = -GREEN_FIRE_PLANT_POP_UP_SPEED;
		break;
	case GREEN_FIRE_PLANT_STATE_POP_DOWN:
		vx = 0.0f;
		vy = GREEN_FIRE_PLANT_POP_UP_SPEED;
		break;
	case GREEN_FIRE_PLANT_STATE_ATTACK:
		this->fireball->SetPosition(this->start_x + GREEN_FIRE_PLANT_FIREBALL_OFFSET_X, this->start_y + GREEN_FIRE_PLANT_FIREBALL_OFFSET_Y);
		this->fireball->SetState(FIREBALL_STATE_ATTACK);

		this->idle_start = GetTickCount64();
		this->vx = 0.0f;
		this->vy = 0.0f;
		break;
	case GREEN_FIRE_PLANT_STATE_IDLE:
		idle_start = GetTickCount64();
		vx = 0.0f;
		vy = 0.0f;
		break;
	}
}
