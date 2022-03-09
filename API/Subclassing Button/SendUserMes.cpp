#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("SendUserMes");

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

#define WM_SORI WM_USER+1
HWND hButton;
WNDPROC OldButtonProc;

LRESULT CALLBACK ButtonSubProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HWND hWndSori;
	switch(iMessage) {
//*
	case WM_LBUTTONUP: // case WM_LBUTTONDOWN: 은 이상하게 먹히네....
		hWndSori=FindWindow(NULL,TEXT("UserMes"));
		if (hWndSori==NULL) {
			MessageBox(hWnd,TEXT("UserMes 프로그램이 실행되어 있지 않습니다"),
				TEXT("이럴수가"),MB_OK);
		} else {
			SendMessage(hWndSori, WM_SORI, 0, 0);	// p.473 메시지 데드락 -> 값을 보내면 return될 때까지 기다린다.
			//PostMessage(hWndSori, WM_SORI, 0, 0);	// 바로 내려갔다가 올라온다. -> 값을 보내면 기다리지 않는다.(queue)
		}
		break;	//*/
/*
	case WM_LBUTTONDOWN:
		CallWindowProc(OldButtonProc, hWnd, iMessage, wParam, lParam);
		hWndSori = FindWindow(NULL, TEXT("UserMes"));
		if (hWndSori == NULL) {
			MessageBox(hWnd, TEXT("UserMes 프로그램이 실행되어 있지 않습니다"),
				TEXT("이럴수가"), MB_OK);
		}
		else {
			SendMessage(hWndSori, WM_SORI, 0, 0);
			SetFocus(hWndMain);	// main window로 focus를 준다
		}
		return 0;	//*/
	}
	return CallWindowProc(OldButtonProc,hWnd,iMessage,wParam,lParam);
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR *Mes=TEXT("UserMes 프로그램에게 메시지를 보냅니다");
	switch (iMessage) {
	case WM_CREATE:
		hButton = CreateWindow(TEXT("button"),TEXT("Click Me"),WS_CHILD | WS_VISIBLE |
			BS_PUSHBUTTON,20,20,100,25,hWnd,(HMENU)0,g_hInst,NULL);
		OldButtonProc = (WNDPROC)SetWindowLongPtr(hButton,GWLP_WNDPROC,(LONG_PTR)ButtonSubProc);
		return 0;
	  case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		TextOut(hdc,50,50,Mes,lstrlen(Mes));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}

