#include "QuestionBrick.h"

void CQuestionBrick::Render() {
	int aniId = ID_ANI_QUESTION_BOX_FULL;
	if (state == QUESTION_BOX_STATE_EMPTY)
		aniId = ID_ANI_QUESTION_BOX_EMPTY;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CQuestionBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	if (!this->subObj->IsDeleted()) {
		if (dynamic_cast<CCoinItem*>(this->subObj)) {
			CCoinItem* ci = dynamic_cast<CCoinItem*>(this->subObj);

			float itx, ity;
			ci->GetPosition(itx, ity);

			if (state == QUESTION_BOX_STATE_EMPTY && ity >= this->y - COIN_ITEM_HEIGHT && ci->IsCoinJump())
				ci->Delete();
		}
		else if (dynamic_cast<CRedMushroomItem*>(this->subObj)) {
			CRedMushroomItem* rmi = dynamic_cast<CRedMushroomItem*>(this->subObj);

			float itx, ity;
			rmi->GetPosition(itx, ity);

			if (rmi->GetState() == RED_MUSHROOM_ITEM_STATE_POP_UP && ity + RED_MUSHROOM_ITEM_HEIGHT <= this->y)
				rmi->SetState(RED_MUSHROOM_ITEM_STATE_RUNNING);
		}
	}

	CGameObject::Update(dt, coObjects);
}

void CQuestionBrick::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x - QUESTION_BRICK_BBOX_WIDTH / 2;
	t = y - QUESTION_BRICK_BBOX_HEIGHT / 2;
	r = l + QUESTION_BRICK_BBOX_WIDTH;
	b = t + QUESTION_BRICK_BBOX_HEIGHT;
}

void CQuestionBrick::SetState(int state) {
	CGameObject::SetState(state);
}

void CQuestionBrick::OnCollisionWith(LPCOLLISIONEVENT e) {
	
}
