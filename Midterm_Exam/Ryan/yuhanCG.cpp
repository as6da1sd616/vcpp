#include "yuhanCG.h"
 void DrawBonobono(HWND hWnd, HDC hdc, int blink) {
    RECT rect;
    GetClientRect(hWnd, &rect);
    bool sp;
    sp = blink;
    
        // �ڽ� �׸���
        HBRUSH hBrush = CreateSolidBrush(RGB(127, 200, 255)); // �Ķ� 
        SelectObject(hdc, hBrush);
        Ellipse(hdc, 250, 100, 550, 400);

        HBRUSH h3Brush = CreateSolidBrush(RGB(255, 150, 255)); //��ũ
        SelectObject(hdc, h3Brush);
        Ellipse(hdc, 385, 240, 415, 310);
        DeleteObject(hBrush);

        HBRUSH h2Brush = CreateSolidBrush(RGB(255, 255, 255)); // ���
        SelectObject(hdc, h2Brush);
        Ellipse(hdc, 400, 245, 440, 275);
        Ellipse(hdc, 360, 245, 400, 275);
        HBRUSH h1Brush = CreateSolidBrush(RGB(0, 0, 0)); // ����
        SelectObject(hdc, h1Brush);
        Ellipse(hdc, 380, 225, 420, 260);
        DeleteObject(hBrush);

        //����
        // ������ ����
        MoveToEx(hdc, 340, 250, NULL);
        // ������ ���� ����
        LineTo(hdc, 380, 260);
        // ������ ����
        MoveToEx(hdc, 340, 270, NULL);
        // ������ ���� ����
        LineTo(hdc, 380, 265);

        // ������ ����
        MoveToEx(hdc, 460, 250, NULL);
        // ������ ���� ����
        LineTo(hdc, 420, 260);
        // ������ ����
        MoveToEx(hdc, 460, 270, NULL);
        // ������ ���� ����
        LineTo(hdc, 420, 265);

        if (sp == false) {
            //�Ϲ� ���� 
            Ellipse(hdc, 300, 190, 310, 205);
            Ellipse(hdc, 470, 190, 480, 205);
            SelectObject(hdc, h2Brush);
            Ellipse(hdc, 302, 195, 308, 200);
            Ellipse(hdc, 472, 195, 479, 200);
        }
        else {
            SelectObject(hdc, h1Brush);
            // >< ���� 
                // ������ ����
            MoveToEx(hdc, 300, 190, NULL);
            // ������ ���� ����
            LineTo(hdc, 320, 205);
            // ������ ����
            MoveToEx(hdc, 300, 210, NULL);
            // ������ ���� ����
            LineTo(hdc, 320, 205);

            // ������ ����
             // ������ ����
            MoveToEx(hdc, 470, 205, NULL);
            LineTo(hdc, 500, 190);
            MoveToEx(hdc, 470, 205, NULL);
            // ������ ���� ����
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
        // �ڽ� �׸���
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 200, 15)); // ��Ȳ
        SelectObject(hdc, hBrush);
        int a, b, c, d;
        a = x;
        b = y;
        c = ex;
        d = ey;

        if (x > ex) { //������ ���� 
            a = x;
            x = ex;
            ex = a;
        }
        if (y > ey) {
            b = y;
            y = ey;
            ey = b;
        }

        if (x!=0&&x <= 24) {  //����׿��� �ĳ����� ����
            x = 24;
        }
        if (y!=0&&y <= 104) {
            y = 104;
        }
        if (ex >= 768) {
            ex = 768;
        }
        if (ey >= 440) {
            ey = 440;
        }



        int resultx = ex - x; // x���� 
        int resulty = ey - y; // y����
        //Rectangle(hdc, x, y, ex, ey); 

        Ellipse(hdc, x, y, x + resultx * 0.27, y + resulty * 0.27); //���ʱ� 

        Ellipse(hdc, x + resultx * 0.725, y, ex, y + resulty * 0.27);// �����ʱ�
        Ellipse(hdc, x, y, ex, ey);//���



        HBRUSH h2Brush = CreateSolidBrush(RGB(255, 255, 255)); // ���
        SelectObject(hdc, h2Brush);
        Ellipse(hdc, x + resultx * 0.51, y + resulty * 0.5, x + resultx * 0.67, y + resulty * 0.62); //��
        Ellipse(hdc, x + resultx * 0.35, y + resulty * 0.5, x + resultx * 0.51, y + resulty * 0.62); //��
        HBRUSH h1Brush = CreateSolidBrush(RGB(0, 0, 0)); // ����
        SelectObject(hdc, h1Brush);
        DeleteObject(hBrush);

        //����
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

        //�Ϲ� ���� 
        Ellipse(hdc, x + resultx * 0.23, y + resulty * 0.36, x + resultx * 0.29, y + resulty * 0.42);
        Ellipse(hdc, x + resultx * 0.7, y + resulty * 0.36, x + resultx * 0.76, y + resulty * 0.42);



    

}