#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

HWND hwnd;
POINT startPos;
BOOL isDrawing = FALSE;
BOOL isMoving = FALSE;
HBRUSH pinkBrush, whiteBrush; // 분홍색 브러시 핸들

// 이동을 위한 변수
int offsetX, offsetY;
// 이전 사각형의 좌표를 저장하는 변수
int prevStartX, prevStartY, prevEndX, prevEndY, pStartX, pStartY, pEndX, pEndY;
// 초기화 함수
void Initialize() {
	isDrawing = FALSE;
	isMoving = FALSE;
	offsetX = 0;
	offsetY = 0;
	prevStartX = 0;
	prevStartY = 0;
	pStartX = 0;
	pStartY = 0;
	prevEndX = 0;
	prevEndY = 0;
}

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	RECT rc2;
	POINT lt, rb;
	GetClientRect(hwnd, &rc2);
	lt.x = rc2.left; lt.y = rc2.top; rb.x = rc2.right; rb.y = rc2.bottom;
	ClientToScreen(hwnd, &lt); ClientToScreen(hwnd, &rb);
	rc2.left = lt.x + 1; rc2.top = lt.y - 100; rc2.right = rb.x + 1; rc2.bottom = rb.y + 1;
	ClipCursor(&rc2);


	switch (uMsg) {
	case WM_CREATE:
		// 분홍색 브러시 생성
		pinkBrush = CreateSolidBrush(RGB(255, 0, 255)); // RGB 색상 값으로 분홍색 설정
		whiteBrush = CreateSolidBrush(RGB(255, 255, 255)); // RGB 색상 값으로 흰색설정
		Initialize();
		break;
	case WM_LBUTTONDOWN:
		isDrawing = TRUE;
		startPos.x = LOWORD(lParam);
		startPos.y = HIWORD(lParam);
		break;
	case WM_RBUTTONDOWN:
		if (LOWORD(lParam) >= prevStartX && LOWORD(lParam) <= prevEndX &&
			HIWORD(lParam) >= prevStartY && HIWORD(lParam) <= prevEndY) {
			isMoving = TRUE;
			offsetX = LOWORD(lParam) - prevStartX;
			offsetY = HIWORD(lParam) - prevStartY;
		}
		break;
	case WM_RBUTTONUP:
		// 마우스 오른쪽 버튼 뗄 때, 이동 모드 해제

		isMoving = FALSE;
		break;
	case WM_LBUTTONUP:

		if (isDrawing) {
			isDrawing = FALSE;
			int endX = LOWORD(lParam);
			int endY = HIWORD(lParam);

			// 이전 사각형 삭제
			HDC hdc = GetDC(hwnd);
			SelectObject(hdc, whiteBrush); // 
			SetROP2(hdc, R2_WHITE);
			Rectangle(hdc, prevStartX, prevStartY, prevEndX, prevEndY);

			// 새로운 사각형 그리기
			SetROP2(hdc, R2_COPYPEN);
			SelectObject(hdc, pinkBrush); // 분홍색 브러시 선택
			Rectangle(hdc, startPos.x, startPos.y, endX, endY);
			ReleaseDC(hwnd, hdc);

			// 현재 사각형의 좌표 저장
			prevStartX = startPos.x;
			prevStartY = startPos.y;
			prevEndX = endX;
			prevEndY = endY;
		}
		break;
	case WM_MOUSEMOVE:
		if (isDrawing) {
			int currentX = LOWORD(lParam);
			int currentY = HIWORD(lParam);

			HDC hdc = GetDC(hwnd);
			SelectObject(hdc, whiteBrush); // 
			SetROP2(hdc, R2_WHITE);
			Rectangle(hdc, startPos.x, startPos.y, pStartX, pStartY);

			SetROP2(hdc, R2_COPYPEN);
			SelectObject(hdc, pinkBrush); // 분홍색 브러시 선택
			Rectangle(hdc, startPos.x, startPos.y, currentX, currentY);

			ReleaseDC(hwnd, hdc);

			pStartX = currentX;
			pStartY = currentY;
		}
		else if (isMoving && (wParam & MK_RBUTTON)) {
			int newX = LOWORD(lParam) - offsetX;
			int newY = HIWORD(lParam) - offsetY;
			int width = prevEndX - prevStartX;
			int height = prevEndY - prevStartY;


			// 이전 사각형 삭제
			HDC hdc = GetDC(hwnd);
			SelectObject(hdc, whiteBrush); // 
			SetROP2(hdc, R2_WHITE);
			Rectangle(hdc, prevStartX, prevStartY, prevEndX, prevEndY);

			// 이동한 사각형 그리기
			SetROP2(hdc, R2_COPYPEN);
			SelectObject(hdc, pinkBrush); // 분홍색 브러시 선택
			Rectangle(hdc, newX, newY, newX + width, newY + height);
			ReleaseDC(hwnd, hdc);

			// 현재 사각형의 좌표 저장
			prevStartX = newX;
			prevStartY = newY;
			prevEndX = newX + width;
			prevEndY = newY + height;

		}
		break;
	case WM_GETMINMAXINFO:
		// 창 크기 변경을 제한하기 위한 메시지 핸들링
		if (1) {
			MINMAXINFO* pInfo = (MINMAXINFO*)lParam;
			pInfo->ptMinTrackSize.x = 800; // 최소 폭
			pInfo->ptMinTrackSize.y = 600; // 최소 높이
			pInfo->ptMaxTrackSize.x = 800; // 최대 폭
			pInfo->ptMaxTrackSize.y = 600; // 최대 높이
			break;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return S_OK;
}
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
	/* 윈도우 클래스 선언.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// 모두 0으로 초기화.

	// 윈도우 클래스 값 설정
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//예외
	}

	// Window viewport 영역 조정
	RECT rect = { 150, 100, 800, 600 };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;



	// Window viewport 영역 조정

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("201907046 김승원"),
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		0, 0, 800, 600,
		NULL, NULL,
		hInstance,
		NULL
	);

	// 오류 검사.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// 창 보이기.
	ShowWindow(hwnd, SW_SHOW); // 창 띄우고
	UpdateWindow(hwnd); // 업데이트해야 보임. 한 쌍으로 쓴다고 보면 됨.



	// 메시지 처리 루프.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		// 메시지 처리.
		if (GetMessage(&msg, hwnd, 0, 0))
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
		{

			// 메시지 해석해줘.
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달해줘.
			DispatchMessage(&msg);

		}
		/*else
		{

		}*/
	}

	//종료 메시지 보내기
	return (int)msg.wParam;

}