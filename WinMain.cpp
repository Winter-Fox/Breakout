#include "GameWindow.h"

// 
void MainWindow::CalculateLayout()
{
    if (pRenderTarget != NULL)
    {
        D2D1_SIZE_F size = pRenderTarget->GetSize();
        // Create blocks
        const int colBlockNum = 10;
        const int rowBlockNum = 4;
        const float blockWidth = size.width / colBlockNum;
        const float blockHeight = size.height / 25;
        for (int row = 0; row < rowBlockNum; row++) 
        {
            for (int col = 0; col < colBlockNum; col++) 
            {
                D2D1_POINT_2F blockCenter = D2D1::Point2F((col+1)*blockWidth - (blockWidth/2), 
                    (row+1)*blockHeight - (blockHeight/2));
                std::unique_ptr<Object> newBlock = std::make_unique<Block>(blockCenter, blockWidth, blockHeight,
                    1, 100);
                sceneObjects_.push_back(std::move(newBlock));
            }
        }

        // Create platform
        D2D1_POINT_2F platformCenter = D2D1::Point2F(size.width / 2, size.height - 2 * size.height/25);
        platform_ = std::make_unique<Platform>(platformCenter, size.width / 8, size.height / 25);

        //Create ball
        D2D1_POINT_2F ballCenter = platformCenter;
        float radius = min(size.height, size.width) / 30;
        ballCenter.y -= 250.0f;
        ball_ = std::make_unique<Ball>(ballCenter, radius);
    }
}

HRESULT MainWindow::CreateGraphicsResources()
{
    HRESULT hr = S_OK;
    if (pRenderTarget == NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        hr = pFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &pRenderTarget);

        if (SUCCEEDED(hr))
        {
            const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0);
            hr = pRenderTarget->CreateSolidColorBrush(color, &pBrush);

            if (SUCCEEDED(hr))
            {
                CalculateLayout();
            }
        }
    }
    return hr;
}

void MainWindow::DiscardGraphicsResources()
{
    SafeRelease(&pRenderTarget);
    SafeRelease(&pBrush);
}

void MainWindow::OnPaint()
{
    HRESULT hr = CreateGraphicsResources();
    if (SUCCEEDED(hr))
    {
        PAINTSTRUCT ps;
        BeginPaint(m_hwnd, &ps);

        pRenderTarget->BeginDraw();

        pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
        for (int i = 0; i < sceneObjects_.size(); i++) 
        {
            sceneObjects_[i]->draw(pRenderTarget, pBrush);
        }
        ball_->draw(pRenderTarget, pBrush);
        platform_->draw(pRenderTarget, pBrush);

        hr = pRenderTarget->EndDraw();
        if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
        {
            DiscardGraphicsResources();
        }
        EndPaint(m_hwnd, &ps);
    }
}

void MainWindow::Resize()
{
    if (pRenderTarget != NULL)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        pRenderTarget->Resize(size);
        CalculateLayout();
        InvalidateRect(m_hwnd, NULL, FALSE);
    }
}

void MainWindow::MoveObject(MovableObject* object, float byX, float byY)
{
    object->move(byX, byY);
    InvalidateRect(m_hwnd, NULL, FALSE);
}

void MainWindow::OnKeyDown(UINT key) 
{
    switch (key)
    {
    case 0x41:
    case VK_LEFT:
        MoveObject(platform_.get(), -1 * plaformSpeed_, 0);
        break;
    case 0x44:
    case VK_RIGHT:
        MoveObject(platform_.get(), 1 * plaformSpeed_, 0);
        break;
    case 0x57:
    case VK_UP:
        MoveObject(platform_.get(), 0, -1 * plaformSpeed_);
        break;
    case 0x53:
    case VK_DOWN:
        MoveObject(platform_.get(), 0, 1 * plaformSpeed_);
        break;
    }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
    MainWindow win;

    if (!win.Create(L"Circle", WS_OVERLAPPED))
    {
        return 0;
    }

    ShowWindow(win.Window(), SW_MAXIMIZE);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        if (FAILED(D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
        {
            return -1;  // Fail CreateWindowEx.
        }
        return 0;

    case WM_DESTROY:
        DiscardGraphicsResources();
        SafeRelease(&pFactory);
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        OnPaint();
        return 0;

    case WM_SIZE:
        Resize();
        return 0;

    case WM_KEYDOWN:
        OnKeyDown((UINT)wParam);
        return 0;
    }
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}