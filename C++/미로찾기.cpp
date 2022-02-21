#include<iostream>
#include<conio.h>

using namespace std;

/*
0 : 벽
1 : 길
2 : 시작점
3 : 도착점
*/

struct _tagPoint
{
	int x;
	int y;
};

// typedef : 타입을 재정의하는 기능이다.
typedef _tagPoint	POINT;
typedef _tagPoint*  PPOINT;

void SetMaze(char Maze[21][21], PPOINT pPlayerPos, PPOINT pStartPos, PPOINT pEndPos)
{
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	*pPlayerPos = *pStartPos;

	strcpy_s(Maze[0],  "21100000000000000000");
	strcpy_s(Maze[1],  "00111111111100000000");
	strcpy_s(Maze[2],  "00100010000111111110");
	strcpy_s(Maze[3],  "01100010000000000010");
	strcpy_s(Maze[4],  "01000011100011111110");
	strcpy_s(Maze[5],  "01000000011110000000");
	strcpy_s(Maze[6],  "01100000010000000000");
	strcpy_s(Maze[7],  "00100000011111100110");
	strcpy_s(Maze[8],  "00011111000000100100");
	strcpy_s(Maze[9],  "00010001111111100100");
	strcpy_s(Maze[10], "01110001000000111100");
	strcpy_s(Maze[11], "01000001000001000000");
	strcpy_s(Maze[12], "01000001111111011110");
	strcpy_s(Maze[13], "01000000000000010010");
	strcpy_s(Maze[14], "01000000000111110010");
	strcpy_s(Maze[15], "01111111111100010010");
	strcpy_s(Maze[16], "00000100000000010010");
	strcpy_s(Maze[17], "01000100000000010010");
	strcpy_s(Maze[18], "01111100000000011010");
	strcpy_s(Maze[19], "00000000000000000013");
}

void Output(char Maze[21][21], PPOINT pPlayerPos)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (pPlayerPos->x == j && pPlayerPos->y == i)
				cout << "☆";
			else if (Maze[i][j] == '0')
				cout << "■";
			else if (Maze[i][j] == '1')
				cout << "  ";
			else if (Maze[i][j] == '2')
				cout << "★";
			else if (Maze[i][j] == '3')
				cout << "◎";
		}
		cout << endl;
	}
}

void MoveUp(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->y - 1 >= 0)
	{
		// 벽인지 체크한다
		if (Maze[pPlayerPos->y - 1][pPlayerPos->x] != '0')
		{
			pPlayerPos->y--;
		}
	}
}

void MoveDown(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->y + 1 < 20)
	{
		// 벽인지 체크한다
		if (Maze[pPlayerPos->y + 1][pPlayerPos->x] != '0')
		{
			pPlayerPos->y++;
		}
	}
}

void MoveLeft(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->x - 1 >= 0)
	{
		// 벽인지 체크한다
		if (Maze[pPlayerPos->y][pPlayerPos->x - 1] != '0')
		{
			pPlayerPos->x--;
		}
	}
}

void MoveRight(char Maze[21][21], PPOINT pPlayerPos)
{
	if (pPlayerPos->x + 1 < 20)
	{
		// 벽인지 체크한다
		if (Maze[pPlayerPos->y][pPlayerPos->x + 1] != '0')
		{
			pPlayerPos->x++;
		}
	}
}

void MovePlayer(char Maze[21][21], PPOINT pPlayerPos, char cInput)
{
	switch (cInput)
	{
	case 'w':
	case 'W':
		MoveUp(Maze, pPlayerPos);
		break;
	case 's':
	case 'S':
		MoveDown(Maze, pPlayerPos);
		break;
	case 'a':
	case 'A':
		MoveLeft(Maze, pPlayerPos);
		break;
	case 'd':
	case 'D':
		MoveRight(Maze, pPlayerPos);
		break;
	}
}

int main()
{
	// 20 X 20 미로를 만들어 준다.
	char strMaze[21][21] = {};

	POINT tPlayerPos;
	POINT tStartPos;
	POINT tEndPos;

	// 미로를 설정한다.
	SetMaze(strMaze, &tPlayerPos, &tStartPos, &tEndPos);

	while (true)
	{
		system("cls");
		// 미로를 출력한다.
		Output(strMaze, &tPlayerPos);

		if (tPlayerPos.x == tEndPos.x && tPlayerPos.y == tEndPos.y)
		{
			cout << "도착했습니다." << endl;
			break;
		}

		cout << "w : 위 / s : 아래 / a : 왼쪽 / d : 오른쪽 / q : 종료" << endl;
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;

		MovePlayer(strMaze, &tPlayerPos, cInput);
	}

	return 0;
}