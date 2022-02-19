#include<iostream>
#include<time.h>

using namespace std;

#define NAME_SIZE			32
#define ITEM_DESC_LENGTH	512
#define INVENTORY_MAX		20
#define STORE_WEAPON_MAX	3
#define STORE_ARMOR_MAX		3
#define LEVEL_MAX			10

enum MAIN_MENU
{
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_HOSPITAL,
	MM_EXIT
};

enum MAP_TYPE
{
	MT_NONE,
	MT_EASY,
	MT_NOMAL,
	MT_HARD,
	MT_BACK
};

enum JOB
{
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END
};

enum BATTLE
{
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
};

enum ITEM_TYPE
{
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};

enum STORE_MENU
{
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
};

enum EQUIP
{
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};

struct _tagItem
{
	char	strName[NAME_SIZE];
	char	strTypeName[NAME_SIZE];
	ITEM_TYPE eType;
	int		iMin;
	int		iMax;
	int		iPrice;
	int		iUseLevel;
	int		iSell;
	char	strDesc[ITEM_DESC_LENGTH];
};

struct _tagInventory
{
	_tagItem	tItem[INVENTORY_MAX];
	int			iItemCount;
	int			iGold;
};

struct _tagPlayer
{
	char	strName[NAME_SIZE];
	char	strJobName[NAME_SIZE];
	JOB		eJob;
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iExp;
	int		iLevel;
	_tagItem		tEquip[EQ_MAX];
	bool			bEquip[EQ_MAX];
	_tagInventory		tInventory;
};

struct _tagMonster
{
	char	strName[NAME_SIZE];
	int		iAttackMin;
	int		iAttackMax;
	int		iArmorMin;
	int		iArmorMax;
	int		iHP;
	int		iHPMax;
	int		iMP;
	int		iMPMax;
	int		iLevel;
	int		iGetExp;
	int		iGetGoldMin;
	int		iGetGoldMax;
};

struct _tagLevelUpStatus
{
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHPMin;
	int iHPMax;
	int iMPMin;
	int iMPMax;
};

int iJobSelect(int iJob);
MAIN_MENU SelectMainMenu();
MAP_TYPE SelectMap();
void OutputPlayer(_tagPlayer tPlayer, const int* iLevelUpExp);
void OutputMonster(_tagMonster tMonster);
STORE_MENU SelectStore();
void OutputWeaponStore(_tagPlayer tPlayer, _tagItem* tStoreWeaponKnight,
	_tagItem* tStoreWeaponArcher, _tagItem* tStoreWeaponWizard);
void OutputArmorStore(_tagPlayer tPlayer, _tagItem* tStoreArmor);
void OutputInventory(_tagPlayer tPlayer);
int SelectHospital();


int main()
{
	srand((unsigned int)time(0));

	// 레벨업에 필요한 목록을 만든다
	const int	iLevelUpExp[LEVEL_MAX] = { 4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000,
	200000, 400000 };

	// JOB_END는 4이다. 직업수가 3개이므로 -1해주어 배열을 각 직업별로 생성한다.
	_tagLevelUpStatus	tLvUpTable[JOB_END - 1] = {};

	tLvUpTable[JOB_KNIGHT - 1].iAttackMin = 4;
	tLvUpTable[JOB_KNIGHT - 1].iAttackMax = 10;
	tLvUpTable[JOB_KNIGHT - 1].iArmorMin = 8;
	tLvUpTable[JOB_KNIGHT - 1].iArmorMax = 16;
	tLvUpTable[JOB_KNIGHT - 1].iHPMin = 50;
	tLvUpTable[JOB_KNIGHT - 1].iHPMax = 100;
	tLvUpTable[JOB_KNIGHT - 1].iMPMin = 10;
	tLvUpTable[JOB_KNIGHT - 1].iMPMax = 20;

	tLvUpTable[JOB_ARCHER - 1].iAttackMin = 10;
	tLvUpTable[JOB_ARCHER - 1].iAttackMax = 15;
	tLvUpTable[JOB_ARCHER - 1].iArmorMin = 5;
	tLvUpTable[JOB_ARCHER - 1].iArmorMax = 10;
	tLvUpTable[JOB_ARCHER - 1].iHPMin = 30;
	tLvUpTable[JOB_ARCHER - 1].iHPMax = 60;
	tLvUpTable[JOB_ARCHER - 1].iMPMin = 30;
	tLvUpTable[JOB_ARCHER - 1].iMPMax = 50;

	tLvUpTable[JOB_WIZARD - 1].iAttackMin = 15;
	tLvUpTable[JOB_WIZARD - 1].iAttackMax = 20;
	tLvUpTable[JOB_WIZARD - 1].iArmorMin = 3;
	tLvUpTable[JOB_WIZARD - 1].iArmorMax = 7;
	tLvUpTable[JOB_WIZARD - 1].iHPMin = 20;
	tLvUpTable[JOB_WIZARD - 1].iHPMax = 40;
	tLvUpTable[JOB_WIZARD - 1].iMPMin = 50;
	tLvUpTable[JOB_WIZARD - 1].iMPMax = 100;

	// 게임을 시작할때 플레이어 정보를 설정하게 한다.
	_tagPlayer tPlayer = {};

	// 플레이어 이름을 입력받는다.
	cout << "캐럭터명 : ";
	cin.getline(tPlayer.strName, NAME_SIZE - 1);
	// -1을 넣어주는 이유는 문자열 인식에 NULL값이 필요하기 때문에

	int iJob = iJobSelect(JOB_NONE);

	tPlayer.iLevel = 1;
	tPlayer.iExp = 0;
	tPlayer.eJob = (JOB)iJob;
	tPlayer.tInventory.iGold = 10000;
	tPlayer.tInventory.iItemCount = 0;

	switch (tPlayer.eJob)
	{
	case JOB_KNIGHT:
		strcpy_s(tPlayer.strJobName, "기사");
		tPlayer.iAttackMin = 5;
		tPlayer.iAttackMax = 10;
		tPlayer.iArmorMin = 15;
		tPlayer.iArmorMax = 20;
		tPlayer.iHP = 500;
		tPlayer.iHPMax = 500;
		tPlayer.iMP = 100;
		tPlayer.iMPMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(tPlayer.strJobName, "궁수");
		tPlayer.iAttackMin = 10;
		tPlayer.iAttackMax = 15;
		tPlayer.iArmorMin = 10;
		tPlayer.iArmorMax = 15;
		tPlayer.iHP = 400;
		tPlayer.iHPMax = 400;
		tPlayer.iMP = 200;
		tPlayer.iMPMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(tPlayer.strJobName, "마법사");
		tPlayer.iAttackMin = 15;
		tPlayer.iAttackMax = 20;
		tPlayer.iArmorMin = 5;
		tPlayer.iArmorMax = 10;
		tPlayer.iHP = 300;
		tPlayer.iHPMax = 300;
		tPlayer.iMP = 300;
		tPlayer.iMPMax = 300;
		break;
	}

	// 몬스터를 생성한다.
	_tagMonster tMonsterArr[MT_BACK - 1] = {};

	// 고블린 생성
	strcpy_s(tMonsterArr[0].strName, "고블린");
	tMonsterArr[0].iAttackMin = 20;
	tMonsterArr[0].iAttackMax = 30;
	tMonsterArr[0].iArmorMin = 2;
	tMonsterArr[0].iArmorMax = 5;
	tMonsterArr[0].iHP = 100;
	tMonsterArr[0].iHPMax = 100;
	tMonsterArr[0].iMP = 10;
	tMonsterArr[0].iMPMax = 10;
	tMonsterArr[0].iLevel = 1;
	tMonsterArr[0].iGetExp = 1000;
	tMonsterArr[0].iGetGoldMin = 500;
	tMonsterArr[0].iGetGoldMax = 1500;

	// 트롤
	strcpy_s(tMonsterArr[1].strName, "트롤");
	tMonsterArr[1].iAttackMin = 80;
	tMonsterArr[1].iAttackMax = 130;
	tMonsterArr[1].iArmorMin = 60;
	tMonsterArr[1].iArmorMax = 90;
	tMonsterArr[1].iHP = 2000;
	tMonsterArr[1].iHPMax = 2000;
	tMonsterArr[1].iMP = 100;
	tMonsterArr[1].iMPMax = 100;
	tMonsterArr[1].iLevel = 5;
	tMonsterArr[1].iGetExp = 7000;
	tMonsterArr[1].iGetGoldMin = 6000;
	tMonsterArr[1].iGetGoldMax = 8000;

	// 드래곤
	strcpy_s(tMonsterArr[2].strName, "드래곤");
	tMonsterArr[2].iAttackMin = 250;
	tMonsterArr[2].iAttackMax = 500;
	tMonsterArr[2].iArmorMin = 200;
	tMonsterArr[2].iArmorMax = 400;
	tMonsterArr[2].iHP = 30000;
	tMonsterArr[2].iHPMax = 30000;
	tMonsterArr[2].iMP = 20000;
	tMonsterArr[2].iMPMax = 20000;
	tMonsterArr[2].iLevel = 10;
	tMonsterArr[2].iGetExp = 30000;
	tMonsterArr[2].iGetGoldMin = 20000;
	tMonsterArr[2].iGetGoldMax = 50000;

	// 상점에서 판매할 아이템목록을 생성한다.
	_tagItem	tStoreWeaponKnight[STORE_WEAPON_MAX] = {};
	_tagItem	tStoreWeaponArcher[STORE_WEAPON_MAX] = {};
	_tagItem	tStoreWeaponWizard[STORE_WEAPON_MAX] = {};
	_tagItem	tStoreArmor[STORE_ARMOR_MAX] = {};

	// 각 아이템 정보를 설정해준다."
	// 기사무기
	strcpy_s(tStoreWeaponKnight[0].strName, "단검");
	strcpy_s(tStoreWeaponKnight[0].strTypeName, "기사무기");
	strcpy_s(tStoreWeaponKnight[0].strDesc, "수행기사가 사용하는 연습용 단검");
	tStoreWeaponKnight[0].iMin = 3;
	tStoreWeaponKnight[0].iMax = 5;
	tStoreWeaponKnight[0].iPrice = 700;
	tStoreWeaponKnight[0].iSell = 500;
	tStoreWeaponKnight[0].iUseLevel = 1;
	tStoreWeaponKnight[0].eType = ITEM_TYPE(IT_WEAPON);

	strcpy_s(tStoreWeaponKnight[1].strName, "장검");
	strcpy_s(tStoreWeaponKnight[1].strTypeName, "기사무기");
	strcpy_s(tStoreWeaponKnight[1].strDesc, "정식기사가 사용하는 검");
	tStoreWeaponKnight[1].iMin = 20;
	tStoreWeaponKnight[1].iMax = 30;
	tStoreWeaponKnight[1].iPrice = 30000;
	tStoreWeaponKnight[1].iSell = 20000;
	tStoreWeaponKnight[1].iUseLevel = 5;
	tStoreWeaponKnight[1].eType = ITEM_TYPE(IT_WEAPON);

	strcpy_s(tStoreWeaponKnight[2].strName, "드래곤나이프");
	strcpy_s(tStoreWeaponKnight[2].strTypeName, "기사무기");
	strcpy_s(tStoreWeaponKnight[2].strDesc, "드래곤을 죽이기위해 만들어진 검");
	tStoreWeaponKnight[2].iMin = 100;
	tStoreWeaponKnight[2].iMax = 150;
	tStoreWeaponKnight[2].iPrice = 150000;
	tStoreWeaponKnight[2].iSell = 120000;
	tStoreWeaponKnight[2].iUseLevel = 10;
	tStoreWeaponKnight[2].eType = ITEM_TYPE(IT_WEAPON);

	// 궁수무기
	strcpy_s(tStoreWeaponArcher[0].strName, "나무활");
	strcpy_s(tStoreWeaponArcher[0].strTypeName, "궁수무기");
	strcpy_s(tStoreWeaponArcher[0].strDesc, "수행궁수가 사용하는 연습용 활");
	tStoreWeaponArcher[0].iMin = 4;
	tStoreWeaponArcher[0].iMax = 6;
	tStoreWeaponArcher[0].iPrice = 700;
	tStoreWeaponArcher[0].iSell = 500;
	tStoreWeaponArcher[0].iUseLevel = 1;
	tStoreWeaponArcher[0].eType = ITEM_TYPE(IT_WEAPON);

	strcpy_s(tStoreWeaponArcher[1].strName, "탄소섬유활");
	strcpy_s(tStoreWeaponArcher[1].strTypeName, "궁수무기");
	strcpy_s(tStoreWeaponArcher[1].strDesc, "정식궁수가 사용하는 활");
	tStoreWeaponArcher[1].iMin = 25;
	tStoreWeaponArcher[1].iMax = 35;
	tStoreWeaponArcher[1].iPrice = 30000;
	tStoreWeaponArcher[1].iSell = 20000;
	tStoreWeaponArcher[1].iUseLevel = 5;
	tStoreWeaponArcher[1].eType = ITEM_TYPE(IT_WEAPON);

	strcpy_s(tStoreWeaponArcher[2].strName, "드래곤보우");
	strcpy_s(tStoreWeaponArcher[2].strTypeName, "궁수무기");
	strcpy_s(tStoreWeaponArcher[2].strDesc, "드래곤을 잡기위해 사용하는 활");
	tStoreWeaponArcher[2].iMin = 110;
	tStoreWeaponArcher[2].iMax = 160;
	tStoreWeaponArcher[2].iPrice = 150000;
	tStoreWeaponArcher[2].iSell = 120000;
	tStoreWeaponArcher[2].iUseLevel = 10;
	tStoreWeaponArcher[2].eType = ITEM_TYPE(IT_WEAPON);

	// 마법사무기
	strcpy_s(tStoreWeaponWizard[0].strName, "완드");
	strcpy_s(tStoreWeaponWizard[0].strTypeName, "마법사무기");
	strcpy_s(tStoreWeaponWizard[0].strDesc, "수행마법사가 사용하는 연습용 완드");
	tStoreWeaponWizard[0].iMin = 7;
	tStoreWeaponWizard[0].iMax = 10;
	tStoreWeaponWizard[0].iPrice = 700;
	tStoreWeaponWizard[0].iSell = 500;
	tStoreWeaponWizard[0].iUseLevel = 1;
	tStoreWeaponWizard[0].eType = ITEM_TYPE(IT_WEAPON);

	strcpy_s(tStoreWeaponWizard[1].strName, "스태프");
	strcpy_s(tStoreWeaponWizard[1].strTypeName, "마법사무기");
	strcpy_s(tStoreWeaponWizard[1].strDesc, "정식마법사가 사용하는 스태프");
	tStoreWeaponWizard[1].iMin = 35;
	tStoreWeaponWizard[1].iMax = 40;
	tStoreWeaponWizard[1].iPrice = 30000;
	tStoreWeaponWizard[1].iSell = 20000;
	tStoreWeaponWizard[1].iUseLevel = 5;
	tStoreWeaponWizard[1].eType = ITEM_TYPE(IT_WEAPON);

	strcpy_s(tStoreWeaponWizard[2].strName, "드래곤스태프");
	strcpy_s(tStoreWeaponWizard[2].strTypeName, "마법사무기");
	strcpy_s(tStoreWeaponWizard[2].strDesc, "드래곤을 잡기위해 사용하는 스태프");
	tStoreWeaponWizard[2].iMin = 150;
	tStoreWeaponWizard[2].iMax = 200;
	tStoreWeaponWizard[2].iPrice = 150000;
	tStoreWeaponWizard[2].iSell = 120000;
	tStoreWeaponWizard[2].iUseLevel = 10;
	tStoreWeaponWizard[2].eType = ITEM_TYPE(IT_WEAPON);

	// 방어구
	strcpy_s(tStoreArmor[0].strName, "기본갑옷");
	strcpy_s(tStoreArmor[0].strTypeName, "방어구");
	strcpy_s(tStoreArmor[0].strDesc, "수행기사가 사용하는 방어구");
	tStoreArmor[0].iMin = 3;
	tStoreArmor[0].iMax = 5;
	tStoreArmor[0].iPrice = 500;
	tStoreArmor[0].iSell = 300;
	tStoreArmor[0].iUseLevel = 1;
	tStoreArmor[0].eType = ITEM_TYPE(IT_ARMOR);

	strcpy_s(tStoreArmor[1].strName, "정식갑옷");
	strcpy_s(tStoreArmor[1].strTypeName, "방어구");
	strcpy_s(tStoreArmor[1].strDesc, "정식기사가 사용하는 방어구");
	tStoreArmor[1].iMin = 20;
	tStoreArmor[1].iMax = 30;
	tStoreArmor[1].iPrice = 20000;
	tStoreArmor[1].iSell = 15000;
	tStoreArmor[1].iUseLevel = 5;
	tStoreArmor[1].eType = ITEM_TYPE(IT_ARMOR);

	strcpy_s(tStoreArmor[2].strName, "드래곤아머");
	strcpy_s(tStoreArmor[2].strTypeName, "방어구");
	strcpy_s(tStoreArmor[2].strDesc, "드래곤을 잡기위해 사용하는 방어구");
	tStoreArmor[2].iMin = 70;
	tStoreArmor[2].iMax = 100;
	tStoreArmor[2].iPrice = 100000;
	tStoreArmor[2].iSell = 80000;
	tStoreArmor[2].iUseLevel = 10;
	tStoreArmor[2].eType = ITEM_TYPE(IT_ARMOR);

	while (true)
	{
		int iMenu = SelectMainMenu();

		if (iMenu == MM_EXIT)
			break;

		switch (iMenu)
		{
		case MM_MAP:
			while (true)
			{
				iMenu = SelectMap();

				// 이 if문에 속한 break는 맵메뉴를 돌려주기 위한 while문에 속해있으므로
				// 이 while문을 나간다.
				if (iMenu == MT_BACK)
					break;

				// 선택한 메뉴에서 -1을 해주면 몬스터 배열의 인덱스가 된다.
				// 그렇게 해서 해당 맵의 몬스터를 생성해준다.
				_tagMonster tMonster = tMonsterArr[iMenu - 1];

				while (true)
				{
					system("cls");
					switch (iMenu)
					{
					case MT_EASY:
						cout << "******************** 쉬움 ********************" << endl;
						break;
					case MT_NOMAL:
						cout << "******************** 보통 ********************" << endl;
						break;
					case MT_HARD:
						cout << "******************* 어려움 *******************" << endl;
						break;
					}

					// 플레이어 정보를 출력한다.
					cout << "=================== Player ===================" << endl;
					OutputPlayer(tPlayer, iLevelUpExp);
					cout << endl;

					// 몬스터 정보 출력
					cout << "================== Monster ===================" << endl;
					OutputMonster(tMonster);
					cout << endl;

					cout << "1. 공격" << endl;
					cout << "2. 도망가기" << endl;
					cout << "메뉴를 선택하세요 : ";
					cin >> iMenu;

					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					else if (iMenu == BATTLE_BACK)
						break;

					switch (iMenu)
					{
					case BATTLE_ATTACK:
					{
						int iAttackMin = tPlayer.iAttackMin;
						int iAttackMax = tPlayer.iAttackMax;

						if (tPlayer.bEquip[EQ_WEAPON])
						{
							iAttackMin += tPlayer.tEquip[EQ_WEAPON].iMin;
							iAttackMax += tPlayer.tEquip[EQ_WEAPON].iMax;
						}

						int iAttack = rand() % (iAttackMax - iAttackMin + 1) + iAttackMin;
						int iArmor = rand() % (tMonster.iArmorMax - tMonster.iArmorMin + 1)
							+ tMonster.iArmorMin;

						int iDamage = iAttack - iArmor;
						// 삼항연산자 : 조건식 ? true일때값 : false일때값;
						iDamage = iDamage < 1 ? 1 : iDamage;

						// 몬스터 HP를 감소시킨다.
						tMonster.iHP -= iDamage;

						cout << tPlayer.strName << "가 " << tMonster.strName << "에게 "
							<< iDamage << "만큼 피해를 입혔습니다." << endl;

						// 몬스터가 죽었을 경우를 처리한다.
						if (tMonster.iHP <= 0)
						{
							cout << tMonster.strName << "가 사망했습니다." << endl;

							tPlayer.iExp += tMonster.iGetExp;
							int iGold =
								rand() % (tMonster.iGetGoldMax - tMonster.iGetGoldMin + 1)
								+ tMonster.iGetGoldMin;
							tPlayer.tInventory.iGold += iGold;

							cout << tMonster.iGetExp << "경험치를 획득하였습니다." << endl;
							cout << iGold << "Gold를 획득하였습니다." << endl;

							tMonster.iHP = tMonster.iHPMax;
							tMonster.iMP = tMonster.iMPMax;

							// 레벨업을 했는지 체크해본다.
							if (tPlayer.iExp >= iLevelUpExp[tPlayer.iLevel - 1])
							{
								// 플레이어 경험치를 레벨업에 필요한 경험치만큼 차감한다.
								tPlayer.iExp -= iLevelUpExp[tPlayer.iLevel - 1];

								// 레벨을 증가시킨다.
								tPlayer.iLevel++;

								cout << "레벨업 하였습니다." << endl;

								// 능력치를 상승시킨다.
								// 직업인덱스를 구한다.
								int iJobIndex = tPlayer.eJob - 1;
								int iAttackUp = rand() % (tLvUpTable[iJobIndex].iAttackMax -
									tLvUpTable[iJobIndex].iAttackMin + 1) + tLvUpTable[iJobIndex].iAttackMin;
								int iArmorUp = rand() % (tLvUpTable[iJobIndex].iArmorMax -
									tLvUpTable[iJobIndex].iArmorMin + 1) + tLvUpTable[iJobIndex].iArmorMin;
								int iHPUP = rand() % (tLvUpTable[iJobIndex].iHPMax -
									tLvUpTable[iJobIndex].iHPMin + 1) + tLvUpTable[iJobIndex].iHPMin;
								int iMPUP = rand() % (tLvUpTable[iJobIndex].iMPMax -
									tLvUpTable[iJobIndex].iMPMin + 1) + tLvUpTable[iJobIndex].iMPMin;

								tPlayer.iAttackMin += tLvUpTable[iJobIndex].iAttackMin;
								tPlayer.iAttackMax += tLvUpTable[iJobIndex].iAttackMax;
								tPlayer.iArmorMin += tLvUpTable[iJobIndex].iArmorMin;
								tPlayer.iArmorMax += tLvUpTable[iJobIndex].iArmorMax;
								tPlayer.iHPMax += iHPUP;
								tPlayer.iMPMax += iMPUP;

								// 체력과 마나를 회복시켜준다.
								tPlayer.iHP = tPlayer.iHPMax;
								tPlayer.iMP = tPlayer.iMPMax;
							}

							system("pause");
							break;
						}

						// 몬스터가 살아있다면 플레이어를 공격한다.
						iAttack = rand() % (tMonster.iAttackMax - tMonster.iAttackMin + 1)
							+ tMonster.iAttackMin;

						int iArmorMin = tPlayer.iArmorMin;
						int iArmorMax = tPlayer.iArmorMax;

						if (tPlayer.bEquip[EQ_ARMOR])
						{
							iArmorMin += tPlayer.tEquip[EQ_ARMOR].iMin;
							iArmorMax += tPlayer.tEquip[EQ_ARMOR].iMax;
						}

						iArmor = rand() % (iArmorMax - iArmorMin + 1) + iArmorMin;

						iDamage = iAttack - iArmor;
						iDamage = iDamage < 1 ? 1 : iDamage;

						// 플레이어의 HP를 감소시킨다.
						tPlayer.iHP -= iDamage;

						cout << tMonster.strName << "가 " << tPlayer.strName << "에게 "
							<< iDamage << "만큼 피해를 입혔습니다." << endl;

						// 플레이어가 죽었을경우
						if (tPlayer.iHP <= 0)
						{
							cout << tPlayer.strName << "플레이어가 사망하였습니다." << endl;

							int iExp = tPlayer.iExp * 0.1f;
							int iGold = tPlayer.tInventory.iGold * 0.1f;

							tPlayer.iExp -= iExp;
							tPlayer.tInventory.iGold -= iGold;

							cout << iExp << "경험치를 잃었습니다." << endl;
							cout << iGold << "Gold를 잃었습니다." << endl;

							tPlayer.iHP = tPlayer.iHPMax;
							tPlayer.iMP = tPlayer.iMPMax;
						}

						system("pause");
					}
					break;
					}

				}
			}
			break;
		case MM_STORE:
			while (true)
			{
				iMenu = SelectStore();

				if (iMenu == SM_BACK)
					break;

				switch (iMenu)
				{
				case SM_WEAPON:
					while (true)
					{
						system("cls");
						// 판매목록을 보여준다.
						OutputWeaponStore(tPlayer, tStoreWeaponKnight, 
							tStoreWeaponArcher, tStoreWeaponWizard);

						cout << STORE_WEAPON_MAX + 1 << ". 뒤로가기" << endl << endl;
						cout << "보유금액 : " << tPlayer.tInventory.iGold << "Gold" << endl;
						cout << "남은공간 : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
						cout << "구입할 아이템을 선택하세요 : ";
						cin >> iMenu;

						if (cin.fail())
						{
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}
						else if (iMenu == STORE_WEAPON_MAX + 1)
							break;
						else if (iMenu > STORE_WEAPON_MAX + 1 || iMenu < 1)
						{
							cout << "잘못 입력하셨습니다." << endl;
							system("pause");
							continue;
						}

						// 상점판매 목록 인덱스를 구해준다.
						int iWeaponIndex = iMenu - 1;

						// 인벤토리가 꽉 찼는지 검사한다.
						if (tPlayer.tInventory.iItemCount == INVENTORY_MAX)
						{
							cout << "가방이 꽉 찼습니다." << endl;
							system("pause");
							continue;
						}
						// 돈이 부족한 경우
						else if (tPlayer.tInventory.iGold < tStoreWeaponKnight[iWeaponIndex].iPrice ||
							tPlayer.tInventory.iGold < tStoreWeaponArcher[iWeaponIndex].iPrice ||
							tPlayer.tInventory.iGold < tStoreWeaponWizard[iWeaponIndex].iPrice)
						{
							cout << "보유금액이 부족합니다." << endl;
							system("pause");
							continue;
						}

						// 처음에는 iItemCount는 하나도 추가되어있지 않기 때문에 0으로 초기화 되어
						// 있으므로 0번 인덱스에 구매한 아이템을 추가하게 된다. 그리고 카운트가 1이
						// 된다. 다음번에 추가할때는 1번 인덱스에 추가하게 된다.
						if (tPlayer.eJob == JOB_KNIGHT)
							tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount]
							= tStoreWeaponKnight[iWeaponIndex];
						else if (tPlayer.eJob == JOB_ARCHER)
							tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount]
							= tStoreWeaponArcher[iWeaponIndex];
						else if (tPlayer.eJob == JOB_WIZARD)
							tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount]
							= tStoreWeaponWizard[iWeaponIndex];

						tPlayer.tInventory.iItemCount++;

						// 골드를 차감한다.
						if (tPlayer.eJob == JOB_KNIGHT)
						{
							tPlayer.tInventory.iGold -= tStoreWeaponKnight[iWeaponIndex].iPrice;
							cout << tStoreWeaponKnight[iWeaponIndex].strName
								<< " 아이템을 구매하였습니다." << endl;
							system("pause");
						}
						else if (tPlayer.eJob == JOB_ARCHER)
						{
							tPlayer.tInventory.iGold -= tStoreWeaponArcher[iWeaponIndex].iPrice;
							cout << tStoreWeaponArcher[iWeaponIndex].strName
								<< " 아이템을 구매하였습니다." << endl;
							system("pause");
						}
						else if (tPlayer.eJob == JOB_WIZARD)
						{
							tPlayer.tInventory.iGold -= tStoreWeaponWizard[iWeaponIndex].iPrice;
							cout << tStoreWeaponWizard[iWeaponIndex].strName
								<< " 아이템을 구매하였습니다." << endl;
							system("pause");
						}

					}
					break;
				case SM_ARMOR:
					while (true)
					{
						system("cls");
						OutputArmorStore(tPlayer, tStoreArmor);

						cout << STORE_ARMOR_MAX + 1 << ". 뒤로가기" << endl << endl;
						cout << "보유금액 : " << tPlayer.tInventory.iGold << "Gold" << endl;
						cout << "남은공간 : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
						cout << "구입할 아이템을 선택하세요 : ";
						cin >> iMenu;

						if (cin.fail())
						{
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}
						else if (iMenu == STORE_ARMOR_MAX + 1)
							break;
						else if (iMenu > STORE_ARMOR_MAX + 1 || iMenu < 1)
						{
							cout << "잘못 입력하셨습니다." << endl;
							system("pause");
							continue;
						}

						// 상점판매 목록 인덱스를 구해준다.
						int iAmorIndex = iMenu - 1;

						// 인벤토리가 꽉 찼는지 검사한다.
						if (tPlayer.tInventory.iItemCount == INVENTORY_MAX)
						{
							cout << "가방이 꽉 찼습니다." << endl;
							system("pause");
							continue;
						}
						// 돈이 부족한 경우
						else if (tPlayer.tInventory.iGold < tStoreArmor[iAmorIndex].iPrice)
						{
							cout << "보유금액이 부족합니다." << endl;
							system("pause");
							continue;
						}

						tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount]
							= tStoreArmor[iAmorIndex];

						tPlayer.tInventory.iItemCount++;

						tPlayer.tInventory.iGold -= tStoreArmor[iAmorIndex].iPrice;
						cout << tStoreArmor[iAmorIndex].strName << " 아이템을 구매하였습니다." << endl;
						system("pause");

					}
					break;
				}

			}
			break;
		case MM_INVENTORY:
			while (true)
			{
				system("cls");
				cout << "******************** 가방 ********************" << endl;
				cout << "=================== Player ===================" << endl;
				OutputPlayer(tPlayer, iLevelUpExp);
				cout << "==============================================" << endl << endl;

				OutputInventory(tPlayer);

				cout << tPlayer.tInventory.iItemCount + 1 << ". 뒤로가기" << endl;
				cout << "장착할 아이템을 선택하세요 : ";
				cin >> iMenu;

				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				else if (iMenu == tPlayer.tInventory.iItemCount + 1)
					break;

				else if (iMenu < 1 || iMenu > tPlayer.tInventory.iItemCount + 1)
				{
					cout << "잘못 입력하셨습니다." << endl;
					system("pause");
					continue;
				}

				// 아이템 인덱스를 구해준다.
				int idx = iMenu - 1;

				// 제대로 선택했을 경우 해당아이템의 종류에 따라 장착 부위를 결정한다.
				EQUIP	eq;

				switch (tPlayer.tInventory.tItem[idx].eType)
				{
				case IT_WEAPON:
					eq = EQ_WEAPON;
					break;
				case IT_ARMOR:
					eq = EQ_ARMOR;
					break;
				}

				// 아이템이 장착되어 있는 경우 장착되어있는 아이템과 장착할 아이템을 교체해주어야 한다.
				// Swap 알고리즘을 활용한다.
				if (tPlayer.bEquip[eq] == true)
				{
					_tagItem	tSwap = tPlayer.tEquip[eq];
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];
					tPlayer.tInventory.tItem[idx] = tSwap;
				}

				// 장착되어있지 않을 경우 인벤토리 아이템을 장착장으로 옮기고 인벤토리 1칸이 비워진다.
				else
				{
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];

					for (int i = idx; i < tPlayer.tInventory.iItemCount - 1; i++)
					{
						tPlayer.tInventory.tItem[i] = tPlayer.tInventory.tItem[i + 1];
					}

					tPlayer.tInventory.iItemCount--;

					// 장착을 했기 때문에 true로 만들어준다.
					tPlayer.bEquip[eq] = true;
				}

				cout << tPlayer.tEquip[eq].strName << "아이템을 장착했습니다." << endl;

				system("pause");
			}

			break;
		case MM_HOSPITAL:
			while (true)
			{
				iMenu = SelectHospital();
				
				if (iMenu == 2)
					break;

				if (iMenu == 1)
				{
					if (tPlayer.iHP == tPlayer.iHPMax && tPlayer.iMP == tPlayer.iMPMax)
					{
						cout << "체력이 모두다 차있습니다." << endl;
						system("pause");
					}
					else
					{
						cout << "체력을 회복하였습니다." << endl;
						tPlayer.iHP = tPlayer.iHPMax;
						tPlayer.iMP = tPlayer.iMPMax;
						tPlayer.tInventory.iGold -= 1000;
						cout << "남은골드 : " << tPlayer.tInventory.iGold << endl;
						system("pause");
					}
				}

			}

			break;
		}
	}

	return 0;
}

int iJobSelect(int iJob)
{
	while (iJob == JOB_NONE)
	{
		system("cls");
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "원하는 직업을 선택하세요 : ";
		cin >> iJob;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		else if (iJob <= JOB_NONE || iJob >= JOB_END)
			iJob = JOB_NONE;
	}

	return iJob;
}

MAIN_MENU SelectMainMenu()
{
	int iMenu;

	while (true)
	{
		system("cls");
		cout << "******************** 로비 ********************" << endl;
		cout << "1. 맵" << endl;
		cout << "2. 상점" << endl;
		cout << "3. 가방" << endl;
		cout << "4. 체력회복" << endl;
		cout << "5. 종료" << endl;
		cout << "메뉴를 선택하세요 : ";
		cin >> iMenu;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (iMenu < MM_NONE || iMenu > MM_EXIT)
		{
			cout << "잘못 선택하셨습니다." << endl;
			system("pause");
			continue;
		}
		else
			break;
	}

	return (MAIN_MENU)iMenu;
}

MAP_TYPE SelectMap()
{
	int iMenu;

	while (true)
	{
		system("cls");

		cout << "********************* 맵 *********************" << endl;
		cout << "1, 쉬움" << endl;
		cout << "2, 보통" << endl;
		cout << "3, 어려움" << endl;
		cout << "4, 뒤로가기" << endl;
		cout << "맵을 선택하세요 : ";
		cin >> iMenu;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (iMenu < MT_NONE || iMenu > MT_BACK)
		{
			cout << "잘못 선택하셨습니다." << endl;
			system("pause");
			continue;
		}
		else
			break;
	}

	return (MAP_TYPE)iMenu;
}

