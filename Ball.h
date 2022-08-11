#pragma once

#include <vector>
#include <memory>

#include "MovableObject.h"
#include "Block.h"

class Ball : public MovableObject
{
public:
	Ball(D2D1_POINT_2F center, float radius) : MovableObject(center, radius, radius)
	{
		ellipse_.point = center;
		ellipse_.radiusX = radius;
		ellipse_.radiusY = radius;
		color_ = D2D1::ColorF(D2D1::ColorF::Pink);
		acceleration_ = { 0, -1 };
	};

	Object* collisionWith(std::vector<std::unique_ptr<Object>> sceneObjects);

	void move(float byX, float byY) override;
	void draw(ID2D1HwndRenderTarget*, ID2D1SolidColorBrush*) override;

private:
	D2D1_ELLIPSE ellipse_;
	MathVector acceleration_;
};


