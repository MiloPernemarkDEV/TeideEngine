#include "window.h"

// Windows Procedure:
// Event -> PeekMessage -> DispatchMessage -> WindowProc
// Events are handled using messages 

static void CenterWindow(HWND hWnd, int width, int height)
{
    RECT rc = { 0, 0, width, height };
    DWORD style = (DWORD)GetWindowLongPtr(hWnd, GWL_STYLE);
    AdjustWindowRect(&rc, style, FALSE);

    int winWidth = rc.right - rc.left;
    int winHeight = rc.bottom - rc.top;

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    int x = (screenWidth - winWidth) / 2;
    int y = (screenHeight - winHeight) / 2;

    SetWindowPos(hWnd, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

static void SetWindowSize(HWND hWnd, int width, int height)
{
    // Get monitor work area (excluding taskbar)
    HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi = { sizeof(mi) };
    GetMonitorInfo(monitor, &mi);

    int screenW = mi.rcWork.right - mi.rcWork.left;
    int screenH = mi.rcWork.bottom - mi.rcWork.top;

    // Clamp width/height to screen size
    width = min(width, screenW);
    height = min(height, screenH);

    DWORD style = (DWORD)GetWindowLongPtr(hWnd, GWL_STYLE);

    RECT rect = { 0, 0, width, height };
    AdjustWindowRect(&rect, style, FALSE);

    int winWidth = rect.right - rect.left;
    int winHeight = rect.bottom - rect.top;

    int x = mi.rcWork.left + (screenW - winWidth) / 2;
    int y = mi.rcWork.top + (screenH - winHeight) / 2;

    SetWindowPos(
        hWnd,
        nullptr,
        x, y,
        winWidth, winHeight,
        SWP_NOZORDER
    );
}



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
        L"TeideEngine",
        style,
        250, 250,
        rect.right - rect.left,
        rect.bottom - rect.top,
        nullptr,
        nullptr,
        m_hInstance,
        nullptr
    );

        CenterWindow(m_hWnd, width, height);


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