void OutputPlayer(_tagPlayer tPlayer,const int* iLevelUpExp)
{
	cout << "이름 : " << tPlayer.strName << "\t\t직업 : "
		<< tPlayer.strJobName << endl;
	cout << "레벨 : " << tPlayer.iLevel << "\t\t경험치 : "
		<< tPlayer.iExp << " / " << iLevelUpExp[tPlayer.iLevel-1] << endl;

	// 무기를 장착하고 있을경우 공격력에 무기공격력을 추가하여 출력한다.
	if (tPlayer.bEquip[EQ_WEAPON] == true)
	{
		cout << "공격력 : " << tPlayer.iAttackMin << "+" << tPlayer.tEquip[EQ_WEAPON].iMin
			<< " ~ " << tPlayer.iAttackMax << "+" << tPlayer.tEquip[EQ_WEAPON].iMax;
	}
	else
	{
		cout << "공격력 : " << tPlayer.iAttackMin << " ~ " << tPlayer.iAttackMax;
	}

	// 방어구를 장착하고 있을때
	if (tPlayer.bEquip[EQ_ARMOR] == true)
	{
		cout << "\t방어력 : " << tPlayer.iArmorMin << "+" << tPlayer.tEquip[EQ_ARMOR].iMin
			<< " ~ " << tPlayer.iArmorMax << "+" << tPlayer.tEquip[EQ_ARMOR].iMax << endl;
	}
	else
	{
		cout << "\t방어력 : " << tPlayer.iArmorMin << " ~ " << tPlayer.iArmorMax << endl;
	}

	cout << "체력 : " << tPlayer.iHP << " / " << tPlayer.iHPMax
		<< "\t마나 : " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;

	if (tPlayer.bEquip[EQ_WEAPON])
		cout << "장착무기 : " << tPlayer.tEquip[EQ_WEAPON].strName;
	else
		cout << "장착무기 : 없음";

	if (tPlayer.bEquip[EQ_ARMOR])
		cout << "\t\t장착방어구 : " << tPlayer.tEquip[EQ_ARMOR].strName << endl;
	else
		cout << "\t\t장착방어구 : 없음" << endl;

	cout << "보유골드 : " << tPlayer.tInventory.iGold << "Gold" << endl;
}

void OutputMonster(_tagMonster tMonster)
{
	cout << "이름 : " << tMonster.strName << "\t\t레벨 : "
		<< tMonster.iLevel << endl;
	cout << "공겨격 : " << tMonster.iAttackMin << " ~ " << tMonster.iArmorMax
		<< "\t\t방어력 : " << tMonster.iArmorMin << " ~ " << tMonster.iArmorMax << endl;
	cout << "체력 : " << tMonster.iHP << " / " << tMonster.iHPMax
		<< "\t마나 : " << tMonster.iMP << " / " << tMonster.iMPMax << endl;
	cout << "획득경험치 : " << tMonster.iGetExp << "\t획득골드 : "
		<< tMonster.iGetGoldMin << " ~ " << tMonster.iGetGoldMax << endl;
}

STORE_MENU SelectStore()
{
	int iMenu;

	while (true)
	{
		system("cls");
		cout << "******************** 상점 ********************" << endl;
		cout << "1. 무기상점" << endl;
		cout << "2. 방어구상점" << endl;
		cout << "3. 뒤로가기" << endl;
		cout << "상점을 선택하세요 : ";
		cin >> iMenu;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (iMenu < SM_NONE || iMenu > SM_BACK)
		{
			cout << "잘못된 선택입니다." << endl;
			system("pause");
			continue;
		}
		else
			break;
	}

	return (STORE_MENU)iMenu;
}

void OutputWeaponStore(_tagPlayer tPlayer, _tagItem* tStoreWeaponKnight,
	_tagItem* tStoreWeaponArcher, _tagItem* tStoreWeaponWizard)
{
	cout << "****************** 무기상점 ******************" << endl;
	if (tPlayer.eJob == JOB_KNIGHT)
	{
		for (int i = 0; i < STORE_WEAPON_MAX; i++)
		{
			cout << i + 1 << ". 이름 : " << tStoreWeaponKnight[i].strName <<
				"\t종류 : " << tStoreWeaponKnight[i].strTypeName << endl;
			cout << "착용레벨 : " << tStoreWeaponKnight[i].iUseLevel << endl;
			cout << "공격력 : " << tStoreWeaponKnight[i].iMin << " ~ " <<
				tStoreWeaponKnight[i].iMax << endl;
			cout << "구매가격 : " << tStoreWeaponKnight[i].iPrice <<
				"\t판매가격 : " << tStoreWeaponKnight[i].iSell << endl;
			cout << "설명 : " << tStoreWeaponKnight[i].strDesc << endl << endl;
		}
	}
	else if (tPlayer.eJob == JOB_ARCHER)
	{
		for (int i = 0; i < STORE_WEAPON_MAX; i++)
		{
			cout << i + 1 << ". 이름 : " << tStoreWeaponArcher[i].strName <<
				"\t종류 : " << tStoreWeaponArcher[i].strTypeName << endl;
			cout << "착용레벨 : " << tStoreWeaponArcher[i].iUseLevel << endl;
			cout << "공격력 : " << tStoreWeaponArcher[i].iMin << " ~ " <<
				tStoreWeaponArcher[i].iMax << endl;
			cout << "구매가격 : " << tStoreWeaponArcher[i].iPrice <<
				"\t판매가격 : " << tStoreWeaponArcher[i].iSell << endl;
			cout << "설명 : " << tStoreWeaponArcher[i].strDesc << endl << endl;
		}
	}
	else if (tPlayer.eJob == JOB_WIZARD)
	{
		for (int i = 0; i < STORE_WEAPON_MAX; i++)
		{
			cout << i + 1 << ". 이름 : " << tStoreWeaponWizard[i].strName <<
				"\t종류 : " << tStoreWeaponWizard[i].strTypeName << endl;
			cout << "착용레벨 : " << tStoreWeaponWizard[i].iUseLevel << endl;
			cout << "공격력 : " << tStoreWeaponWizard[i].iMin << " ~ " <<
				tStoreWeaponWizard[i].iMax << endl;
			cout << "구매가격 : " << tStoreWeaponWizard[i].iPrice <<
				"\t판매가격 : " << tStoreWeaponWizard[i].iSell << endl;
			cout << "설명 : " << tStoreWeaponWizard[i].strDesc << endl << endl;
		}
	}
}

