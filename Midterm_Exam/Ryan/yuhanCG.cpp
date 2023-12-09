#include "yuhanCG.h"

void DrawBox(HWND hWnd, HDC hdc, WPARAM wParam, LPARAM lParam, int left, int top, int right, int bottom, bool boxMove, int newX, int newY, int width, int height, int prevStartX, int prevStartY, int  prevEndX, int prevEndY) {
    RECT rect;
    GetClientRect(hWnd, &rect);
    int x = left;
    int y = top;
    int ex = right;
    int ey = bottom;
    int a, b, c, d;
    if ((x != 0) && (!boxMove)) {
        Rectangle(hdc, x, y, ex, ey);
        prevStartX = x;
        prevStartY = y;
        prevEndX = ex;
        prevEndY = ey;
    }
    if (boxMove) {

        Rectangle(hdc, prevStartX, prevStartY, prevEndX, prevEndY);

    }







}


void DrawCircle(HWND hWnd, HDC hdc, int left, int top, int right, int bottom, double  cre, bool crein) {
    RECT rect;
    GetClientRect(hWnd, &rect);
    int x = left;
    int y = top;
    int ex = right;
    int ey = bottom;
    bool bre = false;
    int a, b, c, d;


    int resultx = (ex - x) / 2 * cre; // x길이 
    int resulty = (ey - y) / 2 * cre; // y길이
    if (crein) {
        if (!bre)
            a = x + resultx;
        b = y + resulty;
        c = ex - resultx;
        d = ey - resulty;
        if (a > c) {
            bre = true;
            a = x;
            b = y;
            c = x;
            d = y;
        }
    }
    else {
        a = x - resultx;
        b = y - resulty;
        c = ex + resultx;
        d = ey + resulty;
    }
    if (x != 0 && x <= 24) {  //드로잉영역 쳐나가기 방지
        x = 24;
    }
    if (y != 0 && y <= 104) {
        y = 104;
    }
    if (ex >= 768) {
        ex = 768;
    }
    if (ey >= 440) {
        ey = 440;
    }
    if (ey <= 104) {
        ey= 104;
    }
    if (a != 0 && a <= 24) {  //드로잉영역 쳐나가기 방지
        a = 24;
    }
    if (b != 0 && b <= 104) {
        b = 104;
    }
    if (c >= 768) {
        c = 768;
    }
    if (d >= 450) {
        d = 450;
    }
    if (d <= 104) {
        d = 104;
    }
    if (cre == 0) {
        Ellipse(hdc, x, y, ex, ey);
    }
    else {//확대
        Ellipse(hdc, a, b, c, d);
    }






}





 void DrawBonobono(HWND hWnd, HDC hdc, int blink) {
    RECT rect;
    GetClientRect(hWnd, &rect);
    bool sp;
    sp = blink;
    
        // 박스 그리기
        HBRUSH hBrush = CreateSolidBrush(RGB(127, 200, 255)); // 파랑 
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 250, 100, 550, 400);

        HBRUSH h3Brush = CreateSolidBrush(RGB(255, 150, 255)); //핑크
        SelectObject(hdc, h3Brush);
        Ellipse(hdc, 385, 240, 415, 310);
        DeleteObject(hBrush);

        HBRUSH h2Brush = CreateSolidBrush(RGB(255, 255, 255)); // 흰색
        SelectObject(hdc, h2Brush);
        Ellipse(hdc, 400, 245, 440, 275);
        Ellipse(hdc, 360, 245, 400, 275);
        HBRUSH h1Brush = CreateSolidBrush(RGB(0, 0, 0)); // 검정
        SelectObject(hdc, h1Brush);
        Ellipse(hdc, 380, 225, 420, 260);
        DeleteObject(hBrush);

        //수염
        // 시작점 설정
        MoveToEx(hdc, 340, 250, NULL);
        // 직선의 끝점 설정
        LineTo(hdc, 380, 260);
        // 시작점 설정
        MoveToEx(hdc, 340, 270, NULL);
        // 직선의 끝점 설정
        LineTo(hdc, 380, 265);

        // 시작점 설정
        MoveToEx(hdc, 460, 250, NULL);
        // 직선의 끝점 설정
        LineTo(hdc, 420, 260);
        // 시작점 설정
        MoveToEx(hdc, 460, 270, NULL);
        // 직선의 끝점 설정
        LineTo(hdc, 420, 265);

        if (sp == false) {
            //일반 눈깔 
            Ellipse(hdc, 300, 190, 310, 205);
            Ellipse(hdc, 470, 190, 480, 205);
            SelectObject(hdc, h2Brush);
            Ellipse(hdc, 302, 195, 308, 200);
            Ellipse(hdc, 472, 195, 479, 200);
        }
        else {
            SelectObject(hdc, h1Brush);
            // >< 눈깔 
                // 시작점 설정
            MoveToEx(hdc, 300, 190, NULL);
            // 직선의 끝점 설정
            LineTo(hdc, 320, 205);
            // 시작점 설정
            MoveToEx(hdc, 300, 210, NULL);
            // 직선의 끝점 설정
            LineTo(hdc, 320, 205);

            // 시작점 설정
             // 시작점 설정
            MoveToEx(hdc, 470, 205, NULL);
            LineTo(hdc, 500, 190);
            MoveToEx(hdc, 470, 205, NULL);
            // 직선의 끝점 설정
            LineTo(hdc, 500, 210);
        }

    

}





