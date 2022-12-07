#pragma once

#include "GameObject.h"

class CTile : public CGameObject {
protected:
	int tileId;

public:
	CTile() {}

	CTile(float x, float y, int tileId) : CGameObject(x, y) {
		this->tileId = tileId;
	};

	void Render();
	void Update(DWORD dt) {};
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
typedef CTile* LPTILE;

