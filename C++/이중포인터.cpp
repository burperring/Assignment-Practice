#include<iostream>

using namespace std;

int main()
{
	int iNumber1 = 1111;
	int iNumber = 2222;
	int* pNum = &iNumber;

	// 이중포인터 : *을 2개 붙인다. 일반 포인터 변수가 일반 변수의 메모리주소를 저장하는 변수라면
	// 이중포인터는 포인터의 포인터이다. 즉, 이중포인터는 포인터변수의 메모리 주소를 저장하는 포인터이다.
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