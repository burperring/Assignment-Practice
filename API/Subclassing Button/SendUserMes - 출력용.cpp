#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("SendUserMes");

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
	  ,LPSTR lpszCmdParam,int nCmdShow)
{

}

#define WM_SORI WM_USER+1
HWND hButton;
WNDPROC OldButtonProc;

LRESULT CALLBACK ButtonSubProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HWND hWndSori;
	switch(iMessage) {
	case WM_LBUTTONUP: // case WM_LBUTTONDOWN: 은 이상하게 먹히네....
		hWndSori=FindWindow(NULL,TEXT("UserMes"));
		if (hWndSori==NULL) {
			MessageBox(hWnd,TEXT("UserMes 프로그램이 실행되어 있지 않습니다"),
				TEXT("이럴수가"),MB_OK);
		} else {
			SendMessage(hWndSori,WM_SORI,0,0);
		}
		break;
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

