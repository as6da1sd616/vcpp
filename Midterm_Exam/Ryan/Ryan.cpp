#include <windows.h>
#include "yuhanCG.h"
POINT drawstart, drawend; //드로잉 영역 좌표 
BOOL mindraw = FALSE; // 마우스가 드로잉 영역에 있는가 
int drawmode = 0;
int x, y, ex, ey, sx, sy, cx, cex;
int offsetX = 0, offsetY = 0;
double cre = 0;
// 이전 사각형의 좌표를 저장하는 변수
int prevStartX, prevStartY, prevEndX, prevEndY, pStartX, pStartY, pEndX, pEndY, mx, my, mex, mey;
int newX, newY, width, height;

POINT startPos;
BOOL isDrawing = FALSE;
int sp = 0;
bool bonoVisible = false;
bool lionVisible = false;
bool circleVisible = false;
bool circleRe = false;
bool crein = false;
bool boxVisible = false;
bool boxMove = false;
bool ix = false;
bool iy = false;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    RECT rc2;
    POINT lt, rb;
    GetClientRect(hWnd, &rc2);
    lt.x = rc2.left; lt.y = rc2.top; rb.x = rc2.right; rb.y = rc2.bottom;
    ClientToScreen(hWnd, &lt); ClientToScreen(hWnd, &rb);
    rc2.left = lt.x + 1; rc2.top = lt.y - 25; rc2.right = rb.x + 1; rc2.bottom = rb.y + 1;
    //ClipCursor(&rc2);


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
    case WM_RBUTTONDOWN:
        if (circleVisible) {
            circleRe = true;
            cre = 0;
            cx = LOWORD(lParam);
        }
        if (boxVisible) {
            boxMove = true;
            mx = LOWORD(lParam);
            my = HIWORD(lParam);


        }


        break;
    case WM_RBUTTONUP:
        if (circleRe) {

            cex = LOWORD(lParam);
            if (cex > cx) {
                cre = (cex - cx) * 0.02;
                crein = false;
            }
            else {
                cre = (cx - cex) * 0.02;
                crein = true;
            }
            InvalidateRect(hWnd, NULL, TRUE);
            circleRe = false;

        }
        if (boxMove) {

            boxMove = FALSE;
        }
        break;
    case WM_LBUTTONDOWN:
        isDrawing = TRUE;
        x = LOWORD(lParam);
        y = HIWORD(lParam);
        cre = 0;
        break;
    case WM_LBUTTONUP:

        if (isDrawing && (circleVisible || lionVisible || boxVisible)) {
            isDrawing = FALSE;
            ex = LOWORD(lParam);
            ey = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) { //1번 
            drawmode = 1;
            bonoVisible = false;
            lionVisible = false;
            circleVisible = false;
            boxVisible = true;
            x = 0;
            y = 0;
            ex = 0;
            ey = 0; //버튼누를때 좌표초기화

            SetFocus(hWnd);
            InvalidateRect(hWnd, NULL, TRUE);


        }
        else if (LOWORD(wParam) == 2) { //2번 
            drawmode = 2;
            bonoVisible = false;
            lionVisible = false;
            circleVisible = true;
            boxVisible = false;
            x = 0;
            y = 0;
            ex = 0;
            ey = 0; //버튼누를때 좌표초기화
            SetFocus(hWnd);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 3) { //3번 
            drawmode = 3;
            bonoVisible = true;
            lionVisible = false;
            circleVisible = false;
            boxVisible = false;
            SetFocus(hWnd);
            InvalidateRect(hWnd, NULL, TRUE);

        }
        else if (LOWORD(wParam) == 4) { //4번 
            drawmode = 4;
            bonoVisible = false;
            lionVisible = true;
            circleVisible = false;
            boxVisible = false;
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
        if (isDrawing && (circleVisible || lionVisible || boxVisible)) {
            ex = LOWORD(lParam);
            ey = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, TRUE);

        }
        if (circleRe) {
            cex = LOWORD(lParam);
            if (cex > cx) {
                cre = (cex - cx) * 0.02;
                crein = false;
            }
            else {
                cre = (cx - cex) * 0.02;
                crein = true;
            }
            InvalidateRect(hWnd, NULL, TRUE);

        }
        if (boxMove) {
            mex = LOWORD(lParam);
            mey = HIWORD(lParam);
            offsetX = mex - mx;
            offsetY = mey - my;
            prevStartX = x + offsetX;
            prevEndX = ex + offsetX;
            prevStartY = y + offsetY;
            prevEndY = ey + offsetY;

            InvalidateRect(hWnd, NULL, TRUE);


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
            if (boxVisible) {
                DrawBox(hWnd, hdc, wParam, lParam, x, y, ex, ey, boxMove, newX, newY, width, height, prevStartX, prevStartY, prevEndX, prevEndY); //네모
            }
            if (circleVisible) {
                DrawCircle(hWnd, hdc, x, y, ex, ey, cre, crein); //원 
            }
            if (bonoVisible) {
                DrawBonobono(hWnd, hdc, sp); //보노보노
            }

            if (lionVisible) {
                DrawRyan(hWnd, hdc, x, y, ex, ey);  //라이언
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
        ClipCursor(NULL);
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

    hWnd = CreateWindow(
        L"ButtonWindowClass", L"201907046김승원", WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX,
        CW_USEDEFAULT, 0, 800, 512, NULL, NULL, hInstance, NULL);

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