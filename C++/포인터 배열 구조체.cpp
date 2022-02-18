#include<iostream>

using namespace std;

struct _tagStudent
{
	int		iKor;
	int		iEng;
	int		iMath;
	int		iTotal;
	float	fAvg;
};

int main()
{
	const char* pText = "테스트 문자열";

	cout << pText << endl;
	cout << (int*)pText << endl;

	pText = "abcd";

	cout << pText << endl;
	cout << (int*)pText << endl; 

	pText = "abcd";

	cout << pText << endl;
	cout << (int*)pText << endl;

	pText = "abcdefg";

	cout << pText << endl;
	cout << (int*)pText << endl;

	char str[8] = "abcdefg";

	cout << str << endl;
	cout << (int*)str << endl;
	cout << (int*)&str[0] << endl;

	_tagStudent		tStudent = {};

	tStudent.iKor = 100;

	_tagStudent* pStudent = &tStudent;

	// 연산자 우선순위 때문에 .을 먼저인식하게 된다. 메모리주소. 은 잘못된 문법이다.
	// 그러므로 *pStudent를 괄호로 감싸준후에 .을 이용해서 가리키는 대상의 멤버변수에 접근해야 한다.
	(*pStudent).iKor = 50;

	// 메모리주소-> 을 이용해서 가리키는 대상의 멤버에 접근할수 있다.
	pStudent->iKor = 80;

	cout << tStudent.iKor << endl;

	// void : 타입이 없다. void의 포인터타입을 활용할 수 있다.
	// void* 변수를 선언하게 되면 이 변수는 어떤 타입의 메모리 주소든 모두 저장가능하다.
	// 단, 역참조가 불가능하고 메모리 주소만 저장 가능하다.
	int iNumber = 100;
	void* pVoid = &iNumber;

	cout << "iNumber Adress : " << pVoid << endl;

	// *pVoid = 10; 할경우 에러가 남
	// 바꾸는 법 2가지
	int* pConvert = (int*)pVoid;
	*pConvert = 1010101010;

	cout << iNumber << endl;

	// 또는
	*((int*)pVoid) = 9999;

	cout << iNumber << endl;

	pVoid = &tStudent;

	cout << "tStudent Adress : " << pVoid << endl;

	return 0;
}