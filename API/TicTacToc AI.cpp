#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass = TEXT("TicTacToe");

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

	hWndMain = hWnd;
	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

int pan[3][3];
int turn = 1;
int icount;
POINT moves[9] = { 1, 1, 0, 0, 2, 0, 0, 2, 2, 2, 1, 0, 0, 1, 2, 1, 1, 2 };

int winpoint(int a){
	if (pan[0][0] == a && pan[1][0] == a && pan[2][0] == a)
		return 1;
	else if (pan[0][1] == a && pan[1][1] == a && pan[2][1] == a)
		return 1;
	else if (pan[0][2] == a && pan[1][2] == a && pan[2][2] == a)
		return 1;
	else if (pan[0][0] == a && pan[0][1] == a && pan[0][2] == a)
		return 1;
	else if (pan[1][0] == a && pan[1][1] == a && pan[1][2] == a)
		return 1;
	else if (pan[2][0] == a && pan[2][1] == a && pan[2][2] == a)
		return 1;
	else if (pan[0][0] == a && pan[1][1] == a && pan[2][2] == a)
		return 1;
	else if (pan[2][0] == a && pan[1][1] == a && pan[0][2] == a)
		return 1;
	else
		return 0;

}
void init(HWND hWnd) {
	int i, j;
	turn = 1; //게임이 연속 될때를 대비해서
	icount = 0;
	for (i = 0; i<3; i++)
	for (j = 0; j<3; j++){
		pan[i][j] = 0;
	}
	InvalidateRect(hWnd, NULL, TRUE);
}
int findLose(int *x, int *y){
	int i, j;
	//사람이 둘수 있는 모든 곳을 둬본다. 
	for (i = 0; i<3; i++)
	for (j = 0; j<3; j++){
		if (pan[i][j] == 0){
			pan[i][j] = 1;
			if (winpoint(1)) { *x = i; *y = j; return 1; }
			else pan[i][j] = 0;
		}
	}
	return 0;
}

int findWin(int *x, int *y){

	//Computer가 둘수 있는 모든 곳을 둬본다. 
	for (int i = 0; i<3; i++)
	for (int j = 0; j<3; j++){
		if (pan[i][j] == 0){
			pan[i][j] = 2;
			if (winpoint(2)) { *x = i; *y = j; return 1; }
			else pan[i][j] = 0;
		}
	}
	return 0;
}

int computer(){
	int i;
	int x, y;

	// 우선 이기는 점을 찾아 둔다.
	if (findWin(&x, &y)){
		pan[x][y] = 2;
		return 1;

	}

	// 이기는 점이 없으면 적이 두면 지는 점을 찾아 둔다.
	if (findLose(&x, &y)){
		pan[x][y] = 2;
		return 0;

	}

	// 승패점이 없으면 마지막으로 중요한 점들중 우선하는 점을 찾아 둔다.
	for (i = 0; i<9; i++) {
		if (pan[moves[i].x][moves[i].y] == 0) {
			x = moves[i].x;
			y = moves[i].y;
			break;
		}
	}
	pan[x][y] = 2;
	return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT  rect;
	HBRUSH hBrush, oldBrush;
	int x, y;
	TCHAR buf[128];

	switch (iMessage) {
	case WM_LBUTTONDOWN:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);
		x = (LOWORD(lParam)) / (rect.right / 3);
		y = (HIWORD(lParam)) / (rect.bottom / 3);
		if (pan[x][y] == 0)
		{
			pan[x][y] = 1;
			icount++;
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);

			if (winpoint(1)){
				wsprintf(buf, TEXT("Human RED Win.\n   New Game ?"));

				if (MessageBox(hWnd, buf, TEXT("TicTacToe"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
					init(hWnd);
				else
					SendMessage(hWnd, WM_CLOSE, 0L, 0L);
				return 0;
			}
			else if (icount == 9){
				if (MessageBox(hWnd, TEXT("   Game Over.\n   New Game ?"), TEXT("TicTacToe"),
					MB_YESNO | MB_ICONEXCLAMATION) == IDYES){
					init(hWnd);
					turn = 1;
				}
				else
					SendMessage(hWnd, WM_CLOSE, 0L, 0L);
				return 0;
			}
			else{
				int ret = computer();
				icount++;
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);
				if (ret){
					wsprintf(buf, TEXT("   Computer GREEN Win.\n   New Game ?"));
					if (MessageBox(hWnd, buf, TEXT("TicTacToe"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
						init(hWnd);
					else
						SendMessage(hWnd, WM_CLOSE, 0L, 0L);
					return 0;
				}

				return 0;
			}
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		SetRect(&rect, rect.left, rect.top, rect.right, rect.bottom);

		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++)
				Rectangle(hdc, i*rect.right / 3, j*rect.bottom / 3, (i + 1) * rect.right / 3, (j + 1) * rect.bottom / 3);
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (pan[i][j] == 1)
				{
					hBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Ellipse(hdc, i*rect.right / 3, j*rect.bottom / 3, (i + 1) * rect.right / 3, (j + 1)*  rect.bottom / 3);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
				else if (pan[i][j] == 2){
					hBrush = (HBRUSH)CreateSolidBrush(RGB(0, 255, 0));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
					Ellipse(hdc, i*rect.right / 3, j*rect.bottom / 3, (i + 1) * rect.right / 3, (j + 1)*  rect.bottom / 3);
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				}
			}
		}


		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}