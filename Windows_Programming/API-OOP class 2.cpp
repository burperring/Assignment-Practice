#include <windows.h>

LRESULT CALLBACK WndProcedure(HWND, UINT, WPARAM, LPARAM);
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
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProcedure;
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

class pt {
public :
//protected:
	int  x;
	int  y;
};

class mypoints : public pt
{
//public: 
	pt p[1000];
	int iCount;
public:
	void Add(int x, int y)
	{
		p[iCount].x = x;
		p[iCount].y = y;
		iCount++;
	}
	void Draw(HDC hdc)
	{
		HBRUSH hBrush;
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, hBrush);
		for (int i = 0; i < iCount; i++)
		{
			Rectangle(hdc, p[i].x - 10, p[i].y - 10,
				p[i].x + 10, p[i].y + 10);
		}
	}
};


//myPOINT p[1000];
//int iCount;   //���� ����
mypoints points;

LRESULT CALLBACK WndProcedure(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{  //Window Procedure      //window handle(�޽����� �߻���)
	HDC hdc;
	PAINTSTRUCT ps;
	int x, y;
	HBRUSH hBrush;
	
	switch (iMessage) {
	case 0x0001://WM_CREATE:
		hWndMain = hWnd;
		return 0;
	case  WM_LBUTTONDOWN: //���ʹ�ư�� ��������
		hdc = GetDC(hWnd);
		x = LOWORD(lParam);  //Macro
		y = HIWORD(lParam);
	//	points.p[points.iCount].x = x;
	//	points.p[points.iCount].y = y;
		points.Add(x,y);
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	
	case WM_PAINT:  // ȭ���� �ٽ� �׷��� os�� ������ MSG
		hdc = BeginPaint(hWnd, &ps);    //len = strlen(buf);  scanf("%d", &a);
		// ȭ�麹�� routine
		points.Draw(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
