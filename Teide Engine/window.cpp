#include "window.h"

// Windows Procedure:
// Event -> PeekMessage -> DispatchMessage -> WindowProc
// Events are handled using messages 


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 2));

        EndPaint(hWnd, &ps);
        return 0;
    }
    // Keep WM_PANT until DirectX12 is set up 
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

window::window()
    : m_hInstance(GetModuleHandle(nullptr))
{
    const wchar_t* CLASS_NAME = L"TEIDE ENGINE";

    WNDCLASSEX wndClass = {};
    wndClass.cbSize = sizeof(WNDCLASSEX);
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WindowProc;
    wndClass.hInstance = m_hInstance;
    wndClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
    wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wndClass.lpszClassName = CLASS_NAME;

    if (!RegisterClassEx(&wndClass))
    {
        MessageBox(nullptr, L"Failed to register window class", L"Error", MB_OK);
        return;
    }

    DWORD style = WS_OVERLAPPEDWINDOW;

    int width = 640;
    int height = 480;

    RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, style, FALSE);

    m_hWnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Title",
        style,
        250, 250,
        rect.right - rect.left,
        rect.bottom - rect.top,
        nullptr,
        nullptr,
        m_hInstance,
        nullptr
    );

    if (!m_hWnd)
    {
        MessageBox(nullptr, L"Failed to create window", L"Error", MB_OK);
        return;
    }

    ShowWindow(m_hWnd, SW_SHOW);
}

window::~window()
{
    const wchar_t* CLASS_NAME = L"TEIDE ENGINE";

    UnregisterClass(CLASS_NAME, m_hInstance);
}

bool window::ProcessMessages()
{
    MSG msg = {};

    while(PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
        return false;
        }


        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}

HWND window::GetHWND() const
{
    return m_hWnd;
}


