#include<iostream>
#include<ctime>
#include<conio.h>
#include<time.h>

using namespace std;

/*
0  : ��
1 : ��
2 : ������
3 : ������
4 : ��ź
5 : ��ź ����Ʈ
6 : �Ŀ�������
7 : ���б� ������
8 : ���������
9 : ��Ȧ
A : ���ִ� ����Ʈ
*/

typedef struct _tagPoint
{
	int x;
	int y;
}POINT, *PPOINT;

// typedef : Ÿ���� �������ϴ� ����̴�.
// typedef _tagPoint	POINT;
// typedef _tagPoint* PPOINT;

typedef struct _tagPlayer
{
	_tagPoint	tPos;
	bool		bWallPush;
	bool		bPushOnOff;
	bool		bTransparency;
	int			iBombPower;
}PLAYER, * PPLAYER;

void SetMaze(char Maze[21][21], PPLAYER pPlayer, PPOINT pStartPos, PPOINT pEndPos)
{
	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	pPlayer->tPos = *pStartPos;

	strcpy_s(Maze[0], "21100000000000000000");
	strcpy_s(Maze[1], "00111111111100000000");
	strcpy_s(Maze[2], "00100010000111111110");
	strcpy_s(Maze[3], "01100010000000000010");
	strcpy_s(Maze[4], "01000011100011111110");
	strcpy_s(Maze[5], "01000000011110000000");
	strcpy_s(Maze[6], "01100000010000000000");
	strcpy_s(Maze[7], "00100000011111100110");
	strcpy_s(Maze[8], "00011111000000100100");
	strcpy_s(Maze[9], "00010001111111100100");
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

void Output(char Maze[21][21], PPLAYER pPlayer)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (Maze[i][j] == '4')
				cout << "��";
			else if (pPlayer->tPos.x == j && pPlayer->tPos.y == i)
				cout << "��";
			else if (Maze[i][j] == '0')
				cout << "��";
			else if (Maze[i][j] == '1')
				cout << "  ";
			else if (Maze[i][j] == '2')
				cout << "��";
			else if (Maze[i][j] == '3')
				cout << "��";
			else if (Maze[i][j] == '5')
				cout << "��";
			else if (Maze[i][j] == '6')
				cout << "��";
			else if (Maze[i][j] == '7')
				cout << "��";
			else if (Maze[i][j] == '8')
				cout << "��";
			else if (Maze[i][j] == 'A')
				cout << "��";
		}
		cout << endl;
	}

	cout << "��ź�Ŀ� : " << pPlayer->iBombPower << endl;

	cout << "����� : ";
	if (pPlayer->bTransparency)
		cout << "ON\t";
	else
		cout << "OFF\t";

	cout << "���б� : ";
	if (pPlayer->bWallPush)
	{
		cout << "���� / ";

		if (pPlayer->bPushOnOff)
			cout << "ON" << endl;
		else
			cout << "OFF" << endl;
	}
	else
		cout << "�Ұ��� / OFF" << endl;
}

bool AddItem(char cItemType, PPLAYER pPlayer) 
{
	if (cItemType == '6')
	{	
		if (pPlayer->iBombPower < 5)
			pPlayer->iBombPower++;

		return true;
	}

	else if (cItemType == '7')
	{
		pPlayer->bWallPush = true;
		pPlayer->bPushOnOff = true;

		return true;
	}

	else if (cItemType == '8')
	{
		pPlayer->bTransparency = true;
		return true;
	}

	return false;
}

