#pragma once

#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include <vector>
#include <memory>

#include "BaseWindow.h"
#include "Block.h"
#include "Ball.h"
#include "Plaform.h"

template <class T> void SafeRelease(T** ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = NULL;
    }
}

class MainWindow : public BaseWindow<MainWindow>
{
    ID2D1Factory* pFactory;
    ID2D1HwndRenderTarget* pRenderTarget;
    ID2D1SolidColorBrush* pBrush;
    D2D1_ELLIPSE            ellipse;

    void    CalculateLayout();
    HRESULT CreateGraphicsResources();
    void    DiscardGraphicsResources();
    void    OnPaint();
    void    Resize();
    void    OnKeyDown(UINT key);
    void    MoveObject(MovableObject* object, float byX, float byY);

    std::vector<std::unique_ptr<Object>> sceneObjects_;
    std::unique_ptr<Ball> ball_;
    std::unique_ptr<Platform> platform_;

    float plaformSpeed_ = 5.0f;
public:

    MainWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL)
    {
    }

    PCWSTR  ClassName() const { return L"Circle Window Class"; }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};
