#include "Ball.h"

void Ball::move(float byX, float byY) 
{
	ellipse_.point.x += byX;
	ellipse_.point.y += byY;
}

void Ball::draw(ID2D1HwndRenderTarget* pRenderTarget, ID2D1SolidColorBrush* pBrush)
{
	pBrush->SetColor(color_);
	pRenderTarget->FillEllipse(ellipse_, pBrush);
}

Object* collisionWith(std::vector<std::unique_ptr<Object>> sceneObjects) 
{
	for (int i = 0; i < sceneObjects.size(); i++)
	{

	}
}