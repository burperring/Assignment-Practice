#include <windows.h>
#include "resource.h"
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("Mouse");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style=CS_HREDRAW | CS_VREDRAW;// | CS_DBLCLKS;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		  CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		  NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	
	while (GetMessage(&Message,NULL,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

typedef struct _line
{
	POINT p[1000];
	int iCount;
	// long iCount;
	int iWidth;
	COLORREF iColor;
} line;

line lines[300];
int iLines;
int iCurrentWidth = 5;
//int iTempCount;
TCHAR *Width[] = { TEXT("1"), TEXT("3"), TEXT("5"), TEXT("7") };

COLORREF iCurrentColor=RGB(255,0,0);

#define ID_LISTBOX 100

enum { ID_R1 = 101, ID_R2, ID_R3, ID_R4, ID_R5, ID_R6 };
HWND r1, r2, r3, r4, r5, r6;
HWND hList;
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x;
	static int y;
	//static BOOL bNowDraw=FALSE;
	HPEN hPen, oldPen;
	switch (iMessage) {
	case WM_CREATE:
		CreateWindow(TEXT("button"), TEXT("Colors"), WS_CHILD | WS_VISIBLE |
			BS_GROUPBOX, 5, 5, 120, 110, hWnd, (HMENU)0, g_hInst, NULL);
		r1 = CreateWindow(TEXT("button"), TEXT("Red"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON | WS_GROUP,
			10, 20, 100, 30, hWnd, (HMENU)ID_R1, g_hInst, NULL);
		r2 = CreateWindow(TEXT("button"), TEXT("Green"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			10, 50, 100, 30, hWnd, (HMENU)ID_R2, g_hInst, NULL);
		r3 = CreateWindow(TEXT("button"), TEXT("Blue"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON,
			10, 80, 100, 30, hWnd, (HMENU)ID_R3, g_hInst, NULL);
		CheckRadioButton(hWnd, ID_R1, ID_R3, ID_R1);

		hList = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,
			140, 10, 180, 150, hWnd, (HMENU)ID_LISTBOX, g_hInst, NULL);
		for (int i = 0; i < 4; i++)
		{
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Width[i]);
		}
		SendMessage(hList, LB_SETCURSEL, (iCurrentWidth - 1) / 2, 0);
		return 0;
	case WM_KEYDOWN:
		switch (wParam){
		case VK_BACK:
			if (iLines != 0)
			{
				iLines--;
				lines[iLines].iCount = 0;
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_LISTBOX:
			switch (HIWORD(wParam)) {
			case LBN_SELCHANGE:
				iCurrentWidth = 1 + (2 * SendMessage(hList, LB_GETCURSEL, 0, 0));
				SetFocus(hWnd);
				break;
			}
			break;
		case IDM_RED: case ID_R1:
			iCurrentColor = RGB(255, 0, 0);
			CheckRadioButton(hWnd, ID_R1, ID_R3, ID_R1);
			SetFocus(hWnd);
			break;
		case IDM_GREEN: case ID_R2:
			iCurrentColor = RGB(0,255, 0);
			CheckRadioButton(hWnd, ID_R1, ID_R3, ID_R2);
			SetFocus(hWnd);
			break;
		case IDM_BLUE: case ID_R3:
			iCurrentColor = RGB(0, 0,255);
			CheckRadioButton(hWnd, ID_R1, ID_R3, ID_R3);
			SetFocus(hWnd);
			break;
		}
		return 0;
	case WM_LBUTTONDOWN:
		lines[iLines].iColor = iCurrentColor;
		lines[iLines].iWidth = iCurrentWidth;
		x=LOWORD(lParam);
		y=HIWORD(lParam);
		lines[iLines].p[lines[iLines].iCount].x = x;
		lines[iLines].p[lines[iLines].iCount].y = y;
		lines[iLines].iCount++;
		//iTempCount++;
		return 0;
	case WM_MOUSEMOVE:
		if (wParam & MK_LBUTTON) {  //왼쪽버튼을 누른상태로 움직이면, p.92
			hdc=GetDC(hWnd);
			hPen = CreatePen(PS_SOLID, iCurrentWidth, iCurrentColor);
			oldPen=(HPEN)SelectObject(hdc,hPen);
			MoveToEx(hdc,x,y,NULL);
			x=LOWORD(lParam);
			y=HIWORD(lParam);
			LineTo(hdc,x,y);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
			ReleaseDC(hWnd,hdc);
			//저장
			lines[iLines].p[lines[iLines].iCount].x = x;
			lines[iLines].p[lines[iLines].iCount].y = y;
			lines[iLines].iCount++;
			//iTempCount++;
		}
		return 0;
	case WM_LBUTTONUP:
		//선객체 하나 완성
		//lines[iLines].iCount = iTempCount;
		iLines++;
		lines[iLines].iCount = 0;
		//iTempCount = 0;
		return 0;
	case WM_LBUTTONDBLCLK:
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		for (int i = 0; i < iLines; i++)
		{
			hPen = CreatePen(PS_SOLID, iCurrentWidth, lines[i].iColor);
			oldPen=(HPEN)SelectObject(hdc, hPen);
			MoveToEx(hdc, lines[i].p[0].x, lines[i].p[0].y, NULL);
			for (int j = 1; j < lines[i].iCount; j++)
			{
				LineTo(hdc, lines[i].p[j].x, lines[i].p[j].y);
			}
			SelectObject(hdc, oldPen);// 단 선택 해제후 삭제
			DeleteObject(hPen); //내가 생성한 그리기 객체는 사용후 삭제
		}

		EndPaint(hWnd, &ps);
		return 0;

	}

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
