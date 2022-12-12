#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_QUESTION_BOX 280000

#define QUESTION_BRICK_WIDTH 16
#define QUESTION_BRICK_BBOX_WIDTH 16
#define QUESTION_BRICK_BBOX_HEIGHT 16

class CQuestionBrick : public CGameObject {
public:
	CQuestionBrick(float x, float y) : CGameObject(x, y) {}
	void Render();
	void Update();
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};