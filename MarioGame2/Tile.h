#pragma once

#include "GameObject.h"

#define TILE_WIDTH 16
#define TILE_HEIGHT 16

class CTile : public CGameObject {
protected:
	int length;
	float cellWidth, cellHeight;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;

public:
	CTile(float x, float y, int object_type,
		float cell_width, float cell_height, int length,
		int spriteIdBegin, int spriteIdMiddle, int spriteIdEnd) : CGameObject(x, y, object_type)
	{
		this->length = length;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdBegin = spriteIdBegin;
		this->spriteIdMiddle = spriteIdMiddle;
		this->spriteIdEnd = spriteIdEnd;
	}

	void Render();
	void Update(DWORD dt) {};
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void RenderBoundingBox();
};
typedef CTile* LPTILE;

