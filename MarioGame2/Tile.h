#pragma once

#include "GameObject.h"

class CTile : public CGameObject {
protected:
	int tileId;

public:
	CTile(float x, float y) : CGameObject(x, y) {};

	void Render();
	void Update(DWORD dt) {};
};
typedef CTile* LPTILE;

