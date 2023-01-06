#include "Font.h"

CFont::CFont(float x, float y, int object_type, int type) : CGameObject(x, y, object_type) {
	this->type = type;
	this->visible = false;
}

void CFont::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
}

void CFont::Render() {
	int ani = -1;

	switch (type) {
	case 0:
		ani = ANI_ID_0;
		break;
	case 1:
		ani = ANI_ID_1;
		break;
	case 2:
		ani = ANI_ID_2;
		break;
	case 3:
		ani = ANI_ID_3;
		break;
	case 4:
		ani = ANI_ID_4;
		break;
	case 5:
		ani = ANI_ID_5;
		break;
	case 6:
		ani = ANI_ID_6;
		break;
	case 7:
		ani = ANI_ID_7;
		break;
	case 8:
		ani = ANI_ID_8;
		break;
	case 9:
		ani = ANI_ID_9;
		break;
	case 10:
		ani = ANI_ID_SPEED;
		break;
	case 11:
		ani = ANI_ID_FLYABLE;
		break;
	case 12:
		ani = ANI_ID_MUSHROOM;
		break;
	case 13:
		ani = ANI_ID_FLOWER;
		break;
	case 14:
		ani = ANI_ID_STAR;
		break;
	}

	if (visible && (type != -1))
		CAnimations::GetInstance()->Get(ani)->Render(x, y);
}

void CFont::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	switch (type)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
		left = x - FONT_BBOX_WIDTH / 2;
		top = y - FONT_BBOX_HEIGHT / 2;
		right = left + FONT_BBOX_WIDTH;
		bottom = top + FONT_BBOX_HEIGHT;
		break;
	case 12:
	case 13:
	case 14:
		left = x - ITEM_SIZE / 2;
		top = y - ITEM_SIZE / 2;
		right = left + ITEM_SIZE;
		bottom = top + ITEM_SIZE;
		break;
	}
}