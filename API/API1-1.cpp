#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Class");

// 진입점 . . . Entry Point		ex) c++의 main()
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

int px_R[1000], py_R[1000];
int px_B[1000], py_B[1000];
int iCount_R = 0;		// 그려진 빨간점의 개수
int iCount_B = 0;		// 그려진 파란점의 개수
// Window Procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int x, y;
	HBRUSH hBrush;

	// Message(Event) Driven Architecture
	switch (iMessage) {
	case WM_CREATE:
		hWndMain = hWnd;
		return 0;
	case WM_LBUTTONDOWN:							// 왼쪽 마우스버튼을 누르면
		hdc = GetDC(hWnd);							// 윈도우에 달려있는 그리기도구상자(DC) 얻기
		px_R[iCount_R] = x = LOWORD(lParam);			// 왼쪽 마우스버튼으로 누른 좌표의 X위치 (매크로)
		py_R[iCount_R] = y = HIWORD(lParam);			// 왼쪽 마우스버튼으로 누른 좌표의 Y위치 (매크로)
		iCount_R++;
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, hBrush);
		Ellipse(hdc, x - 10, y - 10, x + 10, y + 10);		// 원을 그려라
		return 0;
	case WM_RBUTTONDOWN:
		hdc = GetDC(hWnd);
		px_B[iCount_B] = x = LOWORD(lParam);
		py_B[iCount_B] = y = HIWORD(lParam);
		iCount_B++;
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		SelectObject(hdc, hBrush);
		Ellipse(hdc, x - 10, y - 10, x + 10, y + 10);
		return 0;
	case WM_PAINT:					// 다시 그려라
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < iCount_R; i++)
		{
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
			Ellipse(hdc, px_R[i] - 10, py_R[i] - 10, px_R[i] + 10, py_R[i] + 10);
		}
		for (int i = 0; i < iCount_B; i++)
		{
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hBrush);
			Ellipse(hdc, px_B[i] - 10, py_B[i] - 10, px_B[i] + 10, py_B[i] + 10);
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}