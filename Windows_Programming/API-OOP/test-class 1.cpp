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

//int px[1000], py[1000];

//typedef struct tagmyPOINT
///{
//	int  x;
//	int  y;
//} myPOINT;

//점들 - objects
// description---> class : Abstraction 
class pt {
public :
	int  x;
	int  y;
};

class mypoints : public pt
{
public: 
	pt p[1000];
	int iCount;
};

//myPOINT p[1000];
//int iCount;   //점의 개수

//실체화: instantiation
mypoints points;  // 정의한 클래스의 (instance, object) 선언해서 사용

LRESULT CALLBACK WndProcedure(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{  //Window Procedure      //window handle(메시지가 발생한)
	HDC hdc;
	PAINTSTRUCT ps;
	int x, y;
	HBRUSH hBrush;
	
	switch (iMessage) {
	case 0x0001://WM_CREATE:
		hWndMain = hWnd;
		return 0;
	case  WM_LBUTTONDOWN: //왼쪽버튼을 눌렀을때
		hdc = GetDC(hWnd);
		//x = LOWORD(lParam);  //Macro
		//x = (WORD)(lParam);  //casting  //형변환
		x = (unsigned short)(lParam);  //unsigned short 16bit integer
		//y = HIWORD(lParam);
		y = (unsigned short)((lParam) >>16);
	
		points.p[points.iCount].x = x;
		points.p[points.iCount].y = y;
		points.iCount++;

		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	
	case WM_PAINT:  // 화면을 다시 그려라 os가 보내는 MSG
		hdc = BeginPaint(hWnd, &ps);    //len = strlen(buf);  scanf("%d", &a);
		// 화면복구 routine
		hBrush = CreateSolidBrush(RGB(255, 0, 0));
		SelectObject(hdc, hBrush);
		for (int i = 0; i < points.iCount; i++)
		{
			Rectangle(hdc, points.p[i].x - 10, points.p[i].y - 10, 
				points.p[i].x + 10, points.p[i].y + 10);
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
