#include <windows.h>
#include "resource.h"

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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
	POINT p[1000];	// ��ǥ��
	int iCount;		// ���� ������
	int iWidth;		// �� ���� ����
}Line;
Line lines[500];
int iLinesCount;
int iTempCount;
int iCurrentWidth = 1;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN hPen, OldPen;
	static int x;
	static int y;
	//static BOOL bNowDraw=FALSE;

	switch (iMessage) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDM_1:
			iCurrentWidth = 1;
			break;
		case IDM_3:
			iCurrentWidth = 3;
			break;
		case IDM_5:
			iCurrentWidth = 5;
			break;
		case IDM_7:
			iCurrentWidth = 7;
			break;
		case IDM_9:
			iCurrentWidth = 9;
			break;
		}
		return 0;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		lines[iLinesCount].p[iTempCount].x = x;
		lines[iLinesCount].p[iTempCount].y = y;
		iTempCount++;
		//	bNowDraw=TRUE;
		return 0;
	case WM_MOUSEMOVE:
		// �ǹ̸� ������ (���콺�� �������µ� ���ʹ�ư�� ���� ���·� �������ٸ�)
		if (wParam & MK_LBUTTON) {
			hdc = GetDC(hWnd);
			// �� ũ��� �� ����
			hPen = CreatePen(PS_SOLID, iCurrentWidth, RGB(255, 0, 0));
			SelectObject(hdc, hPen);
			MoveToEx(hdc, x, y, NULL);
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			lines[iLinesCount].p[iTempCount].x = x;
			lines[iLinesCount].p[iTempCount].y = y;
			LineTo(hdc, x, y);
			ReleaseDC(hWnd, hdc);
			lines[iLinesCount].iWidth = iCurrentWidth;
			iTempCount++;
		}
		return 0;
	case WM_LBUTTONUP:
		// �Ѱ��� ����ü �ϼ�
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
		for (int i = 0; i < iLinesCount; i++)
		{
			hPen = CreatePen(PS_SOLID, lines[i].iWidth, RGB(255, 0, 0));
			hPen = (HPEN)SelectObject(hdc, hPen);
			MoveToEx(hdc, lines[i].p[0].x, lines[i].p[0].y, NULL);
			for (int j = 0; j < lines[i].iCount - 1; j++)
			{
				LineTo(hdc, lines[i].p[j + 1].x, lines[i].p[j + 1].y);
			}
			// ���� ���� GDI ��ü(�׸��ⰴü)�� ��� �� �ݵ�� �����ؾ��Ѵ�.
			// �� �������� ��(OS�� ���õǾ��ִ� GDI ��ü�� �������� �ʴ´�.)
			DeleteObject(SelectObject(hdc, hPen));
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

