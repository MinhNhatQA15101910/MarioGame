#include "RedFirePlant.h"
#include "AssetIDs.h"

void CRedFirePlant::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - RED_FIRE_PLANT_BBOX_WIDTH / 2;
	top = y - RED_FIRE_PLANT_BBOX_HEIGHT / 2;
	right = left + RED_FIRE_PLANT_BBOX_WIDTH;
	bottom = top + RED_FIRE_PLANT_BBOX_HEIGHT;
}

void CRedFirePlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if ((state == RED_FIRE_PLANT_STATE_IDLE) && (GetTickCount64() - idle_start > RED_FIRE_PLANT_IDLE_TIMEOUT))
		SetState(RED_FIRE_PLANT_STATE_POP_UP);

	if ((state == RED_FIRE_PLANT_STATE_POP_UP) && (this->y <= this->start_y - RED_FIRE_PLANT_HEIGHT))
		SetState(RED_FIRE_PLANT_STATE_ATTACK);

	if ((state == RED_FIRE_PLANT_STATE_ATTACK) && (GetTickCount64() - idle_start > RED_FIRE_PLANT_IDLE_TIMEOUT))
		SetState(RED_FIRE_PLANT_STATE_POP_DOWN);

	if ((state == RED_FIRE_PLANT_STATE_POP_DOWN) && (this->y >= this->start_y))
		SetState(RED_FIRE_PLANT_STATE_IDLE);

	this->fireball->Update(dt, coObjects);
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CRedFirePlant::Render() {
	int aniId = ID_ANI_RED_FIRE_PLANT_ATTACK_LEFT_DOWN;

	float px, py;
	player->GetPositionCenter(px, py);

	switch (state) {
	case RED_FIRE_PLANT_STATE_IDLE:
	case RED_FIRE_PLANT_STATE_ATTACK:
		if ((py > this->y + RED_FIRE_PLANT_SWITCH_ANI_Y) && (px <= this->x + RED_FIRE_PLANT_SWITCH_ANI_X))
			aniId = ID_ANI_RED_FIRE_PLANT_ATTACK_LEFT_DOWN;
		else if ((py <= this->y + RED_FIRE_PLANT_SWITCH_ANI_Y) && (px <= this->x + RED_FIRE_PLANT_SWITCH_ANI_X))
			aniId = ID_ANI_RED_FIRE_PLANT_ATTACK_LEFT_UP;
		else if ((py > this->y + RED_FIRE_PLANT_SWITCH_ANI_Y) && (px > this->x + RED_FIRE_PLANT_SWITCH_ANI_X))
			aniId = ID_ANI_RED_FIRE_PLANT_ATTACK_RIGHT_DOWN;
		else if ((py <= this->y + RED_FIRE_PLANT_SWITCH_ANI_Y) && (px > this->x + RED_FIRE_PLANT_SWITCH_ANI_X))
			aniId = ID_ANI_RED_FIRE_PLANT_ATTACK_RIGHT_UP;
		break;
	case RED_FIRE_PLANT_STATE_POP_UP:
	case RED_FIRE_PLANT_STATE_POP_DOWN:
		if ((py > this->y + RED_FIRE_PLANT_SWITCH_ANI_Y) && (px <= this->x + RED_FIRE_PLANT_SWITCH_ANI_X))
			aniId = ID_ANI_RED_FIRE_PLANT_POP_UP_LEFT_DOWN;
		else if ((py <= this->y + RED_FIRE_PLANT_SWITCH_ANI_Y) && (px <= this->x + RED_FIRE_PLANT_SWITCH_ANI_X))
			aniId = ID_ANI_RED_FIRE_PLANT_POP_UP_LEFT_UP;
		else if ((py > this->y + RED_FIRE_PLANT_SWITCH_ANI_Y) && (px > this->x + RED_FIRE_PLANT_SWITCH_ANI_X))
			aniId = ID_ANI_RED_FIRE_PLANT_POP_UP_RIGHT_DOWN;
		else if ((py <= this->y + RED_FIRE_PLANT_SWITCH_ANI_Y) && (px > this->x + RED_FIRE_PLANT_SWITCH_ANI_X))
			aniId = ID_ANI_RED_FIRE_PLANT_POP_UP_RIGHT_UP;
		break;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	
	this->fireball->Render();
}

void CRedFirePlant::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CRedFirePlant::OnCollisionWith(LPCOLLISIONEVENT e) {

}

CRedFirePlant::CRedFirePlant() {
	this->player = new CMario();
	this->fireball = new CFireBall();
	
	this->start_x = 0.0f;
	this->start_y = 0.0f;
	this->idle_start = -1;
}

CRedFirePlant::CRedFirePlant(float x, float y, int object_type) : CGameObject(x, y, object_type) {
	this->player = new CMario();
	this->fireball = new CFireBall(x + RED_FIRE_PLANT_FIREBALL_OFFSET_X, y + RED_FIRE_PLANT_FIREBALL_OFFSET_Y, OBJECT_TYPE_FIREBALL);
	
	this->start_x = x;
	this->start_y = y;
	this->idle_start = -1;
	
	this->SetState(RED_FIRE_PLANT_STATE_IDLE);
}

void CRedFirePlant::SetState(int state) {
	CGameObject::SetState(state);
	switch (state) {
	case RED_FIRE_PLANT_STATE_POP_UP:
		vx = 0.0f;
		vy = -RED_FIRE_PLANT_POP_UP_SPEED;
		break;
	case RED_FIRE_PLANT_STATE_POP_DOWN:
		vx = 0.0f;
		vy = RED_FIRE_PLANT_POP_UP_SPEED;
		break;
	case RED_FIRE_PLANT_STATE_ATTACK:
		this->fireball->SetPosition(this->start_x + RED_FIRE_PLANT_FIREBALL_OFFSET_X, this->start_y + RED_FIRE_PLANT_FIREBALL_OFFSET_Y);
		this->fireball->SetState(FIREBALL_STATE_ATTACK);
		
		this->idle_start = GetTickCount64();
		this->vx = 0.0f;
		this->vy = 0.0f;
		break;
	case RED_FIRE_PLANT_STATE_IDLE:
		idle_start = GetTickCount64();
		vx = 0.0f;
		vy = 0.0f;
		break;
	}
}
