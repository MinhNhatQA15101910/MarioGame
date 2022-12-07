#pragma once

#include "GameObject.h"

enum TILE_TYPE { SINGLE = 0, MULTIPLE = 1 };

class CTile : public CGameObject {
protected:
	int tileId;
	int length;
	int spriteIdBegin, spriteIdMiddle, spriteIdEnd;

public:
	CTile() {
		tileId = 0;
		length = 0;
		spriteIdBegin = spriteIdMiddle = spriteIdEnd = 0;
	}

	CTile(float x, float y, int tileId) : CGameObject(x, y) {
		this->tileId = tileId;
		length = 0;
		spriteIdBegin = spriteIdMiddle = spriteIdEnd = 0;
	};

	CTile(float x, float y, int length, int spriteIdBegin, int spriteIdMiddle, int spriteIdEnd) {
		this->tileId = 0;
		
		this->length = length;
		this->spriteIdBegin = spriteIdBegin;
		this->spriteIdMiddle = spriteIdMiddle;
		this->spriteIdEnd = spriteIdEnd;
	}

	void Render();
	void Update(DWORD dt) {};
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
typedef CTile* LPTILE;