void MoveUp(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y - 1 >= 0)
	{
		// ������ üũ�Ѵ�
		if (Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '0' &&
			Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] != '4')
		{
			pPlayer->tPos.y--;
		}

		// �� �бⰡ �����ϰ� �ٷ���ĭ�� ���� ���
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] == '0')
		{
			// �� �бⰡ ON ������ ���
			if (pPlayer->bPushOnOff)
			{
				// ���� ��ĭ�� 0���� ũ�ų� ������� �ε����� �ִٴ� �ǹ�
				if (pPlayer->tPos.y - 2 >= 0)
				{
					// ���� ��ĭ�� ���̿��� �бⰡ �����ϴ�. �׷��Ƿ� ������ üũ�Ѵ�.
					if (Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] == '0')
					{
						if (pPlayer->bTransparency)
							pPlayer->tPos.y--;
					}

					// ���� ��ĭ�� ���� ��� ���� �о��.
					else if (Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] == '1')
					{
						// ���� ��ĭ�� ������ �ϰ� 
						Maze[pPlayer->tPos.y - 2][pPlayer->tPos.x] = '0';
						// ��ĭ�� ���̾��µ� ��� ����� �ش�.
						Maze[pPlayer->tPos.y - 1][pPlayer->tPos.x] = '1';
						// �÷��̾ �̵���Ų��.
						pPlayer->tPos.y--;
					}
				}

				else if (pPlayer->bTransparency)
					pPlayer->tPos.y--;
			}

			// �� �б� OFF ������ ���
			else if (pPlayer->bTransparency)
				pPlayer->tPos.y--;
		}

		else if (pPlayer->bTransparency)
			pPlayer->tPos.y--;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MoveDown(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.y + 1 < 20)
	{
		// ������ üũ�Ѵ�
		if (Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '0' &&
			Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] != '4')
		{
			pPlayer->tPos.y++;
		}

		// �� �бⰡ �����ϰ� �ٷξƷ�ĭ�� ���� ���
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] == '0')
		{
			// �� �бⰡ ON ������ ���
			if (pPlayer->bPushOnOff)
			{
				// �Ʒ��� �Ʒ�ĭ�� 0���� ũ�ų� ������� �ε����� �ִٴ� �ǹ�
				if (pPlayer->tPos.y + 2 < 20)
				{
					// �Ʒ��� �Ʒ�ĭ�� ���̿��� �бⰡ �����ϴ�. �׷��Ƿ� ������ üũ�Ѵ�.
					if (Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] == '0')
					{
						if (pPlayer->bTransparency)
							pPlayer->tPos.y++;
					}

					// �Ʒ��� �Ʒ�ĭ�� ���� ��� ���� �о��.
					else if (Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] == '1')
					{
						// �Ʒ��� �Ʒ�ĭ�� ������ �ϰ� 
						Maze[pPlayer->tPos.y + 2][pPlayer->tPos.x] = '0';
						// �Ʒ�ĭ�� ���̾��µ� ��� ����� �ش�.
						Maze[pPlayer->tPos.y + 1][pPlayer->tPos.x] = '1';
						// �÷��̾ �̵���Ų��.
						pPlayer->tPos.y++;
					}
				}

				else if (pPlayer->bTransparency)
					pPlayer->tPos.y++;
			}

			// �� �б� OFF ������ ���
			else if (pPlayer->bTransparency)
				pPlayer->tPos.y++;
		}

		else if (pPlayer->bTransparency)
			pPlayer->tPos.y++;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MoveLeft(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x - 1 >= 0)
	{
		// ������ üũ�Ѵ�
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '0' &&
			Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] != '4')
		{
			pPlayer->tPos.x--;
		}

		// �� �бⰡ �����ϰ� �ٷ���ĭ�� ���� ���
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] == '0')
		{
			// �� �бⰡ ON ������ ���
			if (pPlayer->bPushOnOff)
			{
				// ���� ��ĭ�� 0���� ũ�ų� ������� �ε����� �ִٴ� �ǹ�
				if (pPlayer->tPos.x - 2 >= 0)
				{
					// ���� ��ĭ�� ���̿��� �бⰡ �����ϴ�. �׷��Ƿ� ������ üũ�Ѵ�.
					if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] == '0')
					{
						if (pPlayer->bTransparency)
							pPlayer->tPos.x--;
					}

					// ���� ��ĭ�� ���� ��� ���� �о��.
					else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] == '1')
					{
						// ���� ��ĭ�� ������ �ϰ� 
						Maze[pPlayer->tPos.y][pPlayer->tPos.x - 2] = '0';
						// ��ĭ�� ���̾��µ� ��� ����� �ش�.
						Maze[pPlayer->tPos.y][pPlayer->tPos.x - 1] = '1';
						// �÷��̾ �̵���Ų��.
						pPlayer->tPos.x--;
					}
				}

				else if (pPlayer->bTransparency)
					pPlayer->tPos.x--;
			}

			// �� �б� OFF ������ ���
			else if (pPlayer->bTransparency)
				pPlayer->tPos.x--;
		}

		else if (pPlayer->bTransparency)
			pPlayer->tPos.x--;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MoveRight(char Maze[21][21], PPLAYER pPlayer)
{
	if (pPlayer->tPos.x + 1 < 20)
	{
		// ������ üũ�Ѵ�
		if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '0' &&
			Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] != '4')
		{
			pPlayer->tPos.x++;
		}

		// �� �бⰡ �����ϰ� �ٷ���ĭ�� ���� ���
		else if (pPlayer->bWallPush && Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] == '0')
		{
			// �� �бⰡ ON ������ ���
			if (pPlayer->bPushOnOff)
			{
				// ���� ��ĭ�� 0���� ũ�ų� ������� �ε����� �ִٴ� �ǹ�
				if (pPlayer->tPos.x + 2 < 20)
				{
					// ���� ��ĭ�� ���̿��� �бⰡ �����ϴ�. �׷��Ƿ� ������ üũ�Ѵ�.
					if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 2] == '0')
					{
						if (pPlayer->bTransparency)
							pPlayer->tPos.x++;
					}

					// ���� ��ĭ�� ���� ��� ���� �о��.
					else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x + 2] == '1')
					{
						// ���� ��ĭ�� ������ �ϰ� 
						Maze[pPlayer->tPos.y][pPlayer->tPos.x + 2] = '0';
						// ��ĭ�� ���̾��µ� ��� ����� �ش�.
						Maze[pPlayer->tPos.y][pPlayer->tPos.x + 1] = '1';
						// �÷��̾ �̵���Ų��.
						pPlayer->tPos.x++;
					}
				}

				else if (pPlayer->bTransparency)
					pPlayer->tPos.x++;
			}

			// �� �б� OFF ������ ���
			else if (pPlayer->bTransparency)
				pPlayer->tPos.x++;
		}

		else if (pPlayer->bTransparency)
			pPlayer->tPos.x++;

		if (AddItem(Maze[pPlayer->tPos.y][pPlayer->tPos.x], pPlayer))
			Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '1';
	}
}

