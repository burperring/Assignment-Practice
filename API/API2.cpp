#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("Class");

// ������ . . . Entry Point		ex) c++�� main()
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
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

int px[1000], py[1000];
int iCount = 0;		// �׷��� ���� ����
// Window Procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int x, y;
	HBRUSH hBrush;

	// Message(Event) Driven Architecture
	switch (iMessage) {
	case WM_CREATE:
		hWndMain = hWnd;
		return 0;
	case WM_LBUTTONDOWN:							// ���� ���콺��ư�� ������
		hdc = GetDC(hWnd);							// �����쿡 �޷��ִ� �׸��⵵������(DC) ���
		// x = LOWORD(lParam);						// ���� ���콺��ư���� ���� ��ǥ�� X��ġ (��ũ��)
		px[iCount] = x = (WORD)(lParam);			// ���� �����ǹ�
		// y = HIWORD(lParam);						// ���� ���콺��ư���� ���� ��ǥ�� Y��ġ (��ũ��)
		py[iCount] = y = (WORD)((lParam) >> 16);	// ���� �����ǹ�
		iCount++;
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, hBrush);
		// Rectangle(hdc, x - 10, y - 10, x + 10, y + 10);	// �簢���� �׷��� (�׸��� API)
		Ellipse(hdc, x - 10, y - 10, x + 10, y + 10);		// ���� �׷���
		ReleaseDC(hWnd, hdc);								// DC�� ���������
		return 0;
	case WM_PAINT:					// �ٽ� �׷���
		hdc = BeginPaint(hWnd, &ps);					// DC�� ����
		for (int i = 0; i < iCount; i++)
		{
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
			Ellipse(hdc, px[i] - 10, py[i] - 10, px[i] + 10, py[i] + 10);
		}
		EndPaint(hWnd, &ps);							// DC�� �����϶�
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
