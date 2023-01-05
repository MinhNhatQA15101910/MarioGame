#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "RedMushroomItem.h"
#include "GreenMushroomItem.h"
#include "LeafItem.h"
#include "QuestionBrick.h"
#include "RedFirePlant.h"
#include "GreenFirePlant.h"
#include "GreenPlant.h"
#include "FireBall.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (x <= MARIO_START_X) x = MARIO_START_X;
	if (x >= MARIO_END_X) x = MARIO_END_X;

	if (abs(vx) > abs(maxVx)) vx = maxVx;

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	isOnPlatform = false;

	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CQuestionBrick*>(e->obj))
		OnCollisionWithQuestionBrick(e);
	else if (dynamic_cast<CLeafItem*>(e->obj))
		OnCollisionWithLeafItem(e);
	else if (dynamic_cast<CRedFirePlant*>(e->obj))
		OnCollisionWithRedFirePlant(e);
	else if (dynamic_cast<CGreenFirePlant*>(e->obj))
		OnCollisionWithGreenFirePlant(e);
	else if (dynamic_cast<CGreenPlant*>(e->obj))
		OnCollisionWithGreenPlant(e);
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);

			float goombaX, goombaY;
			goomba->GetPosition(goombaX, goombaY);
			goomba->GetScore()->SetStartX(goombaX);
			goomba->GetScore()->SetStartY(goombaY);
			goomba->GetScore()->SetState(SCORE_STATE_POP_UP);

			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					level = MARIO_LEVEL_SMALL;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				}
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

void CMario::OnCollisionWithQuestionBrick(LPCOLLISIONEVENT e) {
	CQuestionBrick* qb = dynamic_cast<CQuestionBrick*>(e->obj);

	if (e->ny > 0) {
		qb->SetState(QUESTION_BOX_STATE_EMPTY);
		if (!qb->GetSubObj()->IsDeleted()) {

			if (qb->GetItemType() == ITEM_TYPE_COIN) {
				qb->GetSubObj()->SetState(COIN_STATE_JUMP);
				coin++;
			}
			else if (qb->GetItemType() == ITEM_TYPE_GREEN_MUSHROOM) {
				qb->GetSubObj()->SetState(GREEN_MUSHROOM_ITEM_STATE_POP_UP);
			}
			else if (qb->GetItemType() == ITEM_TYPE_RED_MUSHROOM_LEAF) {
				if (this->level == MARIO_LEVEL_SMALL) {
					qb->GetSubObj()->SetState(RED_MUSHROOM_ITEM_STATE_POP_UP);
					qb->GetSubObj2()->Delete();
				}
				else if (this->level == MARIO_LEVEL_BIG) {
					qb->GetSubObj2()->SetState(LEAF_ITEM_STATE_POP_UP);
					qb->GetSubObj()->Delete();
				}
			}
		}
	}
}

void CMario::OnCollisionWithRedMushroomItem(LPCOLLISIONEVENT e) {
	CRedMushroomItem* rmi = dynamic_cast<CRedMushroomItem*>(e->obj);

	if (rmi->GetState() == RED_MUSHROOM_ITEM_STATE_RUNNING) 
	{
		rmi->SetState(RED_MUSHROOM_ITEM_STATE_DISAPPEAR);
		rmi->GetScore()->SetState(SCORE_STATE_POP_UP);
		SetLevel(MARIO_LEVEL_BIG);
	}
}

void CMario::OnCollisionWithGreenMushroomItem(LPCOLLISIONEVENT e) {
	CGreenMushroomItem* gmi = dynamic_cast<CGreenMushroomItem*>(e->obj);

	if (gmi->GetState() == GREEN_MUSHROOM_ITEM_STATE_RUNNING)
	{
		e->obj->Delete();
	}
}

void CMario::OnCollisionWithLeafItem(LPCOLLISIONEVENT e) {
	CLeafItem* li = dynamic_cast<CLeafItem*>(e->obj);

	if (li->GetState() == LEAF_ITEM_STATE_FALLING_LEFT ||
		li->GetState() == LEAF_ITEM_STATE_FALLING_RIGHT
		)
	{
		li->SetState(LEAF_ITEM_STATE_DISAPPEAR);

		float liX, liY;
		li->GetPosition(liX, liY);
		li->GetScore()->SetStartX(liX);
		li->GetScore()->SetStartY(liY);
		li->GetScore()->SetState(SCORE_STATE_POP_UP);

		this->level = MARIO_LEVEL_TANOOKI;
	}
}

