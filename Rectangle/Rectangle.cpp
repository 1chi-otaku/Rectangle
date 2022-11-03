

#include "framework.h"
#include "Rectangle.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_RECTANGLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RECTANGLE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor        = NULL;
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON2));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HCURSOR hcur1 = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR1));
    HCURSOR hcur2 = LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR2));
    TCHAR str[50];
    switch (message)
    {
    case WM_MOUSEMOVE: {
        RECT rect;
        GetClientRect(hWnd, &rect);
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        if (x >= 10 && x <= rect.right-10 &&
            y >= 10 && y <= rect.bottom-10) {
            SetCursor(hcur1);
        }
        else {
            SetCursor(hcur2);
        }
        break;
    }
    case WM_LBUTTONDOWN: {
        RECT rect;
        GetClientRect(hWnd, &rect);
        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        if (x > 10 && x < rect.right - 10 &&
            y > 10 && y < rect.bottom - 10) {
            wsprintf(str, TEXT("Inside"));
        }
        else if (x == 10 || x == rect.right - 10 ||
            y == 10 || y == rect.bottom - 10) {
            wsprintf(str, TEXT("Frontier"));
        }
        else {
            wsprintf(str, TEXT("Outside"));
        }
        SetWindowText(hWnd, str);
        break;
    }
    case WM_RBUTTONDOWN: {
        RECT rect;
        GetClientRect(hWnd, &rect);
        wsprintf(str, TEXT("X=%d  Y=%d"), rect.right, rect.bottom);
        SetWindowText(hWnd, str);
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

