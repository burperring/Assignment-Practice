#include<iostream>

using namespace std;

enum MAIN_MENU
{
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_SEARCH,
	MM_OUTPUT,
	MM_EXIT
};

#define NAME_SIZE 32

typedef struct _tagStudent
{
	char	strName[NAME_SIZE];
	int		iNumber;
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
}STUDENT, *PSTUDENT;

/*
��ũ�帮��Ʈ : �ڷᱸ���� �� �����̴�. �ڷᱸ���� �����͸� �����ϴ� ����� ���Ѵ�.
��ũ�帮��Ʈ�� ������ ����� ������Ѽ� ������ �� �ִ� ������ �����Ѵ�.
��ũ�帮��Ʈ�� �����͸� �����ϱ� ���� ����� ���� �����Ѵ�. �� ����� Ư¡�� ���� ��带 
���� ��带 �� �� �ְ� �ȴ�.(��������� �޸� �ּҸ� �����Ѵٴ� �ǹ��̴�.)
����Ʈ�� ���������� �Ǿ��ִ�. �׷��� ������ �迭ó�� Ư����ҿ� �ٷ������� �Ұ����ϴ�.
������ �տ������� ���ʴ�� Ÿ�� ���� �Ѵ�.
��带 ���� �߰��Ҷ��� ��带 �����ϰ� ������ ��忡 ������ ���ָ� �Ǳ� ������ ������ ������ ����.
*/

// ����Ʈ ��带 �����.
typedef struct _tagNode
{
	STUDENT		tStudent;
	_tagNode*	pNext;
}NODE, *PNODE;

// ����Ʈ ����ü�� ������ش�.
typedef struct _tagList
{
	PNODE	pBegin;
	PNODE	pEnd;
	int		iSize;
}LIST, *PLIST;

int InputInt()
{
	int iInput;
	cin >> iInput;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;
	}

	return iInput;
}

void InputString(char* pString, int iSize)
{
	cin.clear();
	cin.ignore(1024, '\n');
	cin.getline(pString, iSize - 1);
}

void InitList(PLIST pList)
{
	// �����ʹ� �������̸� �ʱ�ȭ�Ҷ� NULL(0) ���� �ʱ�ȭ�صΰ� ���� ���� ����.
	// �ֳ��ϸ� 0�� false 0�� �ƴ� ��� ���� true�̱� �����̴�.
	// �ʱ�ȭ���� ���� ��� �����Ⱚ�� ���ԵǴµ� �� �����Ⱚ ���� treu�̴�.
	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;
}

int OutputMenu()
{
	system("cls");
	cout << "1. �л��߰�" << endl;
	cout << "2. �л�����" << endl;
	cout << "3. �л�Ž��" << endl;
	cout << "4. �л����" << endl;
	cout << "5. ����" << endl;
	cout << "�޴��� �����ϼ��� : ";

	int iInput = InputInt();

	if (iInput <= MM_NONE || iInput > MM_EXIT)
		return MM_NONE;

	return iInput;
}

void Insert(PLIST pList)
{
	system("cls");
	cout << "==================== �л��߰� ====================" << endl;

	STUDENT tStudent = {};

	cout << "�̸� : ";
	InputString(tStudent.strName, NAME_SIZE);

	cout << "�й� : ";
	tStudent.iNumber = InputInt();

	cout << "���� : ";
	tStudent.iKor = InputInt();

	cout << "���� : ";
	tStudent.iEng = InputInt();

	cout << "���� : ";
	tStudent.iMath = InputInt();

	tStudent.iTotal = tStudent.iKor + tStudent.iEng + tStudent.iMath;
	tStudent.fAvg	= tStudent.iTotal / 3.f;

	// �߰��� ����Ʈ ��带 �����Ѵ�.
	PNODE pNode = new NODE;

	// ���� �߰��ϴ� ���� ���� �������� �߰��� ���̱� ������ ���� ��尡 �������� �ʴ´�.
	// �׷��� ���� ���� NULL�� �ʱ�ȭ�ϰ� ������ ������ �Է¹��� �л������� �ֵ����Ѵ�.
	pNode->pNext = NULL;
	pNode->tStudent = tStudent;

	if (pList->pBegin == NULL)
		pList->pBegin = pNode;

	else
		pList->pEnd->pNext = pNode;

	pList->pEnd = pNode;

	++pList->iSize;
}

void ClearList(PLIST pList)
{
	PNODE pNode = pList->pBegin;

	while (pNode != NULL)
	{
		PNODE pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}

	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;
}

// const �������̱� ������ ����Ű�� ����� ���� ������ �� ����.
void OutputStudent(const PSTUDENT pStudnet)
{
	cout << "�̸� : " << pStudnet->strName << "\t�й� : " << pStudnet->iNumber << endl;
	cout << "���� : " << pStudnet->iKor << endl;
	cout << "���� : " << pStudnet->iEng << endl;
	cout << "���� : " << pStudnet->iMath << endl;
	cout << "���� : " << pStudnet->iTotal << "\t��� : " << pStudnet->fAvg << endl;
	cout << "==================================================" << endl;
}

void Output(PLIST pList)
{
	system("cls");
	cout << "==================== �л���� ====================" << endl;

	PNODE pNode = pList->pBegin;

	while (pNode != NULL)
	{
		OutputStudent(&pNode->tStudent);
		pNode = pNode->pNext;
	}

	cout << "�л��� : " << pList->iSize << endl;

	system("pause");
}

void Search(PLIST pList)
{
	system("cls");
	cout << "==================== �л�Ž�� ====================" << endl;

	cout << "Ž���� �̸��� �Է��ϼ��� : ";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);

	PNODE	pNode = pList->pBegin;

	while (pNode != NULL)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			OutputStudent(&pNode->tStudent);
			system("pause");
			return;
		}

		pNode = pNode->pNext;
	}

	cout << "ã�� �л��� �����ϴ�." << endl;
	system("pause");
}

void Delete(PLIST pList)
{
	system("cls");
	cout << "==================== �л����� ====================" << endl;

	cout << "������ �̸��� �Է��ϼ��� : ";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);

	PNODE pNode = pList->pBegin;
	PNODE pPrev = NULL;

	while (pNode != NULL)
	{
		if (strcmp(pNode->tStudent.strName, strName) == 0)
		{
			// ���� ����� ���� ��带 ���´�.
			PNODE pNext = pNode->pNext;

			// ���� ���� ��尡 NULL�̶�� ���� ù��° ��带 ����ٴ� �ǹ��̴�.
			if (pPrev == NULL)
			{
				delete pNode;
				pList->pBegin = pNext;

				if (pNext == NULL)
					pList->pEnd = NULL;
			}

			// ���� ��尡 ���� ��� ���� ����� ������ ���� ����� �������� �������ش�.
			else
			{
				delete pNode;
				pPrev->pNext = pNext;

				if (pNext == NULL)
					pList->pEnd = pPrev;
			}

			cout << strName << "�л� ���� �ȷ�" << endl;

			pList->iSize--; 
			system("pause");
			return;
		}

		// �ش� �л��� �ƴ϶�� ���� ��尡 ���� ��尡 �ȴ�.
		pPrev = pNode;
		pNode = pNode->pNext;
	}

	cout << "������ �л��� ã�� �� �����ϴ�." << endl;
	system("pause");
}

int main()
{
	LIST	tList;

	// InitList�� ���ڷ� PLIST(_tagList*) Ÿ���� �����Ƿ� �ּҸ� �Ѱ��ش�.
	InitList(&tList);

	while (true)
	{
		int iMenu = OutputMenu();

		if (iMenu == MM_EXIT)
			break;

		switch (iMenu)
		{
		case MM_INSERT:
			Insert(&tList);
			break;
		case MM_DELETE:
			Delete(&tList);
			break;
		case MM_SEARCH:
			Search(&tList);
			break;
		case MM_OUTPUT:
			Output(&tList);
			break;
		}
	}

	ClearList(&tList);

	return 0;
}