void MovePlayer(char Maze[21][21], PPLAYER pPlayer, char cInput)
{
	switch (cInput)
	{
	case 'w':
	case 'W':
		MoveUp(Maze, pPlayer);
		break;
	case 's':
	case 'S':
		MoveDown(Maze, pPlayer);
		break;
	case 'a':
	case 'A':
		MoveLeft(Maze, pPlayer);
		break;
	case 'd':
	case 'D':
		MoveRight(Maze, pPlayer);
		break;
	}
}

// ������ ������ const�� �����ϸ� ����Ű�� ����� ���� ������ �� ����.
void CreateBomb(char Maze[21][21], const PPLAYER pPlayer, PPOINT pBombArr, int* pBombCount)
{
	if (*pBombCount == 5)
		return;

	else if (Maze[pPlayer->tPos.y][pPlayer->tPos.x] == '0')
		return;

	for (int i = 0; i < *pBombCount; i++)
	{
		if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y)
			return;
	}

	pBombArr[*pBombCount] = pPlayer->tPos;
	(*pBombCount)++;

	Maze[pPlayer->tPos.y][pPlayer->tPos.x] = '4';
}

void FireEffet(char Maze[21][21], PPLAYER pPlayer, PPOINT pBombArr, int* pBombCount)
{
	for (int i = 0; i < *pBombCount; i++)
	{
		Maze[pBombArr[i].y][pBombArr[i].x] = '5';

		for (int j = 0; j <= pPlayer->iBombPower; j++)
		{
			if (pBombArr[i].y - j >= 0)
			{
				if (Maze[pBombArr[i].y - j][pBombArr[i].x] == '0')
					Maze[pBombArr[i].y - j][pBombArr[i].x] = 'A';
				else
					Maze[pBombArr[i].y - j][pBombArr[i].x] = '5';
			}

			if (pBombArr[i].y + j < 20)
			{
				if (Maze[pBombArr[i].y + j][pBombArr[i].x] == '0')
					Maze[pBombArr[i].y + j][pBombArr[i].x] = 'A';
				else
					Maze[pBombArr[i].y + j][pBombArr[i].x] = '5';
			}

			if (pBombArr[i].x - j >= 0)
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x - j] == '0')
					Maze[pBombArr[i].y][pBombArr[i].x - j] = 'A';
				else
					Maze[pBombArr[i].y][pBombArr[i].x - j] = '5';
			}

			if (pBombArr[i].x + j < 20)
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x + j] == '0')
					Maze[pBombArr[i].y][pBombArr[i].x + j] = 'A';
				else
					Maze[pBombArr[i].y][pBombArr[i].x + j] = '5';
			}
		}
	}
}

