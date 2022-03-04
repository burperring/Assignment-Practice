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
	COLORREF iColor;
	int iWidth;
} line;

line lines[300];
int iLines;

int iTempCount;

COLORREF iCurrentColor = RGB(255, 0, 0);  //default
int iCurrentWidth = 5; //default
HWND hList;

TCHAR *Items[] = { TEXT("1"), TEXT("3"), TEXT("5"), TEXT("7") };

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HWND hList;
	switch (iMessage) {
	case WM_INITDIALOG:
		hList = GetDlgItem(hDlg, IDC_LIST1); //p.238하단
		for (int i = 0; i<4; i++) {
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
		SendMessage(hList, LB_SETCURSEL, (iCurrentWidth - 1) / 2, 0);  //수정
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			iCurrentWidth = 1 + (2 * SendMessage(hList, LB_GETCURSEL, 0, 0));
			EndDialog(hDlg, IDOK);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

//enum { ID_R1 = 101, ID_R2, ID_R3, ID_R4, ID_R5, ID_R6 };
//HWND r1, r2, r3, r4, r5, r6;
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

	/*	for (int i = 0; i<4; i++) {
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
		SendMessage(hList, LB_SETCURSEL, (iCurrentWidth-1)/2, 0);  //수정
*/
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
	/*	case ID_LISTBOX:
			switch (HIWORD(wParam)) {
			case LBN_SELCHANGE:
				iCurrentWidth = 1 + (2 * SendMessage(hList, LB_GETCURSEL, 0, 0));
				break;
			}
			break;
			*/
		case IDM_DIALOG:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, AboutDlgProc);
			break;
		case IDM_RED: 
			iCurrentColor = RGB(255, 0, 0);
			break;
		case IDM_GREEN: 
			iCurrentColor = RGB(0,255, 0);
			break;
		case IDM_BLUE: 
			iCurrentColor = RGB(0, 0,255);
			break;
		}
		return 0;
	case WM_LBUTTONDOWN:
		lines[iLines].iColor = iCurrentColor;
		lines[iLines].iWidth = iCurrentWidth;
		x=LOWORD(lParam);
		y=HIWORD(lParam);
		lines[iLines].p[iTempCount].x = x;
		lines[iLines].p[iTempCount].y = y;
		iTempCount++;
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
			lines[iLines].p[iTempCount].x = x;
			lines[iLines].p[iTempCount].y = y;
			iTempCount++;
		}
		return 0;
	case WM_LBUTTONUP:
		//선객체 하나 완성
		lines[iLines].iCount = iTempCount;
		iLines++;
		iTempCount = 0;
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
			hPen = CreatePen(PS_SOLID, lines[i].iWidth, lines[i].iColor);
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