void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {
    RECT rect;
    GetClientRect(hWnd, &rect);
    int x = left;
    int y = top;
    int ex = right;
    int ey = bottom;
        // 박스 그리기
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 200, 15)); // 주황
        SelectObject(hdc, hBrush);
        int a, b, c, d;
        a = x;
        b = y;
        c = ex;
        d = ey;

        if (x > ex) { //뒤집힘 방지 
            a = x;
            x = ex;
            ex = a;
        }
        if (y > ey) {
            b = y;
            y = ey;
            ey = b;
        }

        if (x!=0&&x <= 24) {  //드로잉영역 쳐나가기 방지
            x = 24;
        }
        if (y!=0&&y <= 104) {
            y = 104;
        }
        if (ex >= 768) {
            ex = 768;
        }
        if (ey >= 450) {
            ey = 450;
        }
        if (ey <= 104) {
            ey = 104;
        }



        int resultx = ex - x; // x길이 
        int resulty = ey - y; // y길이
        //Rectangle(hdc, x, y, ex, ey); 

        Ellipse(hdc, x, y, x + resultx * 0.27, y + resulty * 0.27); //왼쪽귀 

        Ellipse(hdc, x + resultx * 0.725, y, ex, y + resulty * 0.27);// 오른쪽귀
        Ellipse(hdc, x, y, ex, ey);//면상



        HBRUSH h2Brush = CreateSolidBrush(RGB(255, 255, 255)); // 흰색
        SelectObject(hdc, h2Brush);
        Ellipse(hdc, x + resultx * 0.51, y + resulty * 0.5, x + resultx * 0.67, y + resulty * 0.62); //입
        Ellipse(hdc, x + resultx * 0.35, y + resulty * 0.5, x + resultx * 0.51, y + resulty * 0.62); //입
        HBRUSH h1Brush = CreateSolidBrush(RGB(0, 0, 0)); // 검정
        SelectObject(hdc, h1Brush);
        DeleteObject(hBrush);

        //눈썹
        MoveToEx(hdc, x + resultx * 0.16, y + resulty * 0.29, NULL);
        LineTo(hdc, x + resultx * 0.35, y + resulty * 0.29);
        MoveToEx(hdc, x + resultx * 0.16, y + resulty * 0.29 + 1, NULL);
        LineTo(hdc, x + resultx * 0.35, y + resulty * 0.29 + 1);
        MoveToEx(hdc, x + resultx * 0.16, y + resulty * 0.29 + 2, NULL);
        LineTo(hdc, x + resultx * 0.35, y + resulty * 0.29 + 2);


        MoveToEx(hdc, x + resultx * 0.62, y + resulty * 0.29, NULL);
        LineTo(hdc, x + resultx * 0.82, y + resulty * 0.29);
        MoveToEx(hdc, x + resultx * 0.62, y + resulty * 0.29 + 1, NULL);
        LineTo(hdc, x + resultx * 0.82, y + resulty * 0.29 + 1);
        MoveToEx(hdc, x + resultx * 0.62, y + resulty * 0.29 + 2, NULL);
        LineTo(hdc, x + resultx * 0.82, y + resulty * 0.29 + 2);

        //일반 눈깔 
        Ellipse(hdc, x + resultx * 0.23, y + resulty * 0.36, x + resultx * 0.29, y + resulty * 0.42);
        Ellipse(hdc, x + resultx * 0.7, y + resulty * 0.36, x + resultx * 0.76, y + resulty * 0.42);



    

}