// C++ -> Win32 프로젝트, 솔루션x -> window 응용프로그램, 빈 프로젝트
// 메뉴버튼 ID 넣어줄때 Popup False로 바꿔주면 된다. -> ID_DIALOG
// 단축키 생성 : 리소스 -> 우클릭 리소스추가 -> 엑셀러레이터
#include <windows.h>
#include "resource.h"
// #include<tchar.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
void PaintTheBlock(HWND, COLORREF, int);

HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("Mouse");

typedef struct _Line
{
	COLORREF iColor;
	int iCount;
	int iWidth;
	POINT p[1000];
}Line;

Line lines[1000];
int iLineCount;
COLORREF iCurrentColor = RGB(0,0,0);
int iCurrentWidth = 1;

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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
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
TCHAR *Items[] = { TEXT("1"), TEXT("2"), TEXT("3"), TEXT("4"),
TEXT("5"), TEXT("6") };
HWND r1, r2, r3;
HWND hCombo,hRed,hGreen,hBlue,hsRed,hsGreen,hsBlue,hPaint;

#include "resource.h"
BOOL CALLBACK DlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static int Red, Green, Blue;
	static COLORREF iColor; 	static int iWidth;
	int TempPos; TCHAR str[128];
	switch (iMessage) {
	case WM_INITDIALOG:
		iWidth = iCurrentWidth;
		hPaint = GetDlgItem(hDlg, IDC_PAINT);
		hCombo = GetDlgItem(hDlg, IDC_COMBO1);
		hRed = GetDlgItem(hDlg, IDC_SCROLLBAR1);
		hGreen = GetDlgItem(hDlg, IDC_SCROLLBAR2);
		hBlue = GetDlgItem(hDlg, IDC_SCROLLBAR3);
		//hsRed = GetDlgItem(hDlg, IDC_STATIC1);//Test OK
		hsGreen = GetDlgItem(hDlg, IDC_STATIC2);
		hsBlue = GetDlgItem(hDlg, IDC_STATIC3);
		for (int i = 0; i < 6; i++) {
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)Items[i]);
		}
		//SendMessage(hCombo, CB_SETCURSEL, iWidth - 1, 0);
		SetDlgItemInt(hDlg, IDC_COMBO1, iCurrentWidth, FALSE);
		Red = GetRValue(iCurrentColor);
		Green = GetGValue(iCurrentColor);
		Blue = GetBValue(iCurrentColor);
		SetScrollRange(hRed, SB_CTL, 0, 255, TRUE);
		SetScrollPos(hRed, SB_CTL,Red, TRUE);
		SetScrollRange(hGreen, SB_CTL, 0, 255, TRUE);
		SetScrollPos(hGreen, SB_CTL, Green, TRUE);
		SetScrollRange(hBlue, SB_CTL, 0, 255, TRUE);
		SetScrollPos(hBlue, SB_CTL, Blue, TRUE);
		wsprintf(str, "R:%d", Red);
		SetDlgItemText(hDlg, IDC_STATIC1,str);
		wsprintf(str, "G:%d", Green);
		SetWindowText(hsGreen, str);
		wsprintf(str, "B:%d", Blue);
		SetWindowText(hsBlue, str);
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			iCurrentWidth = iWidth;
			iCurrentColor = iColor;
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
				InvalidateRect(hDlg, NULL, TRUE);		// 삐져나오는 그림을 없애준다.
				break;
			/*case CBN_EDITCHANGE:											// 입력받은 값의 굵기로 지정
				iWidth = GetDlgItemInt(hDlg, IDC_COMBO1, NULL, FALSE);		// 없애면 아무리 입력해도 해당 굵기로 지정 불가능
				PaintTheBlock(hPaint, iColor, iWidth);
				InvalidateRect(hDlg, NULL, TRUE);
				break;*/				
			}
			return TRUE;
		}
		return TRUE;
	case WM_HSCROLL:
		/*	if ((HWND)lParam == hRed) temp = r;
			if ((HWND)lParam == hGreen) temp = g;
			if ((HWND)lParam == hBlue) temp = b;*/
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
		if ((HWND)lParam == hGreen)  Green = TempPos;
		if ((HWND)lParam == hBlue) Blue = TempPos;
		SetScrollPos((HWND)lParam, SB_CTL, TempPos, TRUE);
		wsprintf(str, "R:%d", Red);
		SetDlgItemText(hDlg, IDC_STATIC1, str);
		wsprintf(str, "G:%d", Green);
		SetWindowText(hsGreen, str);
		wsprintf(str, "B:%d", Blue);
		SetWindowText(hsBlue, str);
		iColor = RGB(Red, Green, Blue);
		PaintTheBlock(hPaint, iColor, iWidth);
		
		//InvalidateRect(hDlg, NULL, TRUE);
		return TRUE;
	case WM_PAINT:
		PaintTheBlock(hPaint, iColor, iWidth);
		break;
	}
	return FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HPEN MyPen;
	static int x;
	static int y;

	switch (iMessage) {
	case WM_CREATE:
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_DIALOG:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProc);	//대화상자 불러오기
			break;
		}
		return 0;
	case WM_LBUTTONDOWN:
		x=LOWORD(lParam);
		y=HIWORD(lParam);
		return 0;
	case WM_MOUSEMOVE:
		if (wParam & MK_LBUTTON) {
			hdc = GetDC(hWnd);
			MyPen = CreatePen(PS_SOLID, iCurrentWidth, iCurrentColor);
			MyPen = reinterpret_cast<HPEN>(SelectObject(hdc, MyPen));
			MoveToEx(hdc, x, y, NULL);
			lines[iLineCount].iColor = iCurrentColor;
			lines[iLineCount].iWidth = iCurrentWidth;
			lines[iLineCount].p[lines[iLineCount].iCount].x = x;
			lines[iLineCount].p[lines[iLineCount].iCount].y = y;
			lines[iLineCount].iCount++;
			x = LOWORD(lParam);
			y = HIWORD(lParam);
			LineTo(hdc, x, y);
			DeleteObject(SelectObject(hdc,MyPen));
			ReleaseDC(hWnd, hdc);
		}
		return 0;
	case WM_LBUTTONUP:
		iLineCount++;
		return 0;
	case WM_LBUTTONDBLCLK:
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < iLineCount; i++)
		{
			MyPen = CreatePen(PS_SOLID, lines[i].iWidth, lines[i].iColor);
			MyPen = (HPEN)SelectObject(hdc, MyPen);
			MoveToEx(hdc, lines[i].p[0].x, lines[i].p[0].y, NULL);
			for (int j = 0; j < lines[i].iCount - 1; j++)
			{
				LineTo(hdc, lines[i].p[j + 1].x, lines[i].p[j + 1].y);
			}
			DeleteObject(SelectObject(hdc, MyPen));
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
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
	MoveToEx(hdc, rect.left, rect.top, NULL);
	LineTo(hdc, rect.right, rect.bottom);
	DeleteObject(SelectObject(hdc, hPen));
	ReleaseDC(hWnd, hdc);
}