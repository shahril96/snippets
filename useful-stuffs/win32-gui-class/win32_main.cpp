
#include <windows.h>

#include "win32_class.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    
    win32_class winClass("SimpleExample");
    
    if(!winClass.createWindow(hInstance, "Hello World!", nCmdShow)) {
        MessageBox(NULL, "Window generation failed!", "Error", MB_ICONWARNING);
        return 0;
    }
    
    MSG msg;
    
    while(msg.message != WM_QUIT) {
        if(PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
}