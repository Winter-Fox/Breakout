#pragma once
#include "Object.h"
class Block : public Object
{
public:
	Block(D2D1_POINT_2F center, float width, float height, unsigned int strength, int points) :
		Object(center, width, height), 
		strength_(strength), points_(points)
	{
		// Init rectangle of a block
		border_.left = center_.x - (width_ / 2);
		border_.top = center_.y - (height_ / 2);
		border_.right = center_.x + (width_ / 2);
		border_.bottom = center_.y + (height_ / 2);

		// Set a color of a block based on how much strength it has
		switch (strength_) 
		{
		case 1:
			color_ = D2D1::ColorF(D2D1::ColorF::Brown);
			break;
		case 2:
			color_ = D2D1::ColorF(D2D1::ColorF::Orange);
			break;
		case 3:
			color_ = D2D1::ColorF(D2D1::ColorF::Red);
			break;
		default:
			color_ = D2D1::ColorF(D2D1::ColorF::Black);
			break;
		}
	};

	void draw(ID2D1HwndRenderTarget*, ID2D1SolidColorBrush*) override;
private:
	D2D1_RECT_F	   border_;
	unsigned int strength_;
	int			   points_;
};

