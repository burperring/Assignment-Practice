#include <iostream>
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

enum EQUIP
{
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};

enum STORE_MENU
{
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
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

// 레벨업에 필요한 목록을 만든다
const int	g_iLevelUpExp[LEVEL_MAX] = { 4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000,
200000, 400000 };
_tagLevelUpStatus	g_tLvUpTable[JOB_END - 1] = {};

int InputInt()
{
	int iInput;
	cin >> iInput;

	if (cin.fail())
	{
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX; // INT_MAX가 입력되면 잘못된 입력이라는 의미부여
	}

	return iInput;
}

int OutputMainMenu()
{
	system("cls");
	cout << "******************** 로비 ********************" << endl;
	cout << "1. 맵" << endl;
	cout << "2. 상점" << endl;
	cout << "3. 가방" << endl;
	cout << "4. 체력회복" << endl;
	cout << "5. 종료" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iMenu = InputInt();

	if (iMenu == INT_MAX || iMenu <= MM_NONE || iMenu > MM_EXIT)
		return MM_NONE;

	return iMenu;
}

int SelectJob()
{
	int iJob = JOB_NONE;
	while (iJob == JOB_NONE)
	{
		system("cls");
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "원하는 직업을 선택하세요 : ";
		iJob = InputInt();

		if (iJob <= JOB_NONE || iJob >= JOB_END)
			iJob = JOB_NONE;
	}

	return iJob;
}

void SetPlayer(_tagPlayer* pPlayer)
{
	// 플레이어 이름을 입력받는다.
	cout << "이름 : ";
	cin.getline(pPlayer->strName, NAME_SIZE - 1);

	pPlayer->eJob = (JOB)SelectJob();
	pPlayer->iLevel = 1;
	pPlayer->iExp = 0;
	pPlayer->tInventory.iGold = 10000;

	switch (pPlayer->eJob)
	{
	case JOB_KNIGHT:
		strcpy_s(pPlayer->strJobName, "기사");
		pPlayer->iAttackMin = 5;
		pPlayer->iAttackMax = 10;
		pPlayer->iArmorMin = 15;
		pPlayer->iArmorMax = 20;
		pPlayer->iHP = 500;
		pPlayer->iHPMax = 500;
		pPlayer->iMP = 100;
		pPlayer->iMPMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(pPlayer->strJobName, "궁수");
		pPlayer->iAttackMin = 10;
		pPlayer->iAttackMax = 15;
		pPlayer->iArmorMin = 10;
		pPlayer->iArmorMax = 15;
		pPlayer->iHP = 400;
		pPlayer->iHPMax = 400;
		pPlayer->iMP = 200;
		pPlayer->iMPMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(pPlayer->strJobName, "마법사");
		pPlayer->iAttackMin = 15;
		pPlayer->iAttackMax = 20;
		pPlayer->iArmorMin = 5;
		pPlayer->iArmorMax = 10;
		pPlayer->iHP = 300;
		pPlayer->iHPMax = 300;
		pPlayer->iMP = 300;
		pPlayer->iMPMax = 300;
		break;
	}
}

_tagMonster CreateMonster(const char* pName, int iAttackMin, int iAttackMax, int iArmorMin, int iArmorMax,
	int iHP, int iMP, int iLevel, int iExp, int iGoldMin, int iGoldMax)
{
	_tagMonster tMonster = {};

	strcpy_s(tMonster.strName, pName);
	tMonster.iAttackMin = iAttackMin;
	tMonster.iAttackMax = iAttackMax;
	tMonster.iArmorMin = iArmorMin;
	tMonster.iArmorMax = iArmorMax;
	tMonster.iHP = iHP;
	tMonster.iHPMax = iHP;
	tMonster.iMP = iMP;
	tMonster.iMPMax = iMP;
	tMonster.iLevel = iLevel;
	tMonster.iGetExp = iExp;
	tMonster.iGetGoldMin = iGoldMin;
	tMonster.iGetGoldMax = iGoldMax;

	return tMonster;
}

void SetMonster(_tagMonster* pMonsterArr)
{
	pMonsterArr[0] = CreateMonster("고블린", 20, 30, 2, 5, 100, 10, 1, 1000, 500, 1500);
	pMonsterArr[1] = CreateMonster("트롤", 80, 130, 60, 90, 2000, 100, 5, 7000, 6000, 8000);
	pMonsterArr[2] = CreateMonster("드래곤", 250, 500, 200, 400, 30000, 20000, 10, 30000, 20000, 50000);
}

void OutputBattleTag(int iMenu)
{
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
}

void OutputPlayer(_tagPlayer* pPlayer)
{
	// 플레이어 정보를 출력한다.
	cout << "=================== Player ===================" << endl;
	cout << "이름 : " << pPlayer->strName << "\t\t직업 : "
		<< pPlayer->strJobName << endl;
	cout << "레벨 : " << pPlayer->iLevel << "\t\t경험치 : "
		<< pPlayer->iExp << " / " << g_iLevelUpExp[pPlayer->iLevel - 1] << endl;

	// 무기를 장착하고 있을경우 공격력에 무기공격력을 추가하여 출력한다.
	if (pPlayer->bEquip[EQ_WEAPON] == true)
	{
		cout << "공격력 : " << pPlayer->iAttackMin << "+" << pPlayer->tEquip[EQ_WEAPON].iMin
			<< " ~ " << pPlayer->iAttackMax << "+" << pPlayer->tEquip[EQ_WEAPON].iMax;
	}
	else
	{
		cout << "공격력 : " << pPlayer->iAttackMin << " ~ " << pPlayer->iAttackMax;
	}

	// 방어구를 장착하고 있을때
	if (pPlayer->bEquip[EQ_ARMOR] == true)
	{
		cout << "\t방어력 : " << pPlayer->iArmorMin << "+" << pPlayer->tEquip[EQ_ARMOR].iMin
			<< " ~ " << pPlayer->iArmorMax << "+" << pPlayer->tEquip[EQ_ARMOR].iMax << endl;
	}
	else
	{
		cout << "\t방어력 : " << pPlayer->iArmorMin << " ~ " << pPlayer->iArmorMax << endl;
	}

	cout << "체력 : " << pPlayer->iHP << " / " << pPlayer->iHPMax
		<< "\t마나 : " << pPlayer->iMP << " / " << pPlayer->iMPMax << endl;

	if (pPlayer->bEquip[EQ_WEAPON])
		cout << "장착무기 : " << pPlayer->tEquip[EQ_WEAPON].strName;
	else
		cout << "장착무기 : 없음";

	if (pPlayer->bEquip[EQ_ARMOR])
		cout << "\t\t장착방어구 : " << pPlayer->tEquip[EQ_ARMOR].strName << endl;
	else
		cout << "\t\t장착방어구 : 없음" << endl;

	cout << "보유골드 : " << pPlayer->tInventory.iGold << "Gold" << endl << endl;
}

void OutputMonster(_tagMonster* pMonster)
{
	// 몬스터 정보 출력
	cout << "================== Monster ===================" << endl;
	cout << "이름 : " << pMonster->strName << "\t\t레벨 : "
		<< pMonster->iLevel << endl;
	cout << "공겨격 : " << pMonster->iAttackMin << " ~ " << pMonster->iArmorMax
		<< "\t\t방어력 : " << pMonster->iArmorMin << " ~ " << pMonster->iArmorMax << endl;
	cout << "체력 : " << pMonster->iHP << " / " << pMonster->iHPMax
		<< "\t마나 : " << pMonster->iMP << " / " << pMonster->iMPMax << endl;
	cout << "획득경험치 : " << pMonster->iGetExp << "\t획득골드 : "
		<< pMonster->iGetGoldMin << " ~ " << pMonster->iGetGoldMax << endl << endl;
}

int OutputBattleMenu()
{
	cout << "1. 공격" << endl;
	cout << "2. 도망가기" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iMenu = InputInt();

	if (iMenu == INT_MAX || iMenu <= BATTLE_NONE || iMenu > BATTLE_BACK)
		return BATTLE_NONE;

	return iMenu;
}

void Battle(_tagPlayer* pPlayer, _tagMonster* pMonster)
{
	int iAttackMin = pPlayer->iAttackMin;
	int iAttackMax = pPlayer->iAttackMax;

	if (pPlayer->bEquip[EQ_WEAPON])
	{
		iAttackMin += pPlayer->tEquip[EQ_WEAPON].iMin;
		iAttackMax += pPlayer->tEquip[EQ_WEAPON].iMax;
	}

	int iAttack = rand() % (iAttackMax - iAttackMin + 1) + iAttackMin;
	int iArmor = rand() % (pMonster->iArmorMax - pMonster->iArmorMin + 1)
		+ pMonster->iArmorMin;

	int iDamage = iAttack - iArmor;
	// 삼항연산자 : 조건식 ? true일때값 : false일때값;
	iDamage = iDamage < 1 ? 1 : iDamage;

	// 몬스터 HP를 감소시킨다.
	pMonster->iHP -= iDamage;

	cout << pPlayer->strName << "가 " << pMonster->strName << "에게 "
		<< iDamage << "만큼 피해를 입혔습니다." << endl;

	// 몬스터가 죽었을 경우를 처리한다.
	if (pMonster->iHP <= 0)
	{
		cout << pMonster->strName << "가 사망했습니다." << endl;

		pPlayer->iExp += pMonster->iGetExp;
		int iGold =
			rand() % (pMonster->iGetGoldMax - pMonster->iGetGoldMin + 1)
			+ pMonster->iGetGoldMin;
		pPlayer->tInventory.iGold += iGold;

		cout << pMonster->iGetExp << "경험치를 획득하였습니다." << endl;
		cout << iGold << "Gold를 획득하였습니다." << endl;

		pMonster->iHP = pMonster->iHPMax;
		pMonster->iMP = pMonster->iMPMax;

		// 레벨업을 했는지 체크해본다.
		if (pPlayer->iExp >= g_iLevelUpExp[pPlayer->iLevel - 1])
		{
			// 플레이어 경험치를 레벨업에 필요한 경험치만큼 차감한다.
			pPlayer->iExp -= g_iLevelUpExp[pPlayer->iLevel - 1];

			// 레벨을 증가시킨다.
			pPlayer->iLevel++;

			cout << "레벨업 하였습니다." << endl;

			// 능력치를 상승시킨다.
			// 직업인덱스를 구한다.
			int iJobIndex = pPlayer->eJob - 1;
			int iAttackUp = rand() % (g_tLvUpTable[iJobIndex].iAttackMax -
				g_tLvUpTable[iJobIndex].iAttackMin + 1) + g_tLvUpTable[iJobIndex].iAttackMin;
			int iArmorUp = rand() % (g_tLvUpTable[iJobIndex].iArmorMax -
				g_tLvUpTable[iJobIndex].iArmorMin + 1) + g_tLvUpTable[iJobIndex].iArmorMin;
			int iHPUP = rand() % (g_tLvUpTable[iJobIndex].iHPMax -
				g_tLvUpTable[iJobIndex].iHPMin + 1) + g_tLvUpTable[iJobIndex].iHPMin;
			int iMPUP = rand() % (g_tLvUpTable[iJobIndex].iMPMax -
				g_tLvUpTable[iJobIndex].iMPMin + 1) + g_tLvUpTable[iJobIndex].iMPMin;

			pPlayer->iAttackMin += g_tLvUpTable[iJobIndex].iAttackMin;
			pPlayer->iAttackMax += g_tLvUpTable[iJobIndex].iAttackMax;
			pPlayer->iArmorMin += g_tLvUpTable[iJobIndex].iArmorMin;
			pPlayer->iArmorMax += g_tLvUpTable[iJobIndex].iArmorMax;
			pPlayer->iHPMax += iHPUP;
			pPlayer->iMPMax += iMPUP;

			// 체력과 마나를 회복시켜준다.
			pPlayer->iHP = pPlayer->iHPMax;
			pPlayer->iMP = pPlayer->iMPMax;
		}

		return;
	}

	// 몬스터가 살아있다면 플레이어를 공격한다.
	iAttack = rand() % (pMonster->iAttackMax - pMonster->iAttackMin + 1)
		+ pMonster->iAttackMin;

	int iArmorMin = pPlayer->iArmorMin;
	int iArmorMax = pPlayer->iArmorMax;

	if (pPlayer->bEquip[EQ_ARMOR])
	{
		iArmorMin += pPlayer->tEquip[EQ_ARMOR].iMin;
		iArmorMax += pPlayer->tEquip[EQ_ARMOR].iMax;
	}

	iArmor = rand() % (iArmorMax - iArmorMin + 1) + iArmorMin;

	iDamage = iAttack - iArmor;
	iDamage = iDamage < 1 ? 1 : iDamage;

	// 플레이어의 HP를 감소시킨다.
	pPlayer->iHP -= iDamage;

	cout << pMonster->strName << "가 " << pPlayer->strName << "에게 "
		<< iDamage << "만큼 피해를 입혔습니다." << endl;

	// 플레이어가 죽었을경우
	if (pPlayer->iHP <= 0)
	{
		cout << pPlayer->strName << "플레이어가 사망하였습니다." << endl;

		int iExp = pPlayer->iExp * 0.1f;
		int iGold = pPlayer->tInventory.iGold * 0.1f;

		pPlayer->iExp -= iExp;
		pPlayer->tInventory.iGold -= iGold;

		cout << iExp << "경험치를 잃었습니다." << endl;
		cout << iGold << "Gold를 잃었습니다." << endl;

		pPlayer->iHP = pPlayer->iHPMax;
		pPlayer->iMP = pPlayer->iMPMax;
	}
}

void RunBattle(_tagPlayer* pPlayer, _tagMonster* pMonsterArr, int iMenu)
{
	_tagMonster tMonster = pMonsterArr[iMenu - 1];

	while (true)
	{
		system("cls");
		OutputBattleTag(iMenu);

		// 플레이어 출력
		OutputPlayer(pPlayer);

		// 몬스터 출력
		OutputMonster(&tMonster);

		switch (OutputBattleMenu())
		{
		case BATTLE_ATTACK:
			Battle(pPlayer, &tMonster);
			system("pause");
			break;
		case BATTLE_BACK:
			return;
		}
	}
}

int OutputMapMenu()
{
	system("cls");
	cout << "********************* 맵 *********************" << endl;
	cout << "1, 쉬움" << endl;
	cout << "2, 보통" << endl;
	cout << "3, 어려움" << endl;
	cout << "4, 뒤로가기" << endl;
	cout << "맵을 선택하세요 : ";
	int iMenu = InputInt();

	if (iMenu == INT_MAX || iMenu <= MT_NONE || iMenu > MT_BACK)
		return MT_NONE;

	return iMenu;
}

// 맵에 관련된 동작을 처리한다.
void RunMap(_tagPlayer* pPlayer, _tagMonster* pMonsterArr)
{
	bool	bLoop = true;

	while (bLoop)
	{
		int iMenu = OutputMapMenu();

		if (iMenu == MT_BACK)
			return;

		// 전투를 시작한다.
		RunBattle(pPlayer, pMonsterArr, iMenu);
	}
}

_tagLevelUpStatus CreateLvUpStatus(int iAttackMin, int iAttackMax, int iArmorMin, int iArmorMax,
	int iHPMin, int iHPMax, int iMPMin, int iMPMax)
{
	_tagLevelUpStatus tStatus = {};

	tStatus.iAttackMin = iAttackMin;
	tStatus.iAttackMax = iAttackMax;
	tStatus.iArmorMin = iArmorMin;
	tStatus.iArmorMax = iArmorMax;
	tStatus.iHPMin = iHPMin;
	tStatus.iHPMax = iHPMax;
	tStatus.iMPMin = iMPMin;
	tStatus.iMPMax = iMPMax;

	return tStatus;
}

int OutputStoreMenu()
{
	system("cls");
	cout << "******************** 상점 ********************" << endl;
	cout << "1. 무기상점" << endl;
	cout << "2. 방어구상점" << endl;
	cout << "3. 뒤로가기" << endl;
	cout << "상점을 선택하세요 : ";
	int iMenu = InputInt();
	
	if (iMenu <= SM_NONE || iMenu > 3)
		return SM_NONE;

	return iMenu;
}

int OutputStoreItemList(_tagInventory* pInventory, _tagItem* pStore, int iItemCount, int iStoreType)
{
	for (int i = 0; i < iItemCount; i++)
	{
		cout << i + 1 << ". 이름 : " << pStore[i].strName <<
			"\t종류 : " << pStore[i].strTypeName << endl;
		cout << "착용레벨 : " << pStore[i].iUseLevel << endl;
		if (iStoreType == SM_WEAPON)
		{
			cout << "공격력 : " << pStore[i].iMin << " ~ " <<
				pStore[i].iMax << endl;
		}
		else if (iStoreType == SM_ARMOR)
		{
			cout << "방어력 : " << pStore[i].iMin << " ~ " <<
				pStore[i].iMax << endl;
		}
		cout << "구매가격 : " << pStore[i].iPrice <<
			"\t판매가격 : " << pStore[i].iSell << endl;
		cout << "설명 : " << pStore[i].strDesc << endl << endl;
	}

	cout << iItemCount + 1 << ". 뒤로가기" << endl << endl;
	cout << "보유금액 : " << pInventory->iGold << "Gold" << endl;
	cout << "남은공간 : " << INVENTORY_MAX - pInventory->iItemCount << endl;
	cout << "구입할 아이템을 선택하세요 : ";
	int iMenu = InputInt();

	if (iMenu < 1 || iMenu > iItemCount + 1)
		return INT_MAX;

	return iMenu;
}

void BuyItem(_tagInventory* pInventory, _tagItem* pStore, int iItemCount, int iStoreType)
{
	while (true)
	{
		system("cls");
		switch (iStoreType)
		{
		case SM_WEAPON:
			cout << "****************** 무기상점 ******************" << endl;
			break;
		case SM_ARMOR:
			cout << "***************** 방어구상점 *****************" << endl;
			break;
		}
		int iInput = OutputStoreItemList(pInventory, pStore, iItemCount, iStoreType);

		if (iInput == INT_MAX)
		{
			cout << "잘못된 선택입니다." << endl;
			system("pause");
			continue;
		}
		else if (iInput == iItemCount + 1)
			break;

		// 상점판매 목록 인덱스를 구해준다.
		int iIndex = iInput - 1;

		// 인벤토리가 꽉 찼는지 검사한다.
		if (pInventory->iItemCount == INVENTORY_MAX)
		{
			cout << "가방이 꽉 찼습니다." << endl;
			system("pause");
			continue;
		}
		// 돈이 부족한 경우
		else if (pInventory->iGold < pStore[iIndex].iPrice)
		{
			cout << "보유금액이 부족합니다." << endl;
			system("pause");
			continue;
		}

		pInventory->tItem[pInventory->iItemCount] = pStore[iIndex];

		pInventory->iItemCount++;

		pInventory->iGold -= pStore[iIndex].iPrice;
		cout << pStore[iIndex].strName << " 아이템을 구매하였습니다." << endl;
		system("pause");
	}
}

void RunStore(_tagInventory* pInventory, _tagItem* pWeaponKnight, _tagItem* pWeaponArcher,
	_tagItem* pWeaponWizard, _tagItem* pArmor, _tagPlayer* pPlayer)
{
	while (true)
	{
		switch (OutputStoreMenu())
		{
		case SM_WEAPON:
			if (pPlayer->eJob == JOB_KNIGHT)
				BuyItem(pInventory, pWeaponKnight, STORE_WEAPON_MAX, SM_WEAPON);
			else if (pPlayer->eJob == JOB_ARCHER)
				BuyItem(pInventory, pWeaponArcher, STORE_WEAPON_MAX, SM_WEAPON);
			else if (pPlayer->eJob == JOB_WIZARD)
				BuyItem(pInventory, pWeaponWizard, STORE_WEAPON_MAX, SM_WEAPON);
			break;
		case SM_ARMOR:
			BuyItem(pInventory, pArmor, STORE_ARMOR_MAX, SM_ARMOR);
			break;
		case SM_BACK:
			return;
		}
	}
}

_tagItem CreateItem(const char* pName, ITEM_TYPE eType, int iMin, int iMax, int iPrice, int iSell, 
	const char* pDesc, int iUseLevel, _tagPlayer* pPlayer)
{
	_tagItem tItem = {};

	strcpy_s(tItem.strName, pName);
	strcpy_s(tItem.strDesc, pDesc);
	
	tItem.eType = eType;
	switch (eType)
	{
	case IT_WEAPON:
		if (pPlayer->eJob == JOB_KNIGHT)
			strcpy_s(tItem.strTypeName, "기사무기");
		else if (pPlayer->eJob == JOB_ARCHER)
			strcpy_s(tItem.strTypeName, "궁수무기");
		else if (pPlayer->eJob == JOB_WIZARD)
			strcpy_s(tItem.strTypeName, "마법사무기");
		break;
	case IT_ARMOR:
		strcpy_s(tItem.strTypeName, "방어구");
		break;
	}

	tItem.iMin = iMin;
	tItem.iMax = iMax;
	tItem.iPrice = iPrice;
	tItem.iSell = iSell;
	tItem.iUseLevel = iUseLevel;

	return tItem;
}

int OutputInventory(_tagPlayer* pPlayer)
{
	system("cls");
	cout << "******************** 가방 ********************" << endl;

	OutputPlayer(pPlayer);

	for (int i = 0; i < pPlayer->tInventory.iItemCount; i++)
	{
		cout << i + 1 << ".이름 : " << pPlayer->tInventory.tItem[i].strName <<
			"\t종류 : " << pPlayer->tInventory.tItem[i].strTypeName << endl;
		if (pPlayer->tInventory.tItem[i].eType == IT_WEAPON)
		{
			cout << "공격력 : " << pPlayer->tInventory.tItem[i].iMin <<
				" ~ " << pPlayer->tInventory.tItem[i].iMax << endl;
		}
		else if (pPlayer->tInventory.tItem[i].eType == IT_ARMOR)
		{
			cout << "방어력 : " << pPlayer->tInventory.tItem[i].iMin <<
				" ~ " << pPlayer->tInventory.tItem[i].iMax << endl;
		}
		cout << "설명 : " << pPlayer->tInventory.tItem[i].strDesc << endl << endl;
	}

	cout << pPlayer->tInventory.iItemCount + 1 << ". 뒤로가기" << endl;
	cout << "장착할 아이템을 선택하세요 : ";
	int iMenu = InputInt();

	if (iMenu < 1 || iMenu > pPlayer->tInventory.iItemCount + 1)
		return INT_MAX;

	return iMenu;
}

EQUIP ComputeEquipType(ITEM_TYPE eType)
{
	EQUIP	eq;

	switch (eType)
	{
	case IT_WEAPON:
		eq = EQ_WEAPON;
		break;
	case IT_ARMOR:
		eq = EQ_ARMOR;
		break;
	}

	return eq;
}

void RunInventory(_tagPlayer* pPlayer)
{
	while (true)
	{
		int iInput = OutputInventory(pPlayer);

		if (iInput == INT_MAX)
			continue;
		else if (iInput == pPlayer->tInventory.iItemCount + 1)
			break;

		// 아이템 인덱스를 구해준다.
		int idx = iInput - 1;

		// 제대로 선택했을 경우 해당아이템의 종류에 따라 장착 부위를 결정한다.
		EQUIP	eq = ComputeEquipType(pPlayer->tInventory.tItem[idx].eType);

		// 아이템이 장착되어 있는 경우 장착되어있는 아이템과 장착할 아이템을 교체해주어야 한다.
		// Swap 알고리즘을 활용한다.
		if (pPlayer->bEquip[eq] == true)
		{
			_tagItem	tSwap = pPlayer->tEquip[eq];
			pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[idx];
			pPlayer->tInventory.tItem[idx] = tSwap;
		}

		// 장착되어있지 않을 경우 인벤토리 아이템을 장착장으로 옮기고 인벤토리 1칸이 비워진다.
		else
		{
			pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[idx];

			for (int i = idx; i < pPlayer->tInventory.iItemCount - 1; i++)
			{
				pPlayer->tInventory.tItem[i] = pPlayer->tInventory.tItem[i + 1];
			}

			pPlayer->tInventory.iItemCount--;

			// 장착을 했기 때문에 true로 만들어준다.
			pPlayer->bEquip[eq] = true;
		}

		cout << pPlayer->tEquip[eq].strName << "아이템을 장착했습니다." << endl;

		system("pause");
	}
}

int OutputHospital()
{
	system("cls");
	cout << "******************** 병원 ********************" << endl;
	cout << "1000Gold를 지불하고 체력을 회복하겠습니까?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. 돌아가기" << endl;
	cout << "메뉴를 선택하세요 : ";
	int iMenu = InputInt();

	if (iMenu < 1 || iMenu > 2)
		return INT_MAX;

	return iMenu;
}

void RunHospital(_tagPlayer* pPlayer)
{
	while (true)
	{
		int iInput = OutputHospital();

		if (iInput == INT_MAX)
		{
			cout << "잘못된 선택입니다." << endl;
			system("pause");
			continue;
		}
		else if (iInput == 2)
			break;

		if (pPlayer->iHP == pPlayer->iHPMax && pPlayer->iMP == pPlayer->iMPMax)
		{
			cout << "체력이 모두다 차있습니다." << endl;
			system("pause");
		}
		else
		{
			cout << "체력을 회복하였습니다." << endl;
			pPlayer->iHP = pPlayer->iHPMax;
			pPlayer->iMP = pPlayer->iMPMax;
			pPlayer->tInventory.iGold -= 1000;
			cout << "남은골드 : " << pPlayer->tInventory.iGold << endl;
			system("pause");
		}
	}
}

int main()
{
	srand((unsigned int)time(0));

	// 게임을 시작할때 플레이어 정보를 설정하게 한다.
	_tagPlayer tPlayer = {};

	// 플레이어의 정보를 정의한다.
	SetPlayer(&tPlayer);

	// 몬스터를 생성한다.
	_tagMonster tMonsterArr[MT_BACK - 1] = {};

	SetMonster(tMonsterArr);

	g_tLvUpTable[JOB_KNIGHT - 1] = CreateLvUpStatus(4, 10, 8, 16, 50, 100, 10, 20);
	g_tLvUpTable[JOB_ARCHER - 1] = CreateLvUpStatus(10, 15, 5, 10, 30, 60, 30, 50);
	g_tLvUpTable[JOB_WIZARD - 1] = CreateLvUpStatus(15, 20, 3, 7, 20, 40, 50, 100);

	// 상점에서 판매할 아이템목록을 생성한다.
	_tagItem	tStoreWeaponKnight[STORE_WEAPON_MAX] = {};
	_tagItem	tStoreWeaponArcher[STORE_WEAPON_MAX] = {};
	_tagItem	tStoreWeaponWizard[STORE_WEAPON_MAX] = {};
	_tagItem	tStoreArmor[STORE_ARMOR_MAX] = {};

	// 기사무기
	tStoreWeaponKnight[0] = CreateItem("단검", IT_WEAPON, 3, 5, 700, 500,
		"수행기사가 사용하는 연습용 단검", 1, &tPlayer);
	tStoreWeaponKnight[1] = CreateItem("장검", IT_WEAPON, 20, 30, 30000, 20000,
		"정식기사가 사용하는 검", 5, &tPlayer);
	tStoreWeaponKnight[2] = CreateItem("드래곤나이프", IT_WEAPON, 100, 150, 150000, 120000,
		"드래곤을 죽이기 위해 만들어진 검", 10, &tPlayer);
	// 궁수무기
	tStoreWeaponArcher[0] = CreateItem("나무활", IT_WEAPON, 4, 6, 700, 500,
		"수행궁수가 사용하는 연습용 나무활", 1, &tPlayer);
	tStoreWeaponArcher[1] = CreateItem("탄소섬유활", IT_WEAPON, 25, 35, 30000, 20000,
		"정식궁수가 사용하는 활", 5, &tPlayer);
	tStoreWeaponArcher[2] = CreateItem("드래곤보우", IT_WEAPON, 110, 160, 150000, 120000,
		"드래곤을 죽이기 위해 만들어진 활", 10, &tPlayer);
	// 마법사무기
	tStoreWeaponWizard[0] = CreateItem("완드", IT_WEAPON, 7, 10, 700, 500,
		"수행마법사가 사용하는 연습용 완드", 1, &tPlayer);
	tStoreWeaponWizard[1] = CreateItem("스태프", IT_WEAPON, 35, 40, 30000, 20000,
		"정식마법사가 사용하는 스태프", 5, &tPlayer);
	tStoreWeaponWizard[2] = CreateItem("드래곤스태프", IT_WEAPON, 150, 200, 150000, 120000,
		"드래곤을 죽이기 위해 만들어진 스태프", 10, &tPlayer);
	// 방어구
	tStoreArmor[0] = CreateItem("기본갑옷", IT_ARMOR, 3, 5, 500, 300,
		"수행기사가 사용하는 방어구", 1, &tPlayer);
	tStoreArmor[1] = CreateItem("정식갑옷", IT_ARMOR, 20, 30, 20000, 15000,
		"정식기사가 사용하는 방어구", 5, &tPlayer);
	tStoreArmor[2] = CreateItem("드래곤아머", IT_ARMOR, 70, 100, 100000, 80000,
		"드래곤을 잡기위해 만들어진 방어구", 10, &tPlayer);

	bool bLoop = true;

	while (bLoop)
	{
		switch (OutputMainMenu())
		{
		case MM_MAP:
			RunMap(&tPlayer, tMonsterArr);  // 맵 관련 루프를 처리한다.
			break;
		case MM_STORE:
			RunStore(&tPlayer.tInventory, tStoreWeaponKnight, tStoreWeaponArcher, tStoreWeaponWizard,
				tStoreArmor, &tPlayer);
			break;
		case MM_INVENTORY:
			RunInventory(&tPlayer);
			break;
		case MM_HOSPITAL:
			RunHospital(&tPlayer);
			break;
		case MM_EXIT:
			bLoop = false;
			break;
		}
	}

	return 0;
}