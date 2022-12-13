#include "ColorBox.h"

void CColorBox::GetBoundingBox(float& l, float& t, float& r, float& b) {
	l = x - COLOR_BOX_BBOX_WIDTH / 2;
	t = y - COLOR_BOX_BBOX_HEIGHT / 2;
	r = l + COLOR_BOX_BBOX_WIDTH;
	b = t + COLOR_BOX_BBOX_HEIGHT;
}

void CColorBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	float px, py;
	player->GetPosition(px, py);

	// if player is under color box, set isBlocking = 0
	if (py > this->y) isBlocking = 0;
	else isBlocking = 1;

	CGameObject::Update(dt, coObjects);
}

void CColorBox::Render() {
	CSprites* s = CSprites::GetInstance();
	s->Get(this->spriteId)->Draw(x, y);
}
