#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MyScrollBar");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
	  ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
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

#define ID_SCRRED 100
#define ID_SCRGREEN 101
#define ID_SCRBLUE 102
HWND hRed,hGreen,hBlue;
int Red,Green,Blue;
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH MyBrush, OldBrush;
	int TempPos;
	switch (iMessage) {
	case WM_CREATE:
		hRed=CreateWindow(TEXT("scrollbar"),NULL,WS_CHILD | WS_VISIBLE | SBS_HORZ,
			10,10,400,20,hWnd,(HMENU)ID_SCRRED,g_hInst,NULL);
		hGreen=CreateWindow(TEXT("scrollbar"),NULL,WS_CHILD | WS_VISIBLE | SBS_HORZ,
			10,40,400,20,hWnd,(HMENU)ID_SCRGREEN,g_hInst,NULL);
		hBlue=CreateWindow(TEXT("scrollbar"),NULL,WS_CHILD | WS_VISIBLE | SBS_HORZ,
			10,70,400,20,hWnd,(HMENU)ID_SCRBLUE,g_hInst,NULL);
		SetScrollRange(hRed,SB_CTL,0,255,TRUE);
		SetScrollPos(hRed,SB_CTL,0,TRUE);
		SetScrollRange(hGreen,SB_CTL,0,255,TRUE);
		SetScrollPos(hGreen,SB_CTL,0,TRUE);
		SetScrollRange(hBlue,SB_CTL,0,255,TRUE);
		SetScrollPos(hBlue,SB_CTL,0,TRUE);
		return 0;
	case WM_HSCROLL:
		if ((HWND)lParam == hRed) TempPos = Red;
		if ((HWND)lParam == hGreen) TempPos = Green;
		if ((HWND)lParam == hBlue) TempPos = Blue;
		switch (LOWORD(wParam)) {
		case SB_LINELEFT:
			TempPos=max(0,TempPos-1);
			break;
		case SB_LINERIGHT:
			TempPos=min(255,TempPos+1);
			break;
		case SB_PAGELEFT:
			TempPos=max(0,TempPos-10);
			break;
		case SB_PAGERIGHT:
			TempPos=min(255,TempPos+10);
			break;
		case SB_THUMBTRACK:
			TempPos=HIWORD(wParam);
			break;
		}
		if ((HWND)lParam == hRed) Red=TempPos;
		if ((HWND)lParam == hGreen) Green=TempPos;
		if ((HWND)lParam == hBlue) Blue=TempPos;
		SetScrollPos((HWND)lParam,SB_CTL,TempPos,TRUE);
		InvalidateRect(hWnd,NULL,FALSE);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		MyBrush=CreateSolidBrush(RGB(Red,Green,Blue));
		OldBrush=(HBRUSH)SelectObject(hdc,MyBrush);
		Rectangle(hdc,10,100,410,300);
		SelectObject(hdc,OldBrush);
		DeleteObject(MyBrush);
		EndPaint(hWnd,&ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
