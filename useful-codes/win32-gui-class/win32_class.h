
#ifndef WIN32_CLASS_H
#define WIN32_CLASS_H

#include <windows.h>

class win32_class {
    
public:
    
    win32_class(LPCSTR cName) : className(cName) {}
    bool createWindow(HINSTANCE hInstance, LPCSTR winText, int nCmdShow);
    
private:
    
    LPCSTR className;
    HWND m_hwnd;
    
    static LRESULT CALLBACK wndProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

#endif /* WIN32_CLASS_H */

