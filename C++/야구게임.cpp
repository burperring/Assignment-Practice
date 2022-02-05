#include<iostream>
#include<time.h>

using namespace std;

int main()
{
	int iNumber[9] = {};
	srand((unsigned int)time(0));

	for (int i = 0; i < 9; i++)
	{
		iNumber[i] = i + 1;
	}

	int iTemp, idx1, idx2;
	for (int i = 0; i < 100; i++)
	{
		idx1 = rand() % 9;
		idx2 = rand() % 9;

		iTemp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = iTemp;
	}

	cout << "* * * 의 숫자를 맞추시오." << endl;

	int iStrike = 0, iBall = 0;
	int input[3] = { 0 };
	int iGameCount = 1;

	while (true)
	{
		cout << iGameCount << "회 게임" << endl;
		cout << "1 ~ 9 까지중 3개의 숫자를 고르시오(0 : 종료) : ";
		cin >> input[0] >> input[1] >> input[2];

		if (input[0] == 0 || input[1] == 0 || input[2] == 0)
			break;
		else if (input[0] < 0 || input[0] > 9 || input[1] < 0 || input[1] > 9 ||
			input[2] < 0 || input[2] > 9)
		{
			cout << "잘못된 입력입니다. 게임을";
			system("pause");
			continue;
		}
		else if (input[0] == input[1] || input[1] == input[2] || input[2] == input[0])
		{
			cout << "중복된 숫자를 입력했습니다." << endl;
			continue;
		}

		iStrike = 0, iBall = 0;

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (iNumber[i] == input[j])
				{
					if (i == j)
						iStrike++;
					else
						iBall++;

					break;
				}
			}
		}

		if (iStrike == 3)
		{
			cout << "숫자를 모두 맞추셨습니다." << endl;
			break;
		}
		else if (iStrike == 0 && iBall == 0)
		{
			cout << "OUT" << endl;
		}
		else
			cout << "Strike : " << iStrike << " Ball : " << iBall << endl;

		iGameCount++;
	}

	return 0;
}