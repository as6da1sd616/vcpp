#pragma once
#include <windows.h>

void DrawBox(HWND hWnd, HDC hdc, WPARAM wParam, LPARAM lParam, int left, int top, int right, int bottom, bool boxMove, int newX, int newY, int width, int height, int prevStartX, int prevStartY, int  prevEndX, int prevEndY);
void DrawCircle(HWND hWnd, HDC hdc, int left, int top, int right, int bottom, double  cre, bool crein);
void DrawBonobono(HWND hWnd, HDC hdc, int blink);
void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom);