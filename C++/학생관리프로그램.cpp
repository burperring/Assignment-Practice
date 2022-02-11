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
	// 배열에 추가된 개수를 저장할 변수를 추가해준다.
	int iStudnetCount = 0;
	int iStdNumber = 1;

	char strName[NAME_SIZE] = {};

	while (true)
	{
		system("cls");

		// 메뉴를 출력한다.
		cout << "1. 학생등록" << endl;
		cout << "2. 학생삭재" << endl;
		cout << "3. 학생검색" << endl;
		cout << "4. 학생출력" << endl;
		cout << "5. 종료" << endl;
		cout << "메뉴를 선택하세요 : ";
		int iMenu;
		cin >> iMenu;

		// cin은 오른쪽에 int변수가 오면 정수를 입력해야한다. 오른쪽에 오느 변수타입에 맞춰서
		// 값을 입력해야 하는데 실수로 정수가 아닌 문자를 입력할 경우 에러가 발생한다.
		// 그렇기 때문에 예외처리로 에러가 발생했는지를 여기에서 체크하여 에러가 발생하면
		// cin 내부의 에러버퍼를 비워주고 cin 내부에 입력버퍼가 있는데 입력버퍼는 입력한 값을 
		// 저장해놓고 그값을 변수에 넣어주는 역할을 한다. 이 입력버퍼에 \n 이 남아있으므로 
		// 버퍼를 순회하여 \n을 지워준다.
		// 버퍼 : 임시적인저장공간이다.
		// 먼저 에러를 체크한다. cin.fail() 을 했을때 에러가 발생하면 true를 반환한다.
		if (cin.fail())
		{
			// 에러버퍼를 지워준다.
			cin.clear();

			// 입력버퍼에 \n 이 남아있으므로 입력버퍼를 검색하여 \n 을 지워준다.
			// 첫번째는 검색하고자 하는	버퍼크기를 지정한다. 넉넉하게 1024 바이트정도 지정
			// 두번째는 찾고자하는 문자를 넣어준다.
			// 그래서 입력버퍼 처음부터 \n이 있는곳까지 찾아서 그 부분을 모두 지워준다.
			cin.ignore(1024, '\n');
			continue;
		}

		if (iMenu == MENU_EXIT)
			break;

		switch (iMenu)
		{
		case MENU_INSERT:
			system("cls");
			cout << "=============== 학생추가 ===============" << endl;

			// 등록된 학생이 등록할수 있는 최대치일 경우 더이상 등록이 되지않게 만든다.
			if (iStudnetCount == STUDENT_MAX)
			{
				cout << "등록할수 있는 학생수가 최대치입니다." << endl;
				system("pause");
				break;
			}

			// 학생정보를 추가한다. 학생정보는 이름, 주소, 전화번호, 국영수 점수는 입력받고,
			// 학번, 총점, 평균은 연산을 통해 계산해준다.
			// 이름을 입력받는다.
			cout << "이름 : ";
			cin >> tStudentArr[iStudnetCount].strName;

			cin.ignore(1024, '\n');

			cout << "주소 : ";
			cin.getline(tStudentArr[iStudnetCount].strAdress, ADDRESS_SIZE);

			cout << "전화번호 : ";
			cin.getline(tStudentArr[iStudnetCount].strPhoneNumber, PHONE_SIZE);

			cout << "국어 : ";
			cin >> tStudentArr[iStudnetCount].iKor;

			cout << "영어 : ";
			cin >> tStudentArr[iStudnetCount].iEng;

			cout << "수학 : ";
			cin >> tStudentArr[iStudnetCount].iMath;

			tStudentArr[iStudnetCount].iTotal = 
				tStudentArr[iStudnetCount].iKor +
				tStudentArr[iStudnetCount].iEng + 
				tStudentArr[iStudnetCount].iMath;

			tStudentArr[iStudnetCount].fAvg = tStudentArr[iStudnetCount].iTotal / 3.f;

			tStudentArr[iStudnetCount].iNumber = iStdNumber;

			iStdNumber++;
			iStudnetCount++;

			cout << "학생추가완료" << endl;
			break;
		case MENU_DELETE:
			system("cls");

			cout << "=============== 학생삭제 ===============" << endl;

			if (iStudnetCount == 0)
			{
				cout << "현재 등록된 학생수가 없습니다." << endl;
				break;
			}

			cin.ignore(1024, '\n');
			cout << "삭제할 학생 이름을 입력하세요 : ";
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

					cout << "학생을 삭제했습니다." << endl;
					break;
				}
			}

			break;
		case MENU_SEARCH:
			system("cls");

			cout << "=============== 학생검색 ===============" << endl;

			if (iStudnetCount == 0)
			{
				cout << "현재 등록된 학생수가 없습니다." << endl;
				break;
			}

			cin.ignore(1024, '\n');
			cout << "검색할 학생 이름을 입력하세요 : ";
			cin.getline(strName, NAME_SIZE);

			// 등록되어있는 학생수 만큼 반복하며 학생을 찾는다.
			for (int i = 0; i < iStudnetCount; i++)
			{
				// 학생을 찾았을 경우
				if (strcmp(tStudentArr[i].strName, strName) == 0)
				{
					cout << "학번 : " << tStudentArr[i].iNumber << endl;
					cout << "이름 : " << tStudentArr[i].strName << endl;
					cout << "주소 : " << tStudentArr[i].strAdress << endl;
					cout << "전화번호 : " << tStudentArr[i].strPhoneNumber << endl;
					cout << "국어 : " << tStudentArr[i].iKor << endl;
					cout << "영어 : " << tStudentArr[i].iEng << endl;
					cout << "수학 : " << tStudentArr[i].iMath << endl;
					cout << "총점 : " << tStudentArr[i].iTotal << endl;
					cout << "평균 : " << tStudentArr[i].fAvg << endl;
					cout << "========================================" << endl;
					break;
				}
			}

			break;
		case MENU_OUTPUT:
			system("cls");

			cout << "=============== 학생출력 ===============" << endl;

			if (iStudnetCount == 0)
			{
				cout << "현재 등록된 학생수가 없습니다." << endl;
				break;
			}

			// 등록된 학생수만큼 반복하며 학생정보를 출력한다.
			for (int i = 0; i < iStudnetCount; i++)
			{
				cout << "학번 : " << tStudentArr[i].iNumber << endl;
				cout << "이름 : " << tStudentArr[i].strName << endl;
				cout << "주소 : " << tStudentArr[i].strAdress << endl;
				cout << "전화번호 : " << tStudentArr[i].strPhoneNumber << endl;
				cout << "국어 : " << tStudentArr[i].iKor << endl;
				cout << "영어 : " << tStudentArr[i].iEng << endl;
				cout << "수학 : " << tStudentArr[i].iMath << endl;
				cout << "총점 : " << tStudentArr[i].iTotal << endl;
				cout << "평균 : " << tStudentArr[i].fAvg << endl;
				cout << "========================================" << endl;
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