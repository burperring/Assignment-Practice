#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("AnimWin");

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

int pan[3][3];

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT  rect;
	HBRUSH hBrush, oldBrush;
	TCHAR *Mes = TEXT("마우스 왼쪽 버튼을 누르시면 애니메이션을 볼 수 있습니다");
	int x, y;
	 
	static int turn = 1; //static bool turn = 1; 
	// 0=empty, 1=red, 2 = green
	switch (iMessage) {
	case WM_LBUTTONDOWN:
		
		GetClientRect(hWnd, &rect);
		//SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
		x = (LOWORD(lParam)) / (rect.right/3);		// x HitTest
		y = (HIWORD(lParam)) / (rect.bottom/3);		// y HitTest
		if (pan[x][y] == 0)  //비어있다면
		{
			pan[x][y] = turn;
			turn = (turn == 1 ? 2 : 1);  //반전
			InvalidateRect(hWnd, NULL, TRUE);
		}

		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		//SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
		//판그리고
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++)
				Rectangle(hdc, i*rect.right / 3, j*rect.bottom / 3, (i+1) * rect.right/3, (j+1) * rect.bottom / 3);
		}
		//돌그리고
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (pan[i][j] == 1)
				{
					hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Ellipse(hdc, i*rect.right / 3, j*rect.bottom / 3, (i + 1) * rect.right / 3, (j + 1)*  rect.bottom / 3);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);

				}
				else if (pan[i][j] == 2){
					hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Ellipse(hdc, i*rect.right / 3, j*rect.bottom / 3, (i + 1) * rect.right / 3, (j + 1)*  rect.bottom / 3);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}

			}
		}
		
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}