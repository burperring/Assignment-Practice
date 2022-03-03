#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MyListBox");

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

#define ID_LISTBOX 100
TCHAR *Items[]={TEXT("Apple"),TEXT("Orange"),TEXT("Melon"),TEXT("Grape"),
	TEXT("Strawberry")};
//TCHAR *Items[]={TEXT("3"),TEXT("8"),TEXT("10")};
//int w[3]={3,8,10};
HWND hList;
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	int i;
	TCHAR str[128];
	switch (iMessage) {
	case WM_CREATE:
		hList=CreateWindow(TEXT("listbox"),NULL,WS_CHILD | WS_VISIBLE | WS_BORDER |
			LBS_NOTIFY,10,10,100,200,hWnd,(HMENU)ID_LISTBOX,g_hInst,NULL);
		for (i=0;i<5;i++) {
			SendMessage(hList,LB_ADDSTRING,0,(LPARAM)Items[i]);
		}
		// defualt 값 설정해주기
		SendMessage(hList, LB_SETCURSEL,0,0);
		SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(ID_LISTBOX, LBN_SELCHANGE),0);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_LISTBOX:
			switch (HIWORD(wParam)) {
			case LBN_SELCHANGE:
				i=SendMessage(hList, LB_GETCURSEL,0,0);
				//iCurrrentWidth=w[i];
				SendMessage(hList, LB_GETTEXT, i, (LPARAM)str);
				SetWindowText(hWnd, str);
				break;
			}
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
