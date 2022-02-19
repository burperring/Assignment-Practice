#include<iostream>
#include<time.h>

using namespace std;

enum AI_MODE
{
	AM_EASY = 1,
	AM_HARD
};

enum LINE_NUMBER
{
	LN_H1,
	LN_H2,
	LN_H3,
	LN_H4,
	LN_H5,
	LN_V1,
	LN_V2,
	LN_V3,
	LN_V4,
	LN_V5,
	LN_LT,
	LN_RT
};

// �Լ��� ����� ���� �κ����� ���� �� �ִ�.
void SetNumber(int* pArray);
void Shuffle(int* pArray);
AI_MODE SelectAiMode();
void OutputNumber(int* pArray);
void OutputAiNumber(int* pArray);
bool ChangeNumber(int* pArray, int iInput);
int SelectAiNumber(int* pArray, AI_MODE mode);
int BingoCounting(int* pArray);
int BingoCountingH(int* pArray);
int BingoCountingV(int* pArray);
int BingoCountingLT(int* pArray);
int BIngoCountingRT(int* pArray);

int main()
{
	srand((unsigned int)time(0));

	int iNumber[25] = { 0 };
	int iAiNumber[25] = { 0 };

	SetNumber(iNumber);
	SetNumber(iAiNumber);

	// ���ڸ� �����ش�.
	Shuffle(iNumber);
	Shuffle(iAiNumber);

	int iBingo = 0, iAiBingo = 0;

	// Ai ��带 �����Ѵ�.
	AI_MODE eAiMode = SelectAiMode();

	while (true)
	{
		system("cls");

		cout << "============= Player =============" << endl;
		OutputNumber(iNumber);
		cout << "==================================" << endl;
		if (iAiBingo >= 5 || iBingo >= 5)
		{
			cout << "=============== Ai ===============" << endl;
			OutputNumber(iAiNumber);
			cout << "==================================" << endl;
		}
		else
		{
			cout << "=============== Ai ===============" << endl;
			OutputAiNumber(iAiNumber);
			cout << "==================================" << endl;
		}

		cout << "Bingo Line : " << iBingo << endl;
		cout << "AiBingp Line : " << iAiBingo << endl;

		switch (eAiMode)
		{
		case AM_EASY:
			cout << "Ai mode : Easy" << endl;
			break;
		case AM_HARD:
			cout << "Ai mode : Hard" << endl;
			break;
		}

		if (iBingo >= 5)
		{
			cout << "Player �¸�" << endl;
			break;
		}
		else if (iAiBingo >= 5)
		{
			cout << "Ai �¸�" << endl;
			break;
		}

		cout << "���ڸ� �Է��ϼ���.(0 : ����) : ";
		int input;
		cin >> input;

		if (input == 0)
			break;
		else if (input > 25 || input < 1)
			continue;

		bool bAcc = ChangeNumber(iNumber, input);

		if (bAcc)
			continue;

		ChangeNumber(iAiNumber, input);

		// Ai�� ���ڸ� �����Ѵ�. Ai��忡 ���缭 ���õǵ��� �Լ��� �����Ǿ��ִ�.
		input = SelectAiNumber(iAiNumber, eAiMode);

		// Ai�� ���ڸ� ���������Ƿ� �÷��̾�� Ai���ڸ� �ٲ��ش�.
		ChangeNumber(iNumber, input);
		ChangeNumber(iAiNumber, input);

		iBingo = BingoCounting(iNumber);
		iAiBingo = BingoCounting(iAiNumber);
	}

	return 0;
}

// �̷��� ����� ���Ǹ� ������ �ִ�. �Լ�����
void SetNumber(int* pArray)
{
	for (int i = 0; i < 25; i++)
	{
		pArray[i] = i + 1;
	}
}

void Shuffle(int* pArray)
{
	int iTemp, idx1, idx2;

	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = pArray[idx1];
		pArray[idx1] = pArray[idx2];
		pArray[idx2] = iTemp;
	}
}

AI_MODE SelectAiMode()
{
	int iAiMode;
	while (true)
	{
		cout << "1. Easy" << endl;
		cout << "2. Hard" << endl;
		cout << "Ai ��带 �����ϼ��� : ";
		cin >> iAiMode;

		if (iAiMode >= AM_EASY && iAiMode <= AM_HARD)
			break;
	}

	return (AI_MODE)iAiMode;
}

void OutputNumber(int* pArray)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (pArray[i * 5 + j] == INT_MAX)
				cout << "*\t";
			else
				cout << pArray[i * 5 + j] << "\t";
		}
		cout << endl << endl;
	}
}

void OutputAiNumber(int* pArray)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (pArray[i * 5 + j] == INT_MAX)
				cout << "*\t";
			else
				cout << "*\t";
		}
		cout << endl << endl;
	}
}

