#include "FireBall.h"

#include <cmath>

void CFireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x - FIREBALL_BBOX_WIDTH / 2;
	top = y - FIREBALL_BBOX_HEIGHT / 2;
	right = left + FIREBALL_BBOX_WIDTH;
	bottom = top + FIREBALL_BBOX_HEIGHT;
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (state == FIREBALL_STATE_IDLE) {
		this->x = start_x;
		this->y = start_y;
	}
	
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFireBall::Render() {
	if (state == FIREBALL_STATE_ATTACK)
		CAnimations::GetInstance()->Get(ID_ANI_FIREBALL_ATTACK)->Render(x, y);
}

void CFireBall::OnNoCollision(DWORD dt) {
	x += vx * dt;
	y += vy * dt;
}

void CFireBall::OnCollisionWith(LPCOLLISIONEVENT e) {
	if (e->obj->IsBlocking()) {
		this->SetState(FIREBALL_STATE_IDLE);
	}

	if (dynamic_cast<CMario*>(e->obj)) {
		if (this->player->GetUntouchable() == 0)
		{
			this->SetState(FIREBALL_STATE_IDLE);

			if (player->GetLevel() > MARIO_LEVEL_SMALL)
			{
				player->SetLevel(MARIO_LEVEL_SMALL);
				player->StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				player->SetState(MARIO_STATE_DIE);
			}
		}
	}
}

CFireBall::CFireBall() {
	this->start_x = 0.0f;
	this->start_y = 0.0f;
	this->player = new CMario();
}

CFireBall::CFireBall(float x, float y, int object_type) : CGameObject(x, y, object_type) {
	this->player = new CMario();
	this->start_x = x;
	this->start_y = y;
	this->SetState(FIREBALL_STATE_IDLE);
}

void CFireBall::SetState(int state) {
	CGameObject::SetState(state);

	switch (state) {
	case FIREBALL_STATE_IDLE:
		this->vx = 0.0f;
		this->vy = 0.0f;
		break;
	case FIREBALL_STATE_ATTACK:
		float px, py;
		this->player->GetPositionCenter(px, py);

		float fx = this->x + FIREBALL_WIDTH / 2;
		float fy = this->y + FIREBALL_HEIGHT / 2;

		float distance = sqrt((fx - px) * (fx - px) + (fy - py) * (fy - py));
		float distance_x = abs(fx - px);
		float distance_y = abs(fy - py);

		if ((px >= fx) && (py >= fy)) {
			this->vx = distance_x * FIREBALL_MOVING_SPEED / distance;
			this->vy = distance_y * FIREBALL_MOVING_SPEED / distance;
		}
		else if ((px < fx) && (py >= fy)) {
			this->vx = -distance_x * FIREBALL_MOVING_SPEED / distance;
			this->vy = distance_y * FIREBALL_MOVING_SPEED / distance;
		}
		else if ((px >= fx) && (py < fy)) {
			this->vx = distance_x * FIREBALL_MOVING_SPEED / distance;
			this->vy = -distance_y * FIREBALL_MOVING_SPEED / distance;
		}
		else if ((px < fx) && (py < fy)) {
			this->vx = -distance_x * FIREBALL_MOVING_SPEED / distance;
			this->vy = -distance_y * FIREBALL_MOVING_SPEED / distance;
		}

		break;
	}

}
