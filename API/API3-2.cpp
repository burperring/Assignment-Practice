#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Class");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	// ���� �ٲٴ� Ŭ����
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);									// �⺻
	// WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);						// ȸ��
	// WndClass.hbrBackground = (HBRUSH)CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 0));		// ������ ������ �ٵ��� ���
	// Ŀ�� �ٲٴ� Ŭ����
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x = 100;
	static int y = 100;
	static TCHAR *c = TEXT("A");		// ���ڿ� �ϳ� ����
	// static TCHAR c[] = TEXT("A");
	// static TCHAR c[] = ("A");
	static bool s = false;

	switch (iMessage) {
	case WM_CREATE:
		hWndMain = hWnd;
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			s ? c = TEXT("A") : c = TEXT("#");
			// s ? c[0] = TEXT('A') : c[0] = TEXT('#');
			// s ? strcpy(c, TEXT("A")) : strcpy(c, TEXT("#"));
			s = !s;
			break;
		case VK_LEFT:
			x -= 8;
			break;
		case VK_RIGHT:
			x += 8;
			break;
		case VK_UP:
			y -= 8;
			break;
		case VK_DOWN:
			y += 8;
			break;
		}
		// �ٽ� �׸��� true�ϰ�� �̵��Ҷ����� ������ ���ڰ� ������ ���ڰ� �̵��ϴ°� ó�� ����
		// ���� false�� ��� ���ڰ� �̵������� ������ �����ϴ� ���ڴ� �������� ����
		InvalidateRect(hWnd, NULL, true);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		TextOut(hdc, x, y,c, 1);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
