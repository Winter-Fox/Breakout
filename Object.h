#pragma once
#include <d2d1.h>
class Object
{
public:
	Object(D2D1_POINT_2F center, float width, float height) :
		center_(center), width_(width), 
		height_(height), color_(D2D1::ColorF(D2D1::ColorF::Black)) {};
	virtual void draw(ID2D1HwndRenderTarget*, ID2D1SolidColorBrush*) = 0;
protected:
	D2D1_POINT_2F center_;
	float width_, height_;
	D2D1_COLOR_F   color_;
};

struct MathVector
{
	float x, y;
};

