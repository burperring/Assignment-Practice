#include <iostream>
using namespace std;
class foo {
	int i;
public:
	void Print() { cout << "Hello" << endl; }
};//class A

void main() {
	foo inst;
	inst.Print();
}//main