void CMario::OnCollisionWithRedFirePlant(LPCOLLISIONEVENT e) {
	if (e->obj->GetState() != RED_FIRE_PLANT_STATE_IDLE) {
		if (untouchable == 0)
		{
			if (level > MARIO_LEVEL_SMALL)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
	}
}

void CMario::OnCollisionWithGreenFirePlant(LPCOLLISIONEVENT e) {
	if (e->obj->GetState() != GREEN_FIRE_PLANT_STATE_IDLE) {
		if (untouchable == 0)
		{
			if (level > MARIO_LEVEL_SMALL)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
	}
}

void CMario::OnCollisionWithGreenPlant(LPCOLLISIONEVENT e) {
	if (e->obj->GetState() != GREEN_PLANT_STATE_IDLE_BOTTOM) {
		if (untouchable == 0)
		{
			if (level > MARIO_LEVEL_SMALL)
			{
				level = MARIO_LEVEL_SMALL;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);
			}
		}
	}
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}

int CMario::GetAniIdTanooki()
{
	int aniId = -1;
	if (state == MARIO_STATE_MAP || state == MARIO_STATE_MAP_TRANS)
		aniId = ID_ANI_MARIO_TANOOKI_MAP;
	else if (!isOnPlatform)
	{
		if (isFlying)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_TANOOKI_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_TANOOKI_JUMP_RUN_LEFT;
		}
		else if (abs(ax) == MARIO_ACCEL_RUN_X || vx != 0.0f)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_TANOOKI_LANDING_RIGHT;
			else
				aniId = ID_ANI_MARIO_TANOOKI_LANDING_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_TANOOKI_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_TANOOKI_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_TANOOKI_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_TANOOKI_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (hittable)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_TANOOKI_HIT_RIGHT;
					else aniId = ID_ANI_MARIO_TANOOKI_HIT_LEFT;
				}
				else if (isCarrying == false)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_TANOOKI_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_TANOOKI_IDLE_LEFT;
				}
				else
				{
					if (nx > 0) aniId = ID_ANI_MARIO_TANOOKI_CARRY_RIGHT_IDLE;
					else aniId = ID_ANI_MARIO_TANOOKI_CARRY_LEFT_IDLE;
				}
			}
			else if (vx > 0)
			{
				if (hittable)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_TANOOKI_HIT_RIGHT;
					else aniId = ID_ANI_MARIO_TANOOKI_HIT_LEFT;
				}
				else if (ax < 0)
					aniId = ID_ANI_MARIO_TANOOKI_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X && isCarrying == true)
					aniId = ID_ANI_MARIO_TANOOKI_CARRY_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X && vx == maxVx)
					aniId = ID_ANI_MARIO_TANOOKI_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X || vx != maxVx)
				{
					if (kickable)
						aniId = ID_ANI_MARIO_TANOOKI_KICK_RIGHT;
					else
						aniId = ID_ANI_MARIO_TANOOKI_WALKING_RIGHT;
				}
			}
			else // vx < 0
			{
				if (hittable)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_TANOOKI_HIT_RIGHT;
					else aniId = ID_ANI_MARIO_TANOOKI_HIT_LEFT;
				}
				else if (ax > 0)
					aniId = ID_ANI_MARIO_TANOOKI_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X && isCarrying == true)
					aniId = ID_ANI_MARIO_TANOOKI_CARRY_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X && abs(vx) == abs(maxVx))
					aniId = ID_ANI_MARIO_TANOOKI_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X || vx != -maxVx)
				{
					if (kickable)
						aniId = ID_ANI_MARIO_TANOOKI_KICK_LEFT;
					else
						aniId = ID_ANI_MARIO_TANOOKI_WALKING_LEFT;
				}
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_TANOOKI_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
				else if (ax == MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (ax == MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
					aniId = ID_ANI_MARIO_BRACE_LEFT;
				else if (ax == -MARIO_ACCEL_RUN_X)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (ax == -MARIO_ACCEL_WALK_X)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_TANOOKI)
		aniId = GetAniIdTanooki();

	animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return;

	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == MARIO_STATE_MAP) {
		left = x - MARIO_MAP_SIZE / 2;
		top = y - MARIO_MAP_SIZE / 2;
		right = left + MARIO_MAP_SIZE;
		bottom = top + MARIO_MAP_SIZE;
	}
	else if (level == MARIO_LEVEL_TANOOKI) {
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_TANOOKI_BBOX_WIDTH / 2;
			top = y - MARIO_TANOOKI_BBOX_HEIGHT / 2;
			right = left + MARIO_TANOOKI_BBOX_WIDTH;
			bottom = top + MARIO_TANOOKI_BBOX_HEIGHT;
		}
	}
	if (level == MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

