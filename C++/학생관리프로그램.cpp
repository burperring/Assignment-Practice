#include<iostream>

using namespace std;

#define NAME_SIZE		32
#define ADDRESS_SIZE	128
#define PHONE_SIZE		14
#define STUDENT_MAX		10

struct _tagStudent
{
	char	strName[NAME_SIZE];
	char	strAdress[ADDRESS_SIZE];
	char	strPhoneNumber[PHONE_SIZE];
	int		iNumber;
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
};

enum MENU
{
	MENU_NONE,
	MENU_INSERT,
	MENU_DELETE,
	MENU_SEARCH,
	MENU_OUTPUT,
	MENU_EXIT
};

int main()
{
	_tagStudent tStudentArr[STUDENT_MAX] = {};
	// �迭�� �߰��� ������ ������ ������ �߰����ش�.
	int iStudnetCount = 0;
	int iStdNumber = 1;

	char strName[NAME_SIZE] = {};

	while (true)
	{
		system("cls");

		// �޴��� ����Ѵ�.
		cout << "1. �л����" << endl;
		cout << "2. �л�����" << endl;
		cout << "3. �л��˻�" << endl;
		cout << "4. �л����" << endl;
		cout << "5. ����" << endl;
		cout << "�޴��� �����ϼ��� : ";
		int iMenu;
		cin >> iMenu;

		// cin�� �����ʿ� int������ ���� ������ �Է��ؾ��Ѵ�. �����ʿ� ���� ����Ÿ�Կ� ���缭
		// ���� �Է��ؾ� �ϴµ� �Ǽ��� ������ �ƴ� ���ڸ� �Է��� ��� ������ �߻��Ѵ�.
		// �׷��� ������ ����ó���� ������ �߻��ߴ����� ���⿡�� üũ�Ͽ� ������ �߻��ϸ�
		// cin ������ �������۸� ����ְ� cin ���ο� �Է¹��۰� �ִµ� �Է¹��۴� �Է��� ���� 
		// �����س��� �װ��� ������ �־��ִ� ������ �Ѵ�. �� �Է¹��ۿ� \n �� ���������Ƿ� 
		// ���۸� ��ȸ�Ͽ� \n�� �����ش�.
		// ���� : �ӽ�������������̴�.
		// ���� ������ üũ�Ѵ�. cin.fail() �� ������ ������ �߻��ϸ� true�� ��ȯ�Ѵ�.
		if (cin.fail())
		{
			// �������۸� �����ش�.
			cin.clear();

			// �Է¹��ۿ� \n �� ���������Ƿ� �Է¹��۸� �˻��Ͽ� \n �� �����ش�.
			// ù��°�� �˻��ϰ��� �ϴ�	����ũ�⸦ �����Ѵ�. �˳��ϰ� 1024 ����Ʈ���� ����
			// �ι�°�� ã�����ϴ� ���ڸ� �־��ش�.
			// �׷��� �Է¹��� ó������ \n�� �ִ°����� ã�Ƽ� �� �κ��� ��� �����ش�.
			cin.ignore(1024, '\n');
			continue;
		}

		if (iMenu == MENU_EXIT)
			break;

		switch (iMenu)
		{
		case MENU_INSERT:
			system("cls");
			cout << "=============== �л��߰� ===============" << endl;

			// ��ϵ� �л��� ����Ҽ� �ִ� �ִ�ġ�� ��� ���̻� ����� �����ʰ� �����.
			if (iStudnetCount == STUDENT_MAX)
			{
				cout << "����Ҽ� �ִ� �л����� �ִ�ġ�Դϴ�." << endl;
				system("pause");
				break;
			}

			// �л������� �߰��Ѵ�. �л������� �̸�, �ּ�, ��ȭ��ȣ, ������ ������ �Է¹ް�,
			// �й�, ����, ����� ������ ���� ������ش�.
			// �̸��� �Է¹޴´�.
			cout << "�̸� : ";
			cin >> tStudentArr[iStudnetCount].strName;

			cin.ignore(1024, '\n');

			cout << "�ּ� : ";
			cin.getline(tStudentArr[iStudnetCount].strAdress, ADDRESS_SIZE);

			cout << "��ȭ��ȣ : ";
			cin.getline(tStudentArr[iStudnetCount].strPhoneNumber, PHONE_SIZE);

			cout << "���� : ";
			cin >> tStudentArr[iStudnetCount].iKor;

			cout << "���� : ";
			cin >> tStudentArr[iStudnetCount].iEng;

			cout << "���� : ";
			cin >> tStudentArr[iStudnetCount].iMath;

			tStudentArr[iStudnetCount].iTotal = 
				tStudentArr[iStudnetCount].iKor +
				tStudentArr[iStudnetCount].iEng + 
				tStudentArr[iStudnetCount].iMath;

			tStudentArr[iStudnetCount].fAvg = tStudentArr[iStudnetCount].iTotal / 3.f;

			tStudentArr[iStudnetCount].iNumber = iStdNumber;

			iStdNumber++;
			iStudnetCount++;

			cout << "�л��߰��Ϸ�" << endl;
			break;
		case MENU_DELETE:
			system("cls");

			cout << "=============== �л����� ===============" << endl;

			if (iStudnetCount == 0)
			{
				cout << "���� ��ϵ� �л����� �����ϴ�." << endl;
				break;
			}

			cin.ignore(1024, '\n');
			cout << "������ �л� �̸��� �Է��ϼ��� : ";
			cin.getline(strName, NAME_SIZE);

			for (int i = 0; i < iStudnetCount; i++)
			{
				if (strcmp(tStudentArr[i].strName, strName) == 0)
				{
					for (int j = i; j < iStudnetCount - 1; j++)
					{
						tStudentArr[j] = tStudentArr[j + 1];
					}
					iStudnetCount--;

					cout << "�л��� �����߽��ϴ�." << endl;
					break;
				}
			}

			break;
		case MENU_SEARCH:
			system("cls");

			cout << "=============== �л��˻� ===============" << endl;

			if (iStudnetCount == 0)
			{
				cout << "���� ��ϵ� �л����� �����ϴ�." << endl;
				break;
			}

			cin.ignore(1024, '\n');
			cout << "�˻��� �л� �̸��� �Է��ϼ��� : ";
			cin.getline(strName, NAME_SIZE);

			// ��ϵǾ��ִ� �л��� ��ŭ �ݺ��ϸ� �л��� ã�´�.
			for (int i = 0; i < iStudnetCount; i++)
			{
				// �л��� ã���� ���
				if (strcmp(tStudentArr[i].strName, strName) == 0)
				{
					cout << "�й� : " << tStudentArr[i].iNumber << endl;
					cout << "�̸� : " << tStudentArr[i].strName << endl;
					cout << "�ּ� : " << tStudentArr[i].strAdress << endl;
					cout << "��ȭ��ȣ : " << tStudentArr[i].strPhoneNumber << endl;
					cout << "���� : " << tStudentArr[i].iKor << endl;
					cout << "���� : " << tStudentArr[i].iEng << endl;
					cout << "���� : " << tStudentArr[i].iMath << endl;
					cout << "���� : " << tStudentArr[i].iTotal << endl;
					cout << "��� : " << tStudentArr[i].fAvg << endl;
					cout << "========================================" << endl;
					break;
				}
			}

			break;
		case MENU_OUTPUT:
			system("cls");

			cout << "=============== �л���� ===============" << endl;

			if (iStudnetCount == 0)
			{
				cout << "���� ��ϵ� �л����� �����ϴ�." << endl;
				break;
			}

			// ��ϵ� �л�����ŭ �ݺ��ϸ� �л������� ����Ѵ�.
			for (int i = 0; i < iStudnetCount; i++)
			{
				cout << "�й� : " << tStudentArr[i].iNumber << endl;
				cout << "�̸� : " << tStudentArr[i].strName << endl;
				cout << "�ּ� : " << tStudentArr[i].strAdress << endl;
				cout << "��ȭ��ȣ : " << tStudentArr[i].strPhoneNumber << endl;
				cout << "���� : " << tStudentArr[i].iKor << endl;
				cout << "���� : " << tStudentArr[i].iEng << endl;
				cout << "���� : " << tStudentArr[i].iMath << endl;
				cout << "���� : " << tStudentArr[i].iTotal << endl;
				cout << "��� : " << tStudentArr[i].fAvg << endl;
				cout << "========================================" << endl;
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