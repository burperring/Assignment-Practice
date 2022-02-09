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

int main()
{
	int iNumber[25] = { 0 };
	int iAiNumber[25] = { 0 };

	srand((unsigned int)time(0));

	for (int i = 0; i < 25; i++)
	{
		iNumber[i] = i + 1;
		iAiNumber[i] = i + 1;
	}

	int iTemp, idx1, idx2;

	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;

		idx1 = rand() % 25;
		idx2 = rand() % 25;

		iTemp = iAiNumber[idx1];
		iAiNumber[idx1] = iAiNumber[idx2];
		iAiNumber[idx2] = iTemp;
	}

	int iBingo = 0, iAiBingo = 0;
	int iAiMode;

	while(true)
	{
		cout << "1. Easy" << endl;
		cout << "2. Hard" << endl;
		cout << "Ai 모드를 선택하세요 : ";
		cin >> iAiMode;

		if (iAiMode >= AM_EASY && iAiMode <= AM_HARD)
			break;
	}

	int iNoneSelect[25] = {};
	int iNoneSelectCount = 0;

	while (true)
	{
		system("cls");

		cout << "============= Player =============" << endl;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (iNumber[i * 5 + j] == INT_MAX)
					cout << "*\t";
				else
					cout << iNumber[i * 5 + j] << "\t";
			}
			cout << endl;
		}
		cout << "==================================" << endl;
		if (iAiBingo >= 5 || iBingo >=5)
		{
			cout << "=============== Ai ===============" << endl;
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (iAiNumber[i * 5 + j] == INT_MAX)
						cout << "*\t";
					else
						cout << iAiNumber[i * 5 + j] << "\t";
				}
				cout << endl;
			}
			cout << "==================================" << endl;
		}
		else
		{
			cout << "=============== Ai ===============" << endl;
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (iAiNumber[i * 5 + j] == INT_MAX)
						cout << "*\t";
					else
						cout << "*\t";
				}
				cout << endl;
			}
			cout << "==================================" << endl;
		}

		switch (iAiMode)
		{
		case AM_EASY:
			cout << "Ai mode : Easy" << endl;
			break;
		case AM_HARD:
			cout << "Ai mode : Hard" << endl;
			break;
		}

		cout << "Bingo Line : " << iBingo << endl;
		cout << "AiBingp Line : " << iAiBingo << endl;

		if (iBingo >= 5)
		{
			cout << "Player 승리" << endl;
			break;
		}
		else if (iAiBingo >= 5)
		{
			cout << "Ai 승리" << endl;
			break;
		}

		cout << "숫자를 입력하세요.(0 : 종료) : ";
		int input;
		cin >> input;

		if (input == 0)
			break;
		else if (input > 25 || input < 1)
			continue;

		bool bAcc = true;

		for (int i = 0; i < 25; i++)
		{
			if (input == iNumber[i])
			{
				bAcc = false;
				iNumber[i] = INT_MAX;
				break;
			}
		}

		if (bAcc)
			continue;

		for (int i = 0; i < 25; i++)
		{
			if (input == iAiNumber[i])
			{
				iAiNumber[i] = INT_MAX;
				break;
			}
		}

		iNoneSelectCount = 0;
		switch (iAiMode)
		{
		case AM_EASY:
			for (int i = 0; i < 25; i++)
			{
				if (iAiNumber[i] != INT_MAX)
				{
					iNoneSelect[iNoneSelectCount] = iAiNumber[i];
					iNoneSelectCount++;
				}
			}

			input = iNoneSelect[rand() % iNoneSelectCount];
			break;
		case AM_HARD:
			int iLine = 0, iStarCount = 0, iSaveCount = 0;

			for (int i = 0; i < 5; i++)
			{
				iStarCount = 0;

				for (int j = 0; j < 5; j++)
				{
					if (iAiNumber[i * 5 + j] == INT_MAX)
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
					if (iAiNumber[j * 5 + i] == INT_MAX)
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
				if (iAiNumber[i] == INT_MAX)
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
				if (iAiNumber[i] == INT_MAX)
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
					if (iAiNumber[iLine * 5 + i] != INT_MAX)
					{
						input = iAiNumber[iLine * 5 + i];
						break;
					}
				}
			}

			else if (iLine <= LN_V5)
			{
				for (int i = 0; i < 5; i++)
				{
					if (iAiNumber[i * 5 + (iLine - 5)] != INT_MAX)
					{
						input = iAiNumber[i * 5 + (iLine - 5)];
						break;
					}
				}
			}

			else if (iLine == LN_LT)
			{
				for (int i = 0; i < 25; i += 6)
				{
					if (iAiNumber[i] != INT_MAX)
					{
						input = iAiNumber[i];
						break;
					}
				}
			}

			else if (iLine == LN_RT)
			{
				for (int i = 4; i <= 20; i += 4)
				{
					if (iAiNumber[i] != INT_MAX)
					{
						input = iAiNumber[i];
						break;
					}
				}
			}

			break;
		}

		for (int i = 0; i < 25; i++)
		{
			if (iNumber[i] == input)
			{
				iNumber[i] = INT_MAX;
				break;
			}
		}

		for (int i = 0; i < 25; i++)
		{
			if (iAiNumber[i] == input)
			{
				iAiNumber[i] = INT_MAX;
				break;
			}
		}

		iBingo = 0, iAiBingo = 0;

		int iStar1 = 0, iStar2 = 0;
		int iAiStar1 = 0, iAiStar2 = 0;
		for (int i = 0; i < 5; i++)
		{
			iStar1 = iStar2 = 0;
			iAiStar1 = iAiStar2 = 0;
			for (int j = 0; j < 5; j++)
			{
				if (iNumber[i * 5 + j] == INT_MAX)
					iStar1++;
				if (iNumber[j * 5 + i] == INT_MAX)
					iStar2++;
				if (iAiNumber[i * 5 + j] == INT_MAX)
					iAiStar1++;
				if (iAiNumber[j * 5 + i] == INT_MAX)
					iAiStar2++;
			}

			if (iStar1 == 5)
				iBingo++;
			if (iStar2 == 5)
				iBingo++;
			if (iAiStar1 == 5)
				iAiBingo++;
			if (iAiStar2 == 5)
				iAiBingo++;
		}

		iStar1 = 0, iAiStar1 = 0;
		for (int i = 0; i < 25; i += 6)
		{
			if (iNumber[i] == INT_MAX)
				iStar1++;
			if (iAiNumber[i] == INT_MAX)
				iAiStar1++;
		}

		if (iStar1 == 5)
			iBingo++;
		if (iAiStar1 == 5)
			iAiBingo++;

		iStar1 = 0, iAiStar1 = 0;
		for (int i = 4; i <= 20; i += 4)
		{
			if (iNumber[i] == INT_MAX)
				iStar1++;
			if (iAiNumber[i] == INT_MAX)
				iAiStar1++;
		}

		if (iStar1 == 5)
			iBingo++;
		if (iAiStar1 == 5)
			iAiBingo++;

	}

	return 0;
}