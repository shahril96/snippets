#include <Windows.h>

// function prototype
LRESULT CALLBACK wndProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// constant
LPCTSTR NAME = "My Window";

/**
 * 
 * WINAPI - typedef for __stdcall calling convention
 *          by default Windows uses this convention
 * @param hInstance - handle to our current window instance
 * @param prevInstance - uses only by 16-bit application
 * @param cmdLine - arguments if this program called by the command line
 * @param cmdShow - flags if it shoulds run in minimize, maximize or normal
 * @return 
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    /*
     * WNDCLASSEX structure - windows class information
     *                        uses by RegisterClass or RegisterClassEx
     * 
     * @reference - https://msdn.microsoft.com/en-us/library/windows/desktop/ms633577(v=vs.85).aspx
     * 
     */
    WNDCLASSEX wndClass;

    // handle - uses by Windows API
    HWND hWnd;

    /*
     * MSG structure - contains message from thread's message queue
     *                 use by ...
     * @reference - https://msdn.microsoft.com/en-us/library/windows/desktop/ms644958(v=vs.85).aspx
     */
    MSG msg;

    /*
     * Populate window class before registering
     * 
     * @reference - https://msdn.microsoft.com/en-us/library/windows/desktop/ms633577(v=vs.85).aspx
     * 
     */

    // cbSize = size of this struct
    // - it is used in struct versioning, as there is two difference functions which
    //   is WNDCLASS & WNDCLASSEX 
    wndClass.cbSize = sizeof (WNDCLASSEX);
    wndClass.cbClsExtra = 0; // extra memory allocated - set = 0
    wndClass.hInstance = hInstance; // instance of our window
    wndClass.cbWndExtra = 0; // extra mem for windows - set = 0
    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = wndProcedure; // callback for managing messages
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // set icon
    wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // set small icon
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW); // set cursor
    wndClass.hbrBackground = NULL; // set background color
    // if we want `menu` in our program
    // currently we don't want any, so set it to null
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = NAME; // set our window name

    /*
     * register our window class
     * 
     * @reference - https://msdn.microsoft.com/en-us/library/windows/desktop/ms633587(v=vs.85).aspx
     * 
     */
    if (!RegisterClassEx(&wndClass)) {
        return 1;
    }

    /*
     * Create our Window
     * 
     * Parameters :
     * @lpClassName = NAME - previous one identifier from RegisterClassEx
     * @lpWindowName = "Hello, World!" - top window title
     * @dwStyle = WS_OVERLAPPEDWINDOW - style to use, currently using overlapped window
     * @x = CW_USEDEFAULT - initial x position
     * @y = CW_USEDEFAULT - initial y position
     * @nWidth = CW_USEDEFAULT - width of window
     * @nHeight = CW_USEDEFAULT - height of window
     * @hWndParent = NULL - handle to parent of this window, in our case, NULL
     * @hMenu = NULL - handle to the menu, we got none then NULL
     * @hInstance = hInstance - handle of our current window
     * @lpParam = NULL - pointer passed if created from CREATESTRUCT(), we got none then NULL
     * 
     * @reference - https://msdn.microsoft.com/en-us/library/windows/desktop/ms632679(v=vs.85).aspx
     * 
     */
    hWnd = CreateWindow(NAME, "Hello, World!", WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            NULL, NULL, hInstance, NULL);

    // if creation of window failed, then terminate the program
    if (!hWnd) {
        return 1;
    }

    /*
     * by default window is hidden, then make it appear (SW_SHOW)
     * 
     * @reference - https://msdn.microsoft.com/en-us/library/windows/desktop/ms633548(v=vs.85).aspx
     * 
     */
    ShowWindow(hWnd, nCmdShow);

    // loop until WM_QUIT message is given to application
    while (msg.message != WM_QUIT) {

        /*
         * Retrieve message from thread's message queue 
         * 
         * Parameters:
         * @lpMsg = &msg - MSG struct where data will be stored
         * @hWnd = NULL - specify which window to process, NULL is for all
         * @wMsgFilterMin = 0 - specify minimum range of message to be retrieved
         * @wMsgFilterMax = 0 - specify maximum range of message to be retrieved
         *                    - if both wMsgFilterM* is 0, then all msgs will be retrieved
         * @wRemoveMsg = PM_REMOVE - remove message from thread's message queue
         * 
         * @return - non-zero if message retrieved
         * 
         * @reference - https://msdn.microsoft.com/en-us/library/windows/desktop/ms644943(v=vs.85).aspx
         */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0) {

            /*
             * translate virtual-key message into character message
             * 
             * @reference - https://msdn.microsoft.com/en-us/library/windows/desktop/ms644955(v=vs.85).aspx
             * @implementation - https://source.winehq.org/git/wine.git/blob/HEAD:/dlls/user32/message.c#l3864
             */
            TranslateMessage(&msg);

            // dispatch message to window procedure for processing
            // this function will implicitly call the `wndClass.lpfnWndProc` for message dispatching
            DispatchMessage(&msg);
        }
    }


    return 0;
}

/**
 * LRESULT - LONG_PTR 
 * CALLBACK - __stdcall calling convention
 * 
 * @param hWnd - handle to our application window
 * @param message - dispatched message (xrefs from DispatchMessage(&msg))
 * @param wParam & lParam - additional message, it value depends on type of message
 * @return - result of message processing
 * 
 * @return - result of message processing 
 */
LRESULT CALLBACK wndProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

    /**
     * Process the message using switch-case statement.
     * 
     * List of messages - https://msdn.microsoft.com/en-us/library/ms644927%28v=VS.85%29.aspx#system_defined 
     */
    switch (message) {
        
        // process WM_DESTROY message
        case WM_DESTROY:
            
            /**
             * request for thread termination
             * 
             * the event looping at the WinMain should stop the loop
             * when WM_QUIT is being returns by wndProcedure
             * 
             * @nExitCode - use WM_QUIT as a marker for termination
             */
            PostQuitMessage(WM_QUIT);
            break;
            
        // process another messages like minimize, maximize, etc
        // should be pain in the ass if we want to process it all right? :)
        default:
            
            /**
             * Process another messages that hasn't been handles by us.
             * 
             * It should and has to be here, as we want it to process another messages
             * such as minimizing, maximizing, and others. If we haven't got time to handle 
             * all those messages ourselves, then let DefWindowProc handles it for us :)
             * 
             * @params - same like wndProcedure
             * @return - same like wndProcedure
             */
            return DefWindowProcA(hWnd, message, wParam, lParam);
    }

    return 0;
}