bool ChangeNumber(int* pArray, int iInput)
{
	for (int i = 0; i < 25; i++)
	{
		if (iInput == pArray[i])
		{
			pArray[i] = INT_MAX;
			return false;
		}
	}

	// ������� �Դٸ� return false�� ���� �ȵ� ���̹Ƿ� ���� ���ڰ� ���ٴ� ���̴�.
	// ��, �ߺ��� ���ڸ� �Է��߱� ������ true�� �����Ѵ�.
	return true;
}

int SelectAiNumber(int* pArray, AI_MODE mode)
{
	int iNoneSelect[25] = {};
	int iNoneSelectCount = 0;
	
	switch (mode)
	{
	case AM_EASY:
		for (int i = 0; i < 25; i++)
		{
			if (pArray[i] != INT_MAX)
			{
				iNoneSelect[iNoneSelectCount] = pArray[i];
				iNoneSelectCount++;
			}
		}

		return iNoneSelect[rand() % iNoneSelectCount];
	case AM_HARD:
		int iLine = 0, iStarCount = 0, iSaveCount = 0;

		for (int i = 0; i < 5; i++)
		{
			iStarCount = 0;

			for (int j = 0; j < 5; j++)
			{
				if (pArray[i * 5 + j] == INT_MAX)
					iStarCount++;
			}

			if (iStarCount < 5 && iSaveCount < iStarCount)
			{
				iLine = i;
				iSaveCount = iStarCount;
			}
		}

		for (int i = 0; i < 5; i++)
		{
			iStarCount = 0;

			for (int j = 0; j < 5; j++)
			{
				if (pArray[j * 5 + i] == INT_MAX)
					iStarCount++;
			}

			if (iStarCount < 5 && iSaveCount < iStarCount)
			{
				iLine = i + 5;
				iSaveCount = iStarCount;
			}
		}

		iStarCount = 0;
		for (int i = 0; i < 25; i += 6)
		{
			if (pArray[i] == INT_MAX)
				iStarCount++;
		}

		if (iStarCount < 5 && iSaveCount < iStarCount)
		{
			iLine = LN_LT;
			iSaveCount = iStarCount;
		}

		iStarCount = 0;
		for (int i = 4; i <= 20; i += 4)
		{
			if (pArray[i] == INT_MAX)
				iStarCount++;
		}

		if (iStarCount < 5 && iSaveCount < iStarCount)
		{
			iLine = LN_RT;
			iSaveCount = iStarCount;
		}

		if (iLine <= LN_H5)
		{
			for (int i = 0; i < 5; i++)
			{
				if (pArray[iLine * 5 + i] != INT_MAX)
				{
					return pArray[iLine * 5 + i];
				}
			}
		}

		else if (iLine <= LN_V5)
		{
			for (int i = 0; i < 5; i++)
			{
				if (pArray[i * 5 + (iLine - 5)] != INT_MAX)
				{
					return pArray[i * 5 + (iLine - 5)];
				}
			}
		}

		else if (iLine == LN_LT)
		{
			for (int i = 0; i < 25; i += 6)
			{
				if (pArray[i] != INT_MAX)
				{
					return pArray[i];
				}
			}
		}

		else if (iLine == LN_RT)
		{
			for (int i = 4; i <= 20; i += 4)
			{
				if (pArray[i] != INT_MAX)
				{
					return pArray[i];
				}
			}
		}

		break;
	}

	return -1;
}

int BingoCounting(int* pArray)
{
	int iBingo = 0;

	iBingo += BingoCountingH(pArray);
	iBingo += BingoCountingV(pArray);
	iBingo += BingoCountingLT(pArray);
	iBingo += BIngoCountingRT(pArray);

	return iBingo;
}

int BingoCountingH(int* pArray)
{
	int iStar1 = 0, iBingo = 0;

	for (int i = 0; i < 5; i++)
	{
		iStar1 = 0;
		for (int j = 0; j < 5; j++)
		{
			if (pArray[i * 5 + j] == INT_MAX)
				iStar1++;
		}

		if (iStar1 == 5)
			iBingo++;
	}

	return iBingo;
}

int BingoCountingV(int* pArray)
{
	int iStar1 = 0, iBingo = 0;

	for (int i = 0; i < 5; i++)
	{
		iStar1 = 0;
		for (int j = 0; j < 5; j++)
		{
			if (pArray[j * 5 + i] == INT_MAX)
				iStar1++;
		}

		if (iStar1 == 5)
			iBingo++;
	}

	return iBingo;
}

int BingoCountingLT(int* pArray)
{
	int iStar1 = 0, iBingo = 0;
	for (int i = 0; i < 25; i += 6)
	{
		if (pArray[i] == INT_MAX)
			iStar1++;
	}

	if (iStar1 == 5)
		iBingo++;

	return iBingo;
}

int BIngoCountingRT(int* pArray)
{
	int iStar1 = 0, iBingo = 0;
	for (int i = 4; i <= 20; i += 4)
	{
		if (pArray[i] == INT_MAX)
			iStar1++;
	}

	if (iStar1 == 5)
		iBingo++;

	return iBingo;
}
