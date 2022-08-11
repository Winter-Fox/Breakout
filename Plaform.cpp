#include "Plaform.h"

void Platform::move(float byX, float byY)
{
	center_.x += byX;
	center_.y += byY;
	border_.left += byX;
	border_.top += byY;
	border_.right += byX;
	border_.bottom += byY;
}

void Platform::draw(ID2D1HwndRenderTarget* pRenderTarget, ID2D1SolidColorBrush* pBrush)
{
	pBrush->SetColor(color_);
	pRenderTarget->FillRectangle(border_, pBrush);
}