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
	case WM_LBUTTONUP: // case WM_LBUTTONDOWN: �� �̻��ϰ� ������....
		hWndSori=FindWindow(NULL,TEXT("UserMes"));
		if (hWndSori==NULL) {
			MessageBox(hWnd,TEXT("UserMes ���α׷��� ����Ǿ� ���� �ʽ��ϴ�"),
				TEXT("�̷�����"),MB_OK);
		} else {
			SendMessage(hWndSori, WM_SORI, 0, 0);	// p.473 �޽��� ����� -> ���� ������ return�� ������ ��ٸ���.
			//PostMessage(hWndSori, WM_SORI, 0, 0);	// �ٷ� �������ٰ� �ö�´�. -> ���� ������ ��ٸ��� �ʴ´�.(queue)
		}
		break;	//*/
/*
	case WM_LBUTTONDOWN:
		CallWindowProc(OldButtonProc, hWnd, iMessage, wParam, lParam);
		hWndSori = FindWindow(NULL, TEXT("UserMes"));
		if (hWndSori == NULL) {
			MessageBox(hWnd, TEXT("UserMes ���α׷��� ����Ǿ� ���� �ʽ��ϴ�"),
				TEXT("�̷�����"), MB_OK);
		}
		else {
			SendMessage(hWndSori, WM_SORI, 0, 0);
			SetFocus(hWndMain);	// main window�� focus�� �ش�
		}
		return 0;	//*/
	}
	return CallWindowProc(OldButtonProc,hWnd,iMessage,wParam,lParam);
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR *Mes=TEXT("UserMes ���α׷����� �޽����� �����ϴ�");
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

