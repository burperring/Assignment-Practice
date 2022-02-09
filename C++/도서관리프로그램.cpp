#include<iostream>

using namespace std;

#define BOOKNAME_SIZE	128
#define BOOKMAX_SIZE	100

struct _tagBook
{
	char strBookName[BOOKNAME_SIZE];
	int BookMoney;
	int BookNumber;
	bool BookBorrow;
};

enum MENU
{
	MENU_NONE,
	MENU_INSERT,
	MENU_BORROW,
	MENU_RETURN,
	MENU_OUTPUT,
	MENU_EXIT
};

int main()
{
	_tagBook tBookArr[BOOKMAX_SIZE] = {};

	int iBookCount = 0;
	int iBookNumber = 1;

	char strBookName[BOOKNAME_SIZE] = {};

	while (true)
	{
		system("cls");

		cout << "1. 책등록" << endl;
		cout << "2. 책대여" << endl;
		cout << "3. 책반납" << endl;
		cout << "4. 책목록" << endl;
		cout << "5. 종료" << endl;
		cout << "메뉴를 선택하세요 : ";
		int iMenu;
		cin >> iMenu;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		if (iMenu == MENU_EXIT)
			break;

		switch (iMenu)
		{
		case MENU_INSERT:
			system("cls");

			cout << "=============== 책등록 ===============" << endl;

			if (iBookCount == BOOKMAX_SIZE)
			{
				cout << "현재 등록할수 있는 책수가 최대치입니다." << endl;
				system("pause");
				break;
			}

			cin.ignore(1024, '\n');
			cout << "책이름 : ";
			cin.getline(tBookArr[iBookCount].strBookName, BOOKNAME_SIZE);

			cout << "대여금액 : ";
			cin >> tBookArr[iBookCount].BookMoney;

			tBookArr[iBookCount].BookNumber = iBookNumber;

			tBookArr[iBookCount].BookBorrow = true;

			iBookCount++;
			iBookNumber++;
			break;
		case MENU_BORROW:
			system("cls");

			cout << "=============== 책대여 ===============" << endl;

			cin.ignore(1024, '\n');
			cout << "대여할 책 이름을 입력하세요 : ";
			cin.getline(strBookName, BOOKNAME_SIZE);

			for (int i = 0; i < iBookCount; i++)
			{
				if (strcmp(tBookArr[i].strBookName, strBookName) == 0)
				{
					if (tBookArr[i].BookBorrow)
					{
						cout << "현재 "<< tBookArr[i].strBookName 
							<<"(을)를 빌리실수 있습니다." << endl;
						cout << "대여금액은 " << tBookArr[i].BookMoney << "입니다." << endl;
						tBookArr[i].BookBorrow = false;
						break;
					}
					else
					{
						cout << "현재 " << tBookArr[i].strBookName
							<< "(을)를 빌리실수 없습니다." << endl;
					}
				}
			}

			break;
		case MENU_RETURN:
			system("cls");

			cout << "=============== 책반납 ===============" << endl;

			cin.ignore(1024, '\n');
			cout << "반납하실 책 이름을 입력하세요 : ";
			cin.getline(strBookName, BOOKNAME_SIZE);

			for (int i = 0; i < iBookCount; i++)
			{
				if (strcmp(tBookArr[i].strBookName, strBookName) == 0)
				{
					if (tBookArr[i].BookBorrow)
					{
						cout << "잘못된 입력입니다." << endl;
						break;
					}
					else
					{
						cout << "이용해주셔서 감사합니다." << endl;
						tBookArr[i].BookBorrow = true;
						break;
					}
				}
			}

			break;
		case MENU_OUTPUT:
			system("cls");

			cout << "=============== 책목록 ===============" << endl;

			for (int i = 0; i < iBookCount; i++)
			{
				cout << "책이름 : " << tBookArr[i].strBookName << endl;
				cout << "책대여금 : " << tBookArr[i].BookMoney << endl;
				cout << "책번호 : " << tBookArr[i].BookNumber << endl;
				if (tBookArr[i].BookBorrow)
					cout << "책대여여부 : O" << endl;
				else
					cout << "책대여여부 : X" << endl;
				cout << "======================================" << endl;
			}
			break;
		default:
			cout << "메뉴를 잘못 선택하셨습니다." << endl;
			break;
		}

		system("pause");
	}

	return 0;
}