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
	const char* pText = "�׽�Ʈ ���ڿ�";

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

	// ������ �켱���� ������ .�� �����ν��ϰ� �ȴ�. �޸��ּ�. �� �߸��� �����̴�.
	// �׷��Ƿ� *pStudent�� ��ȣ�� �������Ŀ� .�� �̿��ؼ� ����Ű�� ����� ��������� �����ؾ� �Ѵ�.
	(*pStudent).iKor = 50;

	// �޸��ּ�-> �� �̿��ؼ� ����Ű�� ����� ����� �����Ҽ� �ִ�.
	pStudent->iKor = 80;

	cout << tStudent.iKor << endl;

	// void : Ÿ���� ����. void�� ������Ÿ���� Ȱ���� �� �ִ�.
	// void* ������ �����ϰ� �Ǹ� �� ������ � Ÿ���� �޸� �ּҵ� ��� ���尡���ϴ�.
	// ��, �������� �Ұ����ϰ� �޸� �ּҸ� ���� �����ϴ�.
	int iNumber = 100;
	void* pVoid = &iNumber;

	cout << "iNumber Adress : " << pVoid << endl;

	// *pVoid = 10; �Ұ�� ������ ��
	// �ٲٴ� �� 2����
	int* pConvert = (int*)pVoid;
	*pConvert = 1010101010;

	cout << iNumber << endl;

	// �Ǵ�
	*((int*)pVoid) = 9999;

	cout << iNumber << endl;

	pVoid = &tStudent;

	cout << "tStudent Adress : " << pVoid << endl;

	return 0;
}