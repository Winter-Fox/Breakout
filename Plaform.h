#pragma once
#include "MovableObject.h"
class Plaform : public MovableObject
{
public:
	Plaform(D2D1_POINT_2F center, float width, float height) : MovableObject(center, width, height) 
	{
		border_.left = center_.x - (width_ / 2);
		border_.top = center_.y - (height_ / 2);
		border_.right = center_.x + (width_ / 2);
		border_.bottom = center_.y + (height_ / 2);
		color_ = D2D1::ColorF(D2D1::ColorF::Green);
	};
private:
	D2D1_RECT_F border_;
};

