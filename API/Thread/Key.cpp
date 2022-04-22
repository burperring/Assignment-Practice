#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Key");
HWND MainWnd;

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
	MainWnd = hWnd;

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
TCHAR str[256];

struct ThreadParam {
	int x, y;
	TCHAR ch;
} Param[4] = {
	{ 10, 10, TEXT('a') },
	{ 10, 30, TEXT('b') },
	{ 10, 50, TEXT('c') },
	{ 10, 70, TEXT('d') }
};

DWORD WINAPI ThreadFunc(LPVOID temp)//함수포인트
{
	HDC hdc;
	int len;
	int aCount = 0;

	//temp가 void이므로 ThreadParam 형태로 만듬
	ThreadParam *P = (ThreadParam *)temp;

	TCHAR tmp[256];

	hdc = GetDC(MainWnd);
	len = lstrlen(str);
	for (int i = 0; i < len; i++)
	{
		if (str[i] == P->ch)
			aCount++;
	}
	wsprintf(tmp, TEXT("%c의 개수 : %d"), P->ch, aCount);
	TextOut(hdc, P->x, P->y, tmp, lstrlen(tmp));
	ReleaseDC(MainWnd, hdc);
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	DWORD ThreadID;
	//HANDLE hThread[4];
	HANDLE hThread;
	PAINTSTRUCT ps;
	int len;

	switch (iMessage) {
	case WM_CHAR:
		len = lstrlen(str);
		str[len] = (TCHAR)wParam;
		str[len + 1] = 0;
		InvalidateRect(hWnd, NULL, FALSE);//무효영역 발생(다시 그려야 할 영역)
		//for (int i = 0; i < 4; i++){
		//	hThread[i] = CreateThread(NULL, 0, ThreadFunc, &Param[i], 0, &ThreadID);
		//	CloseHandle(hThread[i]);
		//}
		CreateThread(NULL, 0, ThreadFunc, &Param[0], 0, &ThreadID);
		//CloseHandle(hThread);
		CreateThread(NULL, 0, ThreadFunc, &Param[1], 0, &ThreadID);
		//CloseHandle(hThread);
		hThread = CreateThread(NULL, 0, ThreadFunc, &Param[2], 0, &ThreadID);
		//CloseHandle(hThread);
		hThread = CreateThread(NULL, 0, ThreadFunc, &Param[3], 0, &ThreadID);
		//CloseHandle(hThread);
		return 0;
	case WM_LBUTTONDOWN:
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, 100, 100, str, lstrlen(str));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
