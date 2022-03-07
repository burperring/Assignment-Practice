
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

int evaluate(int depth = 0)
{
	if (winpoint(2))
		return 10 + depth;
	else if (winpoint(1))
		return -10 - depth;
	else
		return 0;
}

int minimax(int *pos, int depth, int turn)
{
	int score; // 현재 점수
	int best; // 최고 점수
	int position; // 최적 위치

	if (turn == 1) // 사람의 차례라면
		best = 99; // 최고점수는 양의 무한대 (최소값을 찾아야 하므로)
	else // 컴퓨터의 차례라면
		best = -99; // 최고점수는 음의 무한대 (최대값을 찾아야 하므로)

	//if (depth == 0 || winpoint(1) || winpoint(2)) // 터미널 노드 이거나, 누군가 한명이 이길경우
	//	return evaluate(); // 현재 노드의 점수를 계산함
	//* 위의 방식은 노드의 깊이에 관계없이 항상 같은 점수를 매겨줌. 따라서 항상 최적의 수를 두지 못함. 이를 해결하기 위해 depth를 전달하여 노드 깊이에 따라 중요도가 달라지게 함.
	if (depth == 0 || winpoint(1) || winpoint(2))
	return evaluate(depth);
	//*/

	for (int i = 0; i < 9; i++) // 모든 판을 다 조사함
	{
		if (pan[i % 3][i / 3] == 0) // 비어있는 칸이라면
		{
			pan[i % 3][i / 3] = turn; // 현재 차례에 맞는 돌을 놓는다.
			
			if (turn == 1) // 사람의 차례라면
				score = minimax(pos, depth - 1, 2); 
			    // depth를 1 감소시키고 컴퓨터 차례로 넘어가서 minimax값 계산 
			else // 컴퓨터의 차례라면
				score = minimax(pos, depth - 1, 1); // 사람의 차례로 넘어가서 minimax값 계산
			
			pan[i % 3][i / 3] = 0; // 값이 계산되었으므로 돌을 놓은것을 원래대로 되돌린다
			if (turn == 1) // 사람의 차례라면
			{
				if (score < best) // 최적값은 최소가 되는것을 찾아 기록한다
				{
					best = score;
					position = i; // 최적위치 기록
				}
			}
			else // 컴퓨터의 차례라면
			{
				if (score > best) // 최적값은 최대가 되는것을 찾아 기록한다
				{
					best = score;
					position = i; // 최적위치 기록
				}
			}
		}
	}
	*pos = position; // 최종적으로 결정된 위치를 선택한다.
	return best; // 최적값을 반환한다.
}

int computer(){ // 컴퓨터 인공지능
	int depth = 0;
	int pos = 0;
	for (int i = 0; i < 9;i++)
	if (pan[i % 3][i / 3] == 0)
		depth++; // depth는 현재 비어있는 칸의 수로 결정된다.
	minimax(&pos, depth, 2); // 최초 미니맥스 호출. 지금은 컴퓨터의 차례이므로 turn은 2가 된다.
	pan[pos % 3][pos / 3] = 2; // 미니맥스로 얻은 최적위치에 컴퓨터의 돌을 놓는다.
	if (winpoint(2)) // 컴퓨터가 이겼다면
		return 1; // 1을 반환
	else // 그게 아니면
		return 0; // 0을 반환
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
		x = (LOWORD(lParam)) / (rect.right/3);
		y = (HIWORD(lParam)) / (rect.bottom/3);
		if (pan[x][y] == 0)
		{
			pan[x][y] = 1; // 사람
			icount++;
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			
			if (winpoint(1)){ // 사람이 이기는지 확인
				wsprintf(buf, TEXT("Human RED Win.\n   New Game ?"));
				
				if (MessageBox(hWnd, buf, TEXT("TicTacToe"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
					init(hWnd);
				else
					SendMessage(hWnd, WM_CLOSE, 0L, 0L);
				return 0;
			}
			else if (icount == 9){ // 둘 곳이 없을 때
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
				// 컴퓨터가 둘 곳을 탐색
				int ret=computer();
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
				Rectangle(hdc, i*rect.right / 3, j*rect.bottom / 3, (i+1) * rect.right/3, (j+1) * rect.bottom / 3);
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