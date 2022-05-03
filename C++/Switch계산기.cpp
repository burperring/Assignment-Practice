#include<iostream>

using namespace std;

enum CHOICE
{
	CH_NONE,
	CH_PLUS,
	CH_MINUS,
	CH_MULTI,
	CH_DIVISION,
	CH_SHIFT_L,
	CH_SHIFT_R,
	CH_LE,
	CH_BE,
	CH_END,
};

int main()
{
	int iChoice = CH_NONE;
	int a, b, c;

	while (iChoice == CH_NONE)
	{
		cout << "1.+ 2.- 3.* 4./ 5.<< 6.>> 7.>= 8.<=" << endl;
		cout << "원하는 계산을 선택해주세요 : ";
		cin >> iChoice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (iChoice <= CH_NONE || iChoice >= CH_END)
			iChoice = CH_NONE;
	}

	cout << "1번째 입력값 : ";
	cin >> a;
	cout << "2번째 입력값 : ";
	cin >> b;

	switch (iChoice)
	{
	case CH_PLUS:
		c = a + b;
		cout << c;
		break;
	case CH_MINUS:
		c = a - b;
		cout << c;
		break;
	case CH_MULTI:
		c = a * b;
		cout << c;
		break;
	case CH_DIVISION:
		c = a / b;
		cout << c;
		break;
	case CH_SHIFT_L:
		c = a << b;
		cout << c;
		break;
	case CH_SHIFT_R:
		c = a >> b;
		cout << c;
		break;
	case CH_LE:
		if (a >= b)
			cout << "참";
		else
			cout << "거짓";
		break;
	case CH_BE:
		if (a <= b)
			cout << "참";
		else
			cout << "거짓";
		break;
	}

	return 0;
}