void OutputArmorStore(_tagPlayer tPlayer, _tagItem* tStoreArmor)
{
	cout << "***************** 방어구상점 *****************" << endl;
	for (int i = 0; i < STORE_ARMOR_MAX; i++)
	{
		cout << i + 1 << ". 이름 : " << tStoreArmor[i].strName <<
			"\t종류 : " << tStoreArmor[i].strTypeName << endl;
		cout << "착용레벨 : " << tStoreArmor[i].iUseLevel << endl;
		cout << "방어력 : " << tStoreArmor[i].iMin << " ~ " <<
			tStoreArmor[i].iMax << endl;
		cout << "구매가격 : " << tStoreArmor[i].iPrice <<
			"\t판매가격 : " << tStoreArmor[i].iSell << endl;
		cout << "설명 : " << tStoreArmor[i].strDesc << endl << endl;
	}
}

void OutputInventory(_tagPlayer tPlayer)
{
	for (int i = 0; i < tPlayer.tInventory.iItemCount; i++)
	{
		cout << i + 1 << ".이름 : " << tPlayer.tInventory.tItem[i].strName <<
			"\t종류 : " << tPlayer.tInventory.tItem[i].strTypeName << endl;
		if (tPlayer.tInventory.tItem[i].eType == IT_WEAPON)
		{
			cout << "공격력 : " << tPlayer.tInventory.tItem[i].iMin <<
				" ~ " << tPlayer.tInventory.tItem[i].iMax << endl;
		}
		else if (tPlayer.tInventory.tItem[i].eType == IT_ARMOR)
		{
			cout << "방어력 : " << tPlayer.tInventory.tItem[i].iMin <<
				" ~ " << tPlayer.tInventory.tItem[i].iMax << endl;
		}
		cout << "설명 : " << tPlayer.tInventory.tItem[i].strDesc << endl << endl;
	}
}

int SelectHospital()
{
	int iMenu;
	while (true)
	{
		system("cls");
		cout << "******************** 병원 ********************" << endl;
		cout << "1000Gold를 지불하고 체력을 회복하겠습니까?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. 돌아가기" << endl;
		cout << "메뉴를 선택하세요 : ";
		cin >> iMenu;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (iMenu > 2 || iMenu < 1)
		{
			cout << "잘못된 입력입니다." << endl;
			system("pause");
			continue;
		}
		else
			break;
	}

	return iMenu;
}