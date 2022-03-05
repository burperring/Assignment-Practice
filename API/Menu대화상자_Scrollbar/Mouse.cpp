#include <windows.h>
#include <tchar.h>
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

COLORREF iCurrentColor = RGB(0, 0, 0);  //default
int iCurrentWidth = 1; //default

TCHAR *Items[] = { TEXT("1"), TEXT("3"), TEXT("5"), TEXT("7") };

HWND r1, r2, r3;
HWND hCombo, hRed, hGreen, hBlue, hsRed, hsGreen, hsBlue, hPaint;

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int TempPos;
	static int iWidth;
	static COLORREF iColor;
	static int Red, Green, Blue;
	TCHAR str[128];

	switch (iMessage) {
	case WM_INITDIALOG://p.238 하단
		hCombo = GetDlgItem(hDlg,IDC_COMBO1);
		for (int i = 0; i<4; i++) {
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
		//SendMessage(hCombo, CB_SETCURSEL, (iCurrentWidth - 1) / 2, 0);  //수정
		//p.240 하단
		SetDlgItemInt(hDlg, IDC_COMBO1, iCurrentWidth, FALSE);

		iWidth = iCurrentWidth;
		hPaint = GetDlgItem(hDlg, IDC_PAINT);
		hCombo = GetDlgItem(hDlg, IDC_COMBO1);
		hRed = GetDlgItem(hDlg, IDC_SCROLLBAR1);
		hGreen = GetDlgItem(hDlg, IDC_SCROLLBAR2);
		hBlue = GetDlgItem(hDlg, IDC_SCROLLBAR3);

		Red = GetRValue(iCurrentColor);
		Green = GetGValue(iCurrentColor);
		Blue = GetBValue(iCurrentColor);

		SetScrollRange(hRed, SB_CTL, 0, 255, TRUE);
		SetScrollPos(hRed, SB_CTL, Red, TRUE);
		SetScrollRange(hGreen, SB_CTL, 0, 255, TRUE);
		SetScrollPos(hGreen, SB_CTL, Green, TRUE);
		SetScrollRange(hBlue, SB_CTL, 0, 255, TRUE);
		SetScrollPos(hBlue, SB_CTL, Blue, TRUE);

		wsprintf(str, "R:%d", Red);
		SetDlgItemText(hDlg, IDC_STATIC1, str);
		wsprintf(str, "G:%d", Green);
		SetDlgItemText(hDlg, IDC_STATIC2, str);
		wsprintf(str, "B:%d", Blue);
		SetDlgItemText(hDlg, IDC_STATIC3, str);

		return TRUE;

	case WM_HSCROLL:
		TempPos = GetScrollPos((HWND)lParam, SB_CTL);
		switch (LOWORD(wParam)) {
		case SB_LINELEFT:
			TempPos = max(0, TempPos - 1);
			break;
		case SB_LINERIGHT:
			TempPos = min(255, TempPos + 1);
			break;
		case SB_PAGELEFT:
			TempPos = max(0, TempPos - 10);
			break;
		case SB_PAGERIGHT:
			TempPos = min(255, TempPos + 10);
			break;
		case SB_THUMBTRACK:
			TempPos = HIWORD(wParam);
			break;
		}
		if ((HWND)lParam == hRed) Red = TempPos;
		if ((HWND)lParam == hGreen) Green = TempPos;
		if ((HWND)lParam == hBlue) Blue = TempPos;
		SetScrollPos((HWND)lParam, SB_CTL, TempPos, TRUE);

		wsprintf(str, "R:%d", Red);
		SetDlgItemText(hDlg, IDC_STATIC1, str);
		wsprintf(str, "G:%d", Green);
		SetDlgItemText(hDlg, IDC_STATIC2, str);
		wsprintf(str, "B:%d", Blue);
		SetDlgItemText(hDlg, IDC_STATIC3, str);

		return TRUE;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			//iCurrentWidth = 1 + (2 * SendMessage(hCombo, CB_GETCURSEL, 0, 0));
			iCurrentWidth=GetDlgItemInt(hDlg, IDC_COMBO1, NULL, FALSE);
			iCurrentColor = RGB(Red, Green, Blue);
			EndDialog(hDlg, IDOK);
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return TRUE;
		case IDC_COMBO1:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				iWidth = SendMessage(hCombo, CB_GETCURSEL, 0, 0) + 1;
				PaintTheBlock(hPaint, iColor, iWidth);
				break;
			case CBN_EDITCHANGE:
				iWidth = GetDlgItemInt(hDlg, IDC_COMBO1, NULL, FALSE);
				PaintTheBlock(hPaint, iColor, iWidth);
				break;
			}
		}
		break;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x;
	static int y;
	//static BOOL bNowDraw=FALSE;
	HPEN hPen, oldPen;
	TCHAR str[128];
	switch (iMessage) {
	case WM_CREATE:

		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
/*		case ID_COMBOBOX:
			switch (HIWORD(wParam)) {
			case CBN_SELCHANGE:
				iCurrentWidth = 1 + (2 * SendMessage(hCombo, CB_GETCURSEL, 0, 0));
				break;
			case CBN_EDITCHANGE:
				GetWindowText(hCombo, str, 128);
				iCurrentWidth = _ttoi(str);
				break;
			}
			break; // 없으면 콤보박스가 내려가지 않는다.
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


	case WM_INITMENU:
		if (iCurrentColor == RGB(255, 0, 0)){
			CheckMenuItem((HMENU)wParam, IDM_RED, MF_BYCOMMAND | MF_CHECKED);
			CheckMenuItem((HMENU)wParam, IDM_GREEN, MF_BYCOMMAND | MF_UNCHECKED);
			CheckMenuItem((HMENU)wParam, IDM_BLUE, MF_BYCOMMAND | MF_UNCHECKED);
		}
		else if (iCurrentColor == RGB(0, 255, 0)){
			CheckMenuItem((HMENU)wParam, IDM_RED, MF_BYCOMMAND | MF_UNCHECKED);
			CheckMenuItem((HMENU)wParam, IDM_GREEN, MF_BYCOMMAND | MF_CHECKED);
			CheckMenuItem((HMENU)wParam, IDM_BLUE, MF_BYCOMMAND | MF_UNCHECKED);
		}
		else if (iCurrentColor == RGB(0, 0, 255)){
			CheckMenuItem((HMENU)wParam, IDM_RED, MF_BYCOMMAND | MF_UNCHECKED);
			CheckMenuItem((HMENU)wParam, IDM_GREEN, MF_BYCOMMAND | MF_UNCHECKED);
			CheckMenuItem((HMENU)wParam, IDM_BLUE, MF_BYCOMMAND | MF_CHECKED);
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

void PaintTheBlock(HWND hWnd, COLORREF color, int width)
{
	HDC hdc;
	HPEN hPen;
	RECT rect;

	InvalidateRect(hWnd, NULL, TRUE);
	UpdateWindow(hWnd);

	hdc = GetDC(hWnd);
	GetClientRect(hWnd, &rect);
	hPen = CreatePen(PS_SOLID, width, color);
	hPen = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, rect.left, rect.bottom / 2, NULL);
	LineTo(hdc, rect.right, rect.bottom / 2);
	DeleteObject(SelectObject(hdc, hPen));
	ReleaseDC(hWnd, hdc);
}