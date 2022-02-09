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

		cout << "1. å���" << endl;
		cout << "2. å�뿩" << endl;
		cout << "3. å�ݳ�" << endl;
		cout << "4. å���" << endl;
		cout << "5. ����" << endl;
		cout << "�޴��� �����ϼ��� : ";
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

			cout << "=============== å��� ===============" << endl;

			if (iBookCount == BOOKMAX_SIZE)
			{
				cout << "���� ����Ҽ� �ִ� å���� �ִ�ġ�Դϴ�." << endl;
				system("pause");
				break;
			}

			cin.ignore(1024, '\n');
			cout << "å�̸� : ";
			cin.getline(tBookArr[iBookCount].strBookName, BOOKNAME_SIZE);

			cout << "�뿩�ݾ� : ";
			cin >> tBookArr[iBookCount].BookMoney;

			tBookArr[iBookCount].BookNumber = iBookNumber;

			tBookArr[iBookCount].BookBorrow = true;

			iBookCount++;
			iBookNumber++;
			break;
		case MENU_BORROW:
			system("cls");

			cout << "=============== å�뿩 ===============" << endl;

			cin.ignore(1024, '\n');
			cout << "�뿩�� å �̸��� �Է��ϼ��� : ";
			cin.getline(strBookName, BOOKNAME_SIZE);

			for (int i = 0; i < iBookCount; i++)
			{
				if (strcmp(tBookArr[i].strBookName, strBookName) == 0)
				{
					if (tBookArr[i].BookBorrow)
					{
						cout << "���� "<< tBookArr[i].strBookName 
							<<"(��)�� �����Ǽ� �ֽ��ϴ�." << endl;
						cout << "�뿩�ݾ��� " << tBookArr[i].BookMoney << "�Դϴ�." << endl;
						tBookArr[i].BookBorrow = false;
						break;
					}
					else
					{
						cout << "���� " << tBookArr[i].strBookName
							<< "(��)�� �����Ǽ� �����ϴ�." << endl;
					}
				}
			}

			break;
		case MENU_RETURN:
			system("cls");

			cout << "=============== å�ݳ� ===============" << endl;

			cin.ignore(1024, '\n');
			cout << "�ݳ��Ͻ� å �̸��� �Է��ϼ��� : ";
			cin.getline(strBookName, BOOKNAME_SIZE);

			for (int i = 0; i < iBookCount; i++)
			{
				if (strcmp(tBookArr[i].strBookName, strBookName) == 0)
				{
					if (tBookArr[i].BookBorrow)
					{
						cout << "�߸��� �Է��Դϴ�." << endl;
						break;
					}
					else
					{
						cout << "�̿����ּż� �����մϴ�." << endl;
						tBookArr[i].BookBorrow = true;
						break;
					}
				}
			}

			break;
		case MENU_OUTPUT:
			system("cls");

			cout << "=============== å��� ===============" << endl;

			for (int i = 0; i < iBookCount; i++)
			{
				cout << "å�̸� : " << tBookArr[i].strBookName << endl;
				cout << "å�뿩�� : " << tBookArr[i].BookMoney << endl;
				cout << "å��ȣ : " << tBookArr[i].BookNumber << endl;
				if (tBookArr[i].BookBorrow)
					cout << "å�뿩���� : O" << endl;
				else
					cout << "å�뿩���� : X" << endl;
				cout << "======================================" << endl;
			}
			break;
		default:
			cout << "�޴��� �߸� �����ϼ̽��ϴ�." << endl;
			break;
		}

		system("pause");
	}

	return 0;
}