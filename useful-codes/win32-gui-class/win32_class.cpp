
#include "win32_class.h"

bool win32_class::createWindow(HINSTANCE hInstance, LPCSTR winText, int nCmdShow) {
    
    // create a window class with minimum requirement
    WNDCLASSEX wndc = {0};
    wndc.lpszClassName = className; // class name
    wndc.lpfnWndProc = wndProcedure;
    wndc.hInstance = hInstance;
    wndc.cbSize = sizeof(WNDCLASSEX);
    
    // register the window class
    if(!RegisterClassEx(&wndc)) {
        return false;
    }
    
    m_hwnd = CreateWindowEx(
                0,
                className, // class name
                winText, // by default title text
                WS_OVERLAPPEDWINDOW, // combination of style to make a default window

                // use default positioning
                CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            
                NULL, // parent
                NULL, // menu
                hInstance, // window handle instance
                NULL);
    
    if(!m_hwnd) {
        return false;
    }
    
    ShowWindow(m_hwnd, nCmdShow);
    
    return true;
}

LRESULT CALLBACK win32_class::wndProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    
    switch(message) {
        
        case WM_DESTROY:
            PostQuitMessage(WM_QUIT);
            break;
            
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = hdc = BeginPaint(hWnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) GetStockObject(DKGRAY_BRUSH));
            EndPaint(hWnd, &ps);
            break;
        }
        
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
}