
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
	turn = 1; //������ ���� �ɶ��� ����ؼ�
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
	int score; // ���� ����
	int best; // �ְ� ����
	int position; // ���� ��ġ

	if (turn == 1) // ����� ���ʶ��
		best = 99; // �ְ������� ���� ���Ѵ� (�ּҰ��� ã�ƾ� �ϹǷ�)
	else // ��ǻ���� ���ʶ��
		best = -99; // �ְ������� ���� ���Ѵ� (�ִ밪�� ã�ƾ� �ϹǷ�)

	//if (depth == 0 || winpoint(1) || winpoint(2)) // �͹̳� ��� �̰ų�, ������ �Ѹ��� �̱���
	//	return evaluate(); // ���� ����� ������ �����
	//* ���� ����� ����� ���̿� ������� �׻� ���� ������ �Ű���. ���� �׻� ������ ���� ���� ����. �̸� �ذ��ϱ� ���� depth�� �����Ͽ� ��� ���̿� ���� �߿䵵�� �޶����� ��.
	if (depth == 0 || winpoint(1) || winpoint(2))
	return evaluate(depth);
	//*/

	for (int i = 0; i < 9; i++) // ��� ���� �� ������
	{
		if (pan[i % 3][i / 3] == 0) // ����ִ� ĭ�̶��
		{
			pan[i % 3][i / 3] = turn; // ���� ���ʿ� �´� ���� ���´�.
			
			if (turn == 1) // ����� ���ʶ��
				score = minimax(pos, depth - 1, 2); 
			    // depth�� 1 ���ҽ�Ű�� ��ǻ�� ���ʷ� �Ѿ�� minimax�� ��� 
			else // ��ǻ���� ���ʶ��
				score = minimax(pos, depth - 1, 1); // ����� ���ʷ� �Ѿ�� minimax�� ���
			
			pan[i % 3][i / 3] = 0; // ���� ���Ǿ����Ƿ� ���� �������� ������� �ǵ�����
			if (turn == 1) // ����� ���ʶ��
			{
				if (score < best) // �������� �ּҰ� �Ǵ°��� ã�� ����Ѵ�
				{
					best = score;
					position = i; // ������ġ ���
				}
			}
			else // ��ǻ���� ���ʶ��
			{
				if (score > best) // �������� �ִ밡 �Ǵ°��� ã�� ����Ѵ�
				{
					best = score;
					position = i; // ������ġ ���
				}
			}
		}
	}
	*pos = position; // ���������� ������ ��ġ�� �����Ѵ�.
	return best; // �������� ��ȯ�Ѵ�.
}

int computer(){ // ��ǻ�� �ΰ�����
	int depth = 0;
	int pos = 0;
	for (int i = 0; i < 9;i++)
	if (pan[i % 3][i / 3] == 0)
		depth++; // depth�� ���� ����ִ� ĭ�� ���� �����ȴ�.
	minimax(&pos, depth, 2); // ���� �̴ϸƽ� ȣ��. ������ ��ǻ���� �����̹Ƿ� turn�� 2�� �ȴ�.
	pan[pos % 3][pos / 3] = 2; // �̴ϸƽ��� ���� ������ġ�� ��ǻ���� ���� ���´�.
	if (winpoint(2)) // ��ǻ�Ͱ� �̰�ٸ�
		return 1; // 1�� ��ȯ
	else // �װ� �ƴϸ�
		return 0; // 0�� ��ȯ
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
			pan[x][y] = 1; // ���
			icount++;
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			
			if (winpoint(1)){ // ����� �̱���� Ȯ��
				wsprintf(buf, TEXT("Human RED Win.\n   New Game ?"));
				
				if (MessageBox(hWnd, buf, TEXT("TicTacToe"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
					init(hWnd);
				else
					SendMessage(hWnd, WM_CLOSE, 0L, 0L);
				return 0;
			}
			else if (icount == 9){ // �� ���� ���� ��
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
				// ��ǻ�Ͱ� �� ���� Ž��
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