void Fire(char Maze[21][21], PPLAYER pPlayer, PPOINT pBombArr, int* pBombCount)
{
	for (int i = 0; i < *pBombCount; i++)
	{
		// �÷��̾ ��ź�� �¾����� ���������� ������.
		if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y)
		{
			pPlayer->tPos.x = 0;
			pPlayer->tPos.y = 0;
		}

		Maze[pBombArr[i].y][pBombArr[i].x] = '1';

		for (int j = 0; j <= pPlayer->iBombPower; j++)
		{
			if (pBombArr[i].y - j >= 0)
			{
				if (Maze[pBombArr[i].y - j][pBombArr[i].x] == 'A')
				{
					// ������ ��� Ȯ���� ���Ѵ�.
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if(iPercent < 70)
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '6';
						else if(iPercent < 80)
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '7';
						else
							Maze[pBombArr[i].y - j][pBombArr[i].x] = '8';
					}

					else
						Maze[pBombArr[i].y - j][pBombArr[i].x] = '1';
				}
				else
					Maze[pBombArr[i].y - j][pBombArr[i].x] = '1';

				// �÷��̾ ��ź�� �¾����� ���������� ������.
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y - j)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].y + j < 20)
			{
				if (Maze[pBombArr[i].y + j][pBombArr[i].x] == 'A')
				{
					// ������ ��� Ȯ���� ���Ѵ�.
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '6';
						else if (iPercent < 80)
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '7';
						else
							Maze[pBombArr[i].y + j][pBombArr[i].x] = '8';
					}

					else
						Maze[pBombArr[i].y + j][pBombArr[i].x] = '1';
				}
				else
					Maze[pBombArr[i].y + j][pBombArr[i].x] = '1';

				// �÷��̾ ��ź�� �¾����� ���������� ������.
				if (pPlayer->tPos.x == pBombArr[i].x && pPlayer->tPos.y == pBombArr[i].y + j)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].x - j >= 0)
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x - j] == 'A')
				{
					// ������ ��� Ȯ���� ���Ѵ�.
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '6';
						else if (iPercent < 80)
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '7';
						else
							Maze[pBombArr[i].y][pBombArr[i].x - j] = '8';
					}

					else
						Maze[pBombArr[i].y][pBombArr[i].x - j] = '1';
				}
				else
					Maze[pBombArr[i].y][pBombArr[i].x - j] = '1';

				// �÷��̾ ��ź�� �¾����� ���������� ������.
				if (pPlayer->tPos.x == pBombArr[i].x - j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}

			if (pBombArr[i].x + 1 < 20)
			{
				if (Maze[pBombArr[i].y][pBombArr[i].x + j] == 'A')
				{
					// ������ ��� Ȯ���� ���Ѵ�.
					if (rand() % 100 < 20)
					{
						int iPercent = rand() % 100;
						if (iPercent < 70)
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '6';
						else if (iPercent < 80)
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '7';
						else
							Maze[pBombArr[i].y][pBombArr[i].x + j] = '8';
					}

					else
						Maze[pBombArr[i].y][pBombArr[i].x + j] = '1';
				}
				else
					Maze[pBombArr[i].y][pBombArr[i].x + j] = '1';

				// �÷��̾ ��ź�� �¾����� ���������� ������.
				if (pPlayer->tPos.x == pBombArr[i].x + j && pPlayer->tPos.y == pBombArr[i].y)
				{
					pPlayer->tPos.x = 0;
					pPlayer->tPos.y = 0;
				}
			}
		}
	}

	*pBombCount = 0;
}

int main()
{
	srand((unsigned int)time(0));

	// 20 X 20 �̷θ� ����� �ش�.
	char strMaze[21][21] = {};

	PLAYER	tPlayer = {};
	POINT	tStartPos;
	POINT	tEndPos;

	tPlayer.iBombPower = 1;

	int iBombCount = 0;

	POINT tBombPos[5];

	// �̷θ� �����Ѵ�.
	SetMaze(strMaze, &tPlayer, &tStartPos, &tEndPos);

	while (true)
	{
		system("cls");
		// �̷θ� ����Ѵ�.
		Output(strMaze, &tPlayer);

		if (tPlayer.tPos.x == tEndPos.x && tPlayer.tPos.y == tEndPos.y)
		{
			cout << "�����߽��ϴ�." << endl;
			break;
		}

		cout << "w : �� / s : �Ʒ� / a : ���� / d : ������ / q : ����" << endl;
		cout << "m : ��ź��ġ / n : ��ź ��Ʈ���� / k : ���б� ON/OFF" << endl;
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q')
			break;

		else if (cInput == 'm' || cInput == 'M')
			CreateBomb(strMaze, &tPlayer, tBombPos, &iBombCount);

		else if (cInput == 'n' || cInput == 'N')
		{
			FireEffet(strMaze, &tPlayer, tBombPos, &iBombCount);
			clock_t delay = 0.3 * CLOCKS_PER_SEC;
			clock_t start = clock();
			while (clock() - start < delay)
			{
				system("cls");
				// �̷θ� ����Ѵ�.
				Output(strMaze, &tPlayer);
			}
			Fire(strMaze, &tPlayer, tBombPos, &iBombCount);
		}

		else if (cInput == 'k' || cInput == 'K')
		{
			if (tPlayer.bWallPush)
				tPlayer.bPushOnOff = !tPlayer.bPushOnOff;
		}

		else
			MovePlayer(strMaze, &tPlayer, cInput);
	}

	return 0;
}