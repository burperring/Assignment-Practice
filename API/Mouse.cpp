#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Mouse");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;// | CS_DBLCLKS;
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

typedef struct _tagLine
{
	POINT p[1000];	// 좌표들
	int iCount;		// 점의 갯수들
}Line;
Line lines[500];
int iLinesCount;
int iTempCount;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen;
	static int x;
	static int y;
	//static BOOL bNowDraw=FALSE;

	switch (iMessage) {
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		lines[iLinesCount].p[iTempCount].x = x;
		lines[iLinesCount].p[iTempCount].y = y;
		iTempCount++;
		//	bNowDraw=TRUE;
		return 0;
	case WM_MOUSEMOVE:
		// 의미만 보낸다 (마우스로 움직였는데 왼쪽버튼을 누른 상태로 움직였다면)
		if (wParam & MK_LBUTTON) {
			hdc = GetDC(hWnd);
			// 펜 크기와 색 저장
			hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
			SelectObject(hdc, hPen);
			MoveToEx(hdc, x, y, NULL);
			x = LOWORD(lParam);
			y = HIWORD(lParam);			
			lines[iLinesCount].p[iTempCount].x = x;
			lines[iLinesCount].p[iTempCount].y = y;
			LineTo(hdc, x, y);
			ReleaseDC(hWnd, hdc);
			iTempCount++;
		}
		return 0;
	case WM_LBUTTONUP:
		// 한개의 선객체 완성
		lines[iLinesCount].iCount = iTempCount;
		iTempCount = 0;
		iLinesCount++;
		//	bNowDraw=FALSE;
		return 0;
	case WM_LBUTTONDBLCLK:
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
		SelectObject(hdc, hPen);
		for (int i = 0; i < iLinesCount; i++)
		{
			for (int j = 0; j < lines[i].iCount - 1; j++)
			{
				MoveToEx(hdc, lines[i].p[j].x, lines[i].p[j].y, NULL);
				LineTo(hdc, lines[i].p[j+1].x, lines[i].p[j+1].y);
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

