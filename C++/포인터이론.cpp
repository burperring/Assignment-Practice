#include<iostream>

using namespace std;

int main()
{
	/*
	포인터 : 가리키다. 일반 변수는 일반적인 값을 저장하게 되지만 포인터 변수는 메모리 주소를
			 저장하게 된다. 모든 변수 타입은 포인터 타입을 선언할수 있다.
			 int변수의 주소는 int 포인터 변수에 저장을 해야한다.
			 포인터는 메모리 주소를 담아놓는 변수이기 때문에 x86으로 개발할때는 무조건 4byte가 나온다.
			 x64로 개발할때는 무조건 8byte가 나온다.

			 포인터는 자기 스스로 아무런일도 할 수 없다. 반드시 다른 변수의	메모리주소를 가지고 있어야
			 일을 할 수 있는데 가지고 있는 그 메모리 주소에 접근해서 값을 제어할 수 있다.

	형태 : 변수타입* 변수명 : 의 형태로 선언한다.
	*/

	int iNumber = 10;
	// 변수 선언시 *을 붙여주면 해당 타입의 포인터 변수가 선언된다.
	// 변수 앞에 &을 붙여주면 해당 변수의 메모리 주소가 된다.
	int* pNum = &iNumber;
	// pNum은 iNumber변수의 메모리 주소를 값으로 갖게 됐다. 그러므로 pNum을 이용해 iNumber값을
	// 제어할 수 있게 된 것이다.

	cout << sizeof(int*) << endl;
	cout << sizeof(char*) << endl;
	cout << sizeof(double*) << endl;
	
	// pNum을 이용해서 iNumber 값을 제어해보자.
	// 역참조를 이용해서 값을 얻어오거나 변경할 수 있다.
	// 역참조는 포인터 변수 앞에 *을 붙이게 되면 역참조가 된다.
	cout << *pNum << endl;
	*pNum = 1234;

	cout << "iNumber Value : " << iNumber << endl;
	cout << "iNumber Adress : " << &iNumber << endl;
	cout << "pNum Value : " << pNum << endl;
	cout << "pNum Adress : " << &pNum << endl;

	/*
	포인터와 배열의 관계 : 배열명은 포인터다. 배열명 자체가 해당 배열의 메모리에서의 시작점 주소를 의미
	*/
	int iArr[10] = { 1,2,3,4,5,6,7,8,9,10 };

	cout << "iArr Adress : " << iArr << endl;
	cout << "iArr Adress : " << &iArr[0] << endl;

	int* pArr = iArr;

	cout << pArr[2] << endl;

	/*
	포인터 연산 : +, - 연산을 제공한다. ++, -- 도 가능한데 1을 증가하게 되면 단순히 메모리주소값이 
				  1 증가하는 것이 아니다. int 포인터의 경우 int 타입의 메모리 주소를 가지게 되는데
				  메모리 주소에 1을 더해주면 1증가가 아닌 가리키는 해당 포인터타입의 변수타입의
				  크기만큼 증가하게된다. int 포인터이므로 int의 크기인 4만큼 값이 증가한다.
	*/

	cout << pArr << endl;
	cout << pArr + 2 << endl;
	cout << *pArr << endl;
	cout << *(pArr + 2) << endl;
	cout << *pArr + 100 << endl;

	return 0;
}