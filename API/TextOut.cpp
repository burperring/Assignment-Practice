#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TextOut");

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
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
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

//*
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	// const TCHAR* str = TEXT("Beautiful Korea");		// 문자열의 주소를 반환
	const TCHAR str[] = TEXT("Beautiful Korea");		//

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);
		TextOut(hdc, 100, 100, str, 15);
		ReleaseDC(hWnd, hdc);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
//*/

/*
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		TextOut(hdc,100,100,TEXT("Beautiful Korea"),15);
		EndPaint(hWnd,&ps);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/

/*
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		SetTextAlign(hdc, TA_CENTER);
		TextOut(hdc,200,60,TEXT("Beautiful Korea"),15);
		TextOut(hdc,200,80,TEXT("is My"),5);
		TextOut(hdc,200,100,TEXT("Lovely Home Country"),19);
		EndPaint(hWnd,&ps);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/

/*
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		SetTextAlign(hdc, TA_UPDATECP);
		TextOut(hdc,200,60,TEXT("One "),4);
		TextOut(hdc,200,80,TEXT("Two "),4);
		TextOut(hdc,200,100,TEXT("Three"),5);
		EndPaint(hWnd,&ps);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/