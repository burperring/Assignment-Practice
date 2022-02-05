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

	cout << "* * * �� ���ڸ� ���߽ÿ�." << endl;

	int iStrike = 0, iBall = 0;
	int input[3] = { 0 };
	int iGameCount = 1;

	while (true)
	{
		cout << iGameCount << "ȸ ����" << endl;
		cout << "1 ~ 9 ������ 3���� ���ڸ� ���ÿ�(0 : ����) : ";
		cin >> input[0] >> input[1] >> input[2];

		if (input[0] == 0 || input[1] == 0 || input[2] == 0)
			break;
		else if (input[0] < 0 || input[0] > 9 || input[1] < 0 || input[1] > 9 ||
			input[2] < 0 || input[2] > 9)
		{
			cout << "�߸��� �Է��Դϴ�. ������";
			system("pause");
			continue;
		}
		else if (input[0] == input[1] || input[1] == input[2] || input[2] == input[0])
		{
			cout << "�ߺ��� ���ڸ� �Է��߽��ϴ�." << endl;
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
			cout << "���ڸ� ��� ���߼̽��ϴ�." << endl;
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