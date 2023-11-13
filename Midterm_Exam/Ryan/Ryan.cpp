#include <windows.h>
#include "yuhanCG.h"
POINT drawstart, drawend; //드로잉 영역 좌표 
BOOL mindraw = FALSE; // 마우스가 드로잉 영역에 있는가 
int drawmode = 0;
int x, y, ex, ey, sx, sy;
// 이전 사각형의 좌표를 저장하는 변수
int prevStartX, prevStartY, prevEndX, prevEndY, pStartX, pStartY, pEndX, pEndY;
POINT startPos;
BOOL isDrawing = FALSE;
int sp = 0;
bool bonoVisible = false;
bool lionVisible = false;




LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_KEYDOWN:
        if ((wParam == VK_SPACE)) {

            sp = 1;

            InvalidateRect(hWnd, NULL, TRUE);
        }
        break; //이걸 왜빼먹어서 안되게하냐 
    case WM_KEYUP:
        if ((wParam == VK_SPACE)) {

            sp = 0;

            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_LBUTTONDOWN:
        isDrawing = TRUE;
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        break;
    case WM_LBUTTONUP:

        if (isDrawing && lionVisible) {
            isDrawing = FALSE;
            ex = LOWORD(lParam);
            ey = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) { //1번 
            drawmode = 1;

            SetFocus(hWnd);
            InvalidateRect(hWnd, NULL, TRUE);


        }
        else if (LOWORD(wParam) == 2) { //2번 
            drawmode = 2;

            SetFocus(hWnd);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 3) { //3번 
            drawmode = 3;
            bonoVisible = true;
            lionVisible = false;
            SetFocus(hWnd);
            InvalidateRect(hWnd, NULL, TRUE);

        }
        else if (LOWORD(wParam) == 4) { //4번 
            drawmode = 4;
            bonoVisible = false;
            lionVisible = true;
            x = 0;
            y = 0;
            ex = 0;
            ey = 0; //버튼누를때 좌표초기화
            SetFocus(hWnd);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 5) { //5번 
            drawmode = 5;

            SetFocus(hWnd);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;

    case WM_MOUSEMOVE:

        POINT mousePos;
        GetCursorPos(&mousePos);

        // 이동한 마우스 위치가 드로잉 영역 내에 있는지 확인합니다.
        if (mousePos.x >= drawstart.x && mousePos.x <= drawend.x &&
            mousePos.y >= drawstart.y && mousePos.y <= drawend.y) {
            mindraw = TRUE; // 드로잉 영역 내에 마우스가 있음
        }
        else {
            mindraw = FALSE; // 드로잉 영역 밖에 마우스가 있음
        }
        break;

    case WM_PAINT:
        if (true) {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // 클라이언트 영역 크기 가져오기
            RECT clientRect;
            GetClientRect(hWnd, &clientRect);

            int margin = 8;
            int boxWidth = clientRect.right - clientRect.left - 2 * margin;
            int boxHeight = clientRect.bottom - clientRect.top - 2 * margin;

            // RGB(255, 240, 200) 색상의 네모 그리기
            HBRUSH hColorBrush = CreateSolidBrush(RGB(255, 240, 200)); // 원하는 색상의 브러시 생성
            SelectObject(hdc, hColorBrush);

            int left = margin;
            int top = margin;
            int right = left + boxWidth;
            int bottom = top + boxHeight;

            //box그리기 
            Rectangle(hdc, left, top, right, bottom);

            //드로잉영역그리기 
            HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
            SelectObject(hdc, whiteBrush);
            Rectangle(hdc, left + 8, top + 88, right - 8, bottom - 8);
            drawstart.x = left + 8;
            drawstart.y = top + 88;
            drawend.x = right - 8;
            drawend.y = bottom - 8;
          


            if (wParam == VK_SPACE) {
                sp = 1;
            }
            if (bonoVisible) {
                DrawBonobono(hWnd, hdc, sp); //보노보노
            }
           
            if (lionVisible) {
                DrawRyan(hWnd, hdc, x, y, ex, ey); //보노보노
            }
            EndPaint(hWnd, &ps);

        }


        break;
    case WM_SETCURSOR: {
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hWnd, &pt);

        if (pt.x > drawstart.x && pt.x < drawend.x &&
            pt.y > drawstart.y && pt.y < drawend.y) {
            // 마우스 커서를 십자가 모양으로 설정
            SetCursor(LoadCursor(NULL, IDC_CROSS));
            return TRUE; // 처리됨을 알림
        }
        else { //다시 화살표 
            SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
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
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

    HWND hWnd;
    HWND hButton1, hButton2, hButton3, hButton4, hButton5;

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = CreateSolidBrush(RGB(255, 240, 200)); // 배경색 설정
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"ButtonWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    // 윈도우 창 크기를 800x480로 설정하고 메뉴바를 포함하지 않도록 스타일을 조절합니다.
    hWnd = CreateWindow(
        L"ButtonWindowClass", L"라이언", WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, 0, 800, 480, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }
    int btnmargin = 146; //버튼+ 마진 
    int btnstart = 32;// 1번 버튼 시작지점 
    hButton1 = CreateWindow(
        L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        btnstart, 16, 130, 64, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        btnstart + btnmargin, 16, 130, 64, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        btnstart + btnmargin * 2, 16, 130, 64, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        btnstart + btnmargin * 3, 16, 130, 64, hWnd, (HMENU)4, hInstance, NULL);
    hButton5 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        btnstart + btnmargin * 4, 16, 130, 64, hWnd, (HMENU)5, hInstance, NULL);



    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}