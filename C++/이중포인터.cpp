#include<iostream>

using namespace std;

int main()
{
	int iNumber1 = 1111;
	int iNumber = 2222;
	int* pNum = &iNumber;

	// ���������� : *�� 2�� ���δ�. �Ϲ� ������ ������ �Ϲ� ������ �޸��ּҸ� �����ϴ� �������
	// ���������ʹ� �������� �������̴�. ��, ���������ʹ� �����ͺ����� �޸� �ּҸ� �����ϴ� �������̴�.
	int** ppNum = &pNum;

	*pNum = 3333;

	cout << "iNumber : " << iNumber << endl;
	cout << "iNumber Addr : " << &iNumber << endl;
	cout << "*pNum : " << *pNum << endl;
	cout << "pNum Value : " << pNum << endl;
	cout << "pNum Addr : " << &pNum << endl;
	cout << "*ppNum : " << *ppNum << endl;
	cout << "**ppNum : " << **ppNum << endl;
	cout << "ppNum Value : " << ppNum << endl;
	cout << "ppNum Addr : " << &ppNum << endl << endl;

	*ppNum = &iNumber1;
	cout << "iNumber1 : " << iNumber1 << endl;
	cout << "iNumber1 Addr : " << &iNumber1 << endl;
	cout << "*pNum : " << *pNum << endl;
	cout << "pNum Value : " << pNum << endl;
	cout << "pNum Addr : " << &pNum << endl;
	cout << "*ppNum : " << *ppNum << endl;
	cout << "**ppNum : " << **ppNum << endl;
	cout << "ppNum Value : " << ppNum << endl;
	cout << "ppNum Addr : " << &ppNum << endl;

	return 0;
}