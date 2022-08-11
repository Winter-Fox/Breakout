#include "Block.h"

void Block::draw(ID2D1HwndRenderTarget* pRenderTarget, ID2D1SolidColorBrush* pBrush) 
{
	pBrush->SetColor(color_);
	pRenderTarget->FillRectangle(border_, pBrush);
	pBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
	pRenderTarget->DrawRectangle(border_, pBrush);
}