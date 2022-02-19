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

// �������� �ʿ��� ����� �����
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
		return INT_MAX; // INT_MAX�� �ԷµǸ� �߸��� �Է��̶�� �ǹ̺ο�
	}

	return iInput;
}

int OutputMainMenu()
{
	system("cls");
	cout << "******************** �κ� ********************" << endl;
	cout << "1. ��" << endl;
	cout << "2. ����" << endl;
	cout << "3. ����" << endl;
	cout << "4. ü��ȸ��" << endl;
	cout << "5. ����" << endl;
	cout << "�޴��� �����ϼ��� : ";
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
		cout << "1. ���" << endl;
		cout << "2. �ü�" << endl;
		cout << "3. ������" << endl;
		cout << "���ϴ� ������ �����ϼ��� : ";
		iJob = InputInt();

		if (iJob <= JOB_NONE || iJob >= JOB_END)
			iJob = JOB_NONE;
	}

	return iJob;
}

void SetPlayer(_tagPlayer* pPlayer)
{
	// �÷��̾� �̸��� �Է¹޴´�.
	cout << "�̸� : ";
	cin.getline(pPlayer->strName, NAME_SIZE - 1);

	pPlayer->eJob = (JOB)SelectJob();
	pPlayer->iLevel = 1;
	pPlayer->iExp = 0;
	pPlayer->tInventory.iGold = 10000;

	switch (pPlayer->eJob)
	{
	case JOB_KNIGHT:
		strcpy_s(pPlayer->strJobName, "���");
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
		strcpy_s(pPlayer->strJobName, "�ü�");
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
		strcpy_s(pPlayer->strJobName, "������");
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
	pMonsterArr[0] = CreateMonster("���", 20, 30, 2, 5, 100, 10, 1, 1000, 500, 1500);
	pMonsterArr[1] = CreateMonster("Ʈ��", 80, 130, 60, 90, 2000, 100, 5, 7000, 6000, 8000);
	pMonsterArr[2] = CreateMonster("�巡��", 250, 500, 200, 400, 30000, 20000, 10, 30000, 20000, 50000);
}

void OutputBattleTag(int iMenu)
{
	switch (iMenu)
	{
	case MT_EASY:
		cout << "******************** ���� ********************" << endl;
		break;
	case MT_NOMAL:
		cout << "******************** ���� ********************" << endl;
		break;
	case MT_HARD:
		cout << "******************* ����� *******************" << endl;
		break;
	}
}

void OutputPlayer(_tagPlayer* pPlayer)
{
	// �÷��̾� ������ ����Ѵ�.
	cout << "=================== Player ===================" << endl;
	cout << "�̸� : " << pPlayer->strName << "\t\t���� : "
		<< pPlayer->strJobName << endl;
	cout << "���� : " << pPlayer->iLevel << "\t\t����ġ : "
		<< pPlayer->iExp << " / " << g_iLevelUpExp[pPlayer->iLevel - 1] << endl;

	// ���⸦ �����ϰ� ������� ���ݷ¿� ������ݷ��� �߰��Ͽ� ����Ѵ�.
	if (pPlayer->bEquip[EQ_WEAPON] == true)
	{
		cout << "���ݷ� : " << pPlayer->iAttackMin << "+" << pPlayer->tEquip[EQ_WEAPON].iMin
			<< " ~ " << pPlayer->iAttackMax << "+" << pPlayer->tEquip[EQ_WEAPON].iMax;
	}
	else
	{
		cout << "���ݷ� : " << pPlayer->iAttackMin << " ~ " << pPlayer->iAttackMax;
	}

	// ���� �����ϰ� ������
	if (pPlayer->bEquip[EQ_ARMOR] == true)
	{
		cout << "\t���� : " << pPlayer->iArmorMin << "+" << pPlayer->tEquip[EQ_ARMOR].iMin
			<< " ~ " << pPlayer->iArmorMax << "+" << pPlayer->tEquip[EQ_ARMOR].iMax << endl;
	}
	else
	{
		cout << "\t���� : " << pPlayer->iArmorMin << " ~ " << pPlayer->iArmorMax << endl;
	}

	cout << "ü�� : " << pPlayer->iHP << " / " << pPlayer->iHPMax
		<< "\t���� : " << pPlayer->iMP << " / " << pPlayer->iMPMax << endl;

	if (pPlayer->bEquip[EQ_WEAPON])
		cout << "�������� : " << pPlayer->tEquip[EQ_WEAPON].strName;
	else
		cout << "�������� : ����";

	if (pPlayer->bEquip[EQ_ARMOR])
		cout << "\t\t������ : " << pPlayer->tEquip[EQ_ARMOR].strName << endl;
	else
		cout << "\t\t������ : ����" << endl;

	cout << "������� : " << pPlayer->tInventory.iGold << "Gold" << endl << endl;
}

void OutputMonster(_tagMonster* pMonster)
{
	// ���� ���� ���
	cout << "================== Monster ===================" << endl;
	cout << "�̸� : " << pMonster->strName << "\t\t���� : "
		<< pMonster->iLevel << endl;
	cout << "���ܰ� : " << pMonster->iAttackMin << " ~ " << pMonster->iArmorMax
		<< "\t\t���� : " << pMonster->iArmorMin << " ~ " << pMonster->iArmorMax << endl;
	cout << "ü�� : " << pMonster->iHP << " / " << pMonster->iHPMax
		<< "\t���� : " << pMonster->iMP << " / " << pMonster->iMPMax << endl;
	cout << "ȹ�����ġ : " << pMonster->iGetExp << "\tȹ���� : "
		<< pMonster->iGetGoldMin << " ~ " << pMonster->iGetGoldMax << endl << endl;
}

int OutputBattleMenu()
{
	cout << "1. ����" << endl;
	cout << "2. ��������" << endl;
	cout << "�޴��� �����ϼ��� : ";
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
	// ���׿����� : ���ǽ� ? true�϶��� : false�϶���;
	iDamage = iDamage < 1 ? 1 : iDamage;

	// ���� HP�� ���ҽ�Ų��.
	pMonster->iHP -= iDamage;

	cout << pPlayer->strName << "�� " << pMonster->strName << "���� "
		<< iDamage << "��ŭ ���ظ� �������ϴ�." << endl;

	// ���Ͱ� �׾��� ��츦 ó���Ѵ�.
	if (pMonster->iHP <= 0)
	{
		cout << pMonster->strName << "�� ����߽��ϴ�." << endl;

		pPlayer->iExp += pMonster->iGetExp;
		int iGold =
			rand() % (pMonster->iGetGoldMax - pMonster->iGetGoldMin + 1)
			+ pMonster->iGetGoldMin;
		pPlayer->tInventory.iGold += iGold;

		cout << pMonster->iGetExp << "����ġ�� ȹ���Ͽ����ϴ�." << endl;
		cout << iGold << "Gold�� ȹ���Ͽ����ϴ�." << endl;

		pMonster->iHP = pMonster->iHPMax;
		pMonster->iMP = pMonster->iMPMax;

		// �������� �ߴ��� üũ�غ���.
		if (pPlayer->iExp >= g_iLevelUpExp[pPlayer->iLevel - 1])
		{
			// �÷��̾� ����ġ�� �������� �ʿ��� ����ġ��ŭ �����Ѵ�.
			pPlayer->iExp -= g_iLevelUpExp[pPlayer->iLevel - 1];

			// ������ ������Ų��.
			pPlayer->iLevel++;

			cout << "������ �Ͽ����ϴ�." << endl;

			// �ɷ�ġ�� ��½�Ų��.
			// �����ε����� ���Ѵ�.
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

			// ü�°� ������ ȸ�������ش�.
			pPlayer->iHP = pPlayer->iHPMax;
			pPlayer->iMP = pPlayer->iMPMax;
		}

		return;
	}

	// ���Ͱ� ����ִٸ� �÷��̾ �����Ѵ�.
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

	// �÷��̾��� HP�� ���ҽ�Ų��.
	pPlayer->iHP -= iDamage;

	cout << pMonster->strName << "�� " << pPlayer->strName << "���� "
		<< iDamage << "��ŭ ���ظ� �������ϴ�." << endl;

	// �÷��̾ �׾������
	if (pPlayer->iHP <= 0)
	{
		cout << pPlayer->strName << "�÷��̾ ����Ͽ����ϴ�." << endl;

		int iExp = pPlayer->iExp * 0.1f;
		int iGold = pPlayer->tInventory.iGold * 0.1f;

		pPlayer->iExp -= iExp;
		pPlayer->tInventory.iGold -= iGold;

		cout << iExp << "����ġ�� �Ҿ����ϴ�." << endl;
		cout << iGold << "Gold�� �Ҿ����ϴ�." << endl;

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

		// �÷��̾� ���
		OutputPlayer(pPlayer);

		// ���� ���
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
	cout << "********************* �� *********************" << endl;
	cout << "1, ����" << endl;
	cout << "2, ����" << endl;
	cout << "3, �����" << endl;
	cout << "4, �ڷΰ���" << endl;
	cout << "���� �����ϼ��� : ";
	int iMenu = InputInt();

	if (iMenu == INT_MAX || iMenu <= MT_NONE || iMenu > MT_BACK)
		return MT_NONE;

	return iMenu;
}

// �ʿ� ���õ� ������ ó���Ѵ�.
void RunMap(_tagPlayer* pPlayer, _tagMonster* pMonsterArr)
{
	bool	bLoop = true;

	while (bLoop)
	{
		int iMenu = OutputMapMenu();

		if (iMenu == MT_BACK)
			return;

		// ������ �����Ѵ�.
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
	cout << "******************** ���� ********************" << endl;
	cout << "1. �������" << endl;
	cout << "2. ������" << endl;
	cout << "3. �ڷΰ���" << endl;
	cout << "������ �����ϼ��� : ";
	int iMenu = InputInt();
	
	if (iMenu <= SM_NONE || iMenu > 3)
		return SM_NONE;

	return iMenu;
}

int OutputStoreItemList(_tagInventory* pInventory, _tagItem* pStore, int iItemCount, int iStoreType)
{
	for (int i = 0; i < iItemCount; i++)
	{
		cout << i + 1 << ". �̸� : " << pStore[i].strName <<
			"\t���� : " << pStore[i].strTypeName << endl;
		cout << "���뷹�� : " << pStore[i].iUseLevel << endl;
		if (iStoreType == SM_WEAPON)
		{
			cout << "���ݷ� : " << pStore[i].iMin << " ~ " <<
				pStore[i].iMax << endl;
		}
		else if (iStoreType == SM_ARMOR)
		{
			cout << "���� : " << pStore[i].iMin << " ~ " <<
				pStore[i].iMax << endl;
		}
		cout << "���Ű��� : " << pStore[i].iPrice <<
			"\t�ǸŰ��� : " << pStore[i].iSell << endl;
		cout << "���� : " << pStore[i].strDesc << endl << endl;
	}

	cout << iItemCount + 1 << ". �ڷΰ���" << endl << endl;
	cout << "�����ݾ� : " << pInventory->iGold << "Gold" << endl;
	cout << "�������� : " << INVENTORY_MAX - pInventory->iItemCount << endl;
	cout << "������ �������� �����ϼ��� : ";
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
			cout << "****************** ������� ******************" << endl;
			break;
		case SM_ARMOR:
			cout << "***************** ������ *****************" << endl;
			break;
		}
		int iInput = OutputStoreItemList(pInventory, pStore, iItemCount, iStoreType);

		if (iInput == INT_MAX)
		{
			cout << "�߸��� �����Դϴ�." << endl;
			system("pause");
			continue;
		}
		else if (iInput == iItemCount + 1)
			break;

		// �����Ǹ� ��� �ε����� �����ش�.
		int iIndex = iInput - 1;

		// �κ��丮�� �� á���� �˻��Ѵ�.
		if (pInventory->iItemCount == INVENTORY_MAX)
		{
			cout << "������ �� á���ϴ�." << endl;
			system("pause");
			continue;
		}
		// ���� ������ ���
		else if (pInventory->iGold < pStore[iIndex].iPrice)
		{
			cout << "�����ݾ��� �����մϴ�." << endl;
			system("pause");
			continue;
		}

		pInventory->tItem[pInventory->iItemCount] = pStore[iIndex];

		pInventory->iItemCount++;

		pInventory->iGold -= pStore[iIndex].iPrice;
		cout << pStore[iIndex].strName << " �������� �����Ͽ����ϴ�." << endl;
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
			strcpy_s(tItem.strTypeName, "��繫��");
		else if (pPlayer->eJob == JOB_ARCHER)
			strcpy_s(tItem.strTypeName, "�ü�����");
		else if (pPlayer->eJob == JOB_WIZARD)
			strcpy_s(tItem.strTypeName, "�����繫��");
		break;
	case IT_ARMOR:
		strcpy_s(tItem.strTypeName, "��");
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
	cout << "******************** ���� ********************" << endl;

	OutputPlayer(pPlayer);

	for (int i = 0; i < pPlayer->tInventory.iItemCount; i++)
	{
		cout << i + 1 << ".�̸� : " << pPlayer->tInventory.tItem[i].strName <<
			"\t���� : " << pPlayer->tInventory.tItem[i].strTypeName << endl;
		if (pPlayer->tInventory.tItem[i].eType == IT_WEAPON)
		{
			cout << "���ݷ� : " << pPlayer->tInventory.tItem[i].iMin <<
				" ~ " << pPlayer->tInventory.tItem[i].iMax << endl;
		}
		else if (pPlayer->tInventory.tItem[i].eType == IT_ARMOR)
		{
			cout << "���� : " << pPlayer->tInventory.tItem[i].iMin <<
				" ~ " << pPlayer->tInventory.tItem[i].iMax << endl;
		}
		cout << "���� : " << pPlayer->tInventory.tItem[i].strDesc << endl << endl;
	}

	cout << pPlayer->tInventory.iItemCount + 1 << ". �ڷΰ���" << endl;
	cout << "������ �������� �����ϼ��� : ";
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

		// ������ �ε����� �����ش�.
		int idx = iInput - 1;

		// ����� �������� ��� �ش�������� ������ ���� ���� ������ �����Ѵ�.
		EQUIP	eq = ComputeEquipType(pPlayer->tInventory.tItem[idx].eType);

		// �������� �����Ǿ� �ִ� ��� �����Ǿ��ִ� �����۰� ������ �������� ��ü���־�� �Ѵ�.
		// Swap �˰����� Ȱ���Ѵ�.
		if (pPlayer->bEquip[eq] == true)
		{
			_tagItem	tSwap = pPlayer->tEquip[eq];
			pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[idx];
			pPlayer->tInventory.tItem[idx] = tSwap;
		}

		// �����Ǿ����� ���� ��� �κ��丮 �������� ���������� �ű�� �κ��丮 1ĭ�� �������.
		else
		{
			pPlayer->tEquip[eq] = pPlayer->tInventory.tItem[idx];

			for (int i = idx; i < pPlayer->tInventory.iItemCount - 1; i++)
			{
				pPlayer->tInventory.tItem[i] = pPlayer->tInventory.tItem[i + 1];
			}

			pPlayer->tInventory.iItemCount--;

			// ������ �߱� ������ true�� ������ش�.
			pPlayer->bEquip[eq] = true;
		}

		cout << pPlayer->tEquip[eq].strName << "�������� �����߽��ϴ�." << endl;

		system("pause");
	}
}

int OutputHospital()
{
	system("cls");
	cout << "******************** ���� ********************" << endl;
	cout << "1000Gold�� �����ϰ� ü���� ȸ���ϰڽ��ϱ�?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. ���ư���" << endl;
	cout << "�޴��� �����ϼ��� : ";
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
			cout << "�߸��� �����Դϴ�." << endl;
			system("pause");
			continue;
		}
		else if (iInput == 2)
			break;

		if (pPlayer->iHP == pPlayer->iHPMax && pPlayer->iMP == pPlayer->iMPMax)
		{
			cout << "ü���� ��δ� ���ֽ��ϴ�." << endl;
			system("pause");
		}
		else
		{
			cout << "ü���� ȸ���Ͽ����ϴ�." << endl;
			pPlayer->iHP = pPlayer->iHPMax;
			pPlayer->iMP = pPlayer->iMPMax;
			pPlayer->tInventory.iGold -= 1000;
			cout << "������� : " << pPlayer->tInventory.iGold << endl;
			system("pause");
		}
	}
}

int main()
{
	srand((unsigned int)time(0));

	// ������ �����Ҷ� �÷��̾� ������ �����ϰ� �Ѵ�.
	_tagPlayer tPlayer = {};

	// �÷��̾��� ������ �����Ѵ�.
	SetPlayer(&tPlayer);

	// ���͸� �����Ѵ�.
	_tagMonster tMonsterArr[MT_BACK - 1] = {};

	SetMonster(tMonsterArr);

	g_tLvUpTable[JOB_KNIGHT - 1] = CreateLvUpStatus(4, 10, 8, 16, 50, 100, 10, 20);
	g_tLvUpTable[JOB_ARCHER - 1] = CreateLvUpStatus(10, 15, 5, 10, 30, 60, 30, 50);
	g_tLvUpTable[JOB_WIZARD - 1] = CreateLvUpStatus(15, 20, 3, 7, 20, 40, 50, 100);

	// �������� �Ǹ��� �����۸���� �����Ѵ�.
	_tagItem	tStoreWeaponKnight[STORE_WEAPON_MAX] = {};
	_tagItem	tStoreWeaponArcher[STORE_WEAPON_MAX] = {};
	_tagItem	tStoreWeaponWizard[STORE_WEAPON_MAX] = {};
	_tagItem	tStoreArmor[STORE_ARMOR_MAX] = {};

	// ��繫��
	tStoreWeaponKnight[0] = CreateItem("�ܰ�", IT_WEAPON, 3, 5, 700, 500,
		"�����簡 ����ϴ� ������ �ܰ�", 1, &tPlayer);
	tStoreWeaponKnight[1] = CreateItem("���", IT_WEAPON, 20, 30, 30000, 20000,
		"���ı�簡 ����ϴ� ��", 5, &tPlayer);
	tStoreWeaponKnight[2] = CreateItem("�巡�ﳪ����", IT_WEAPON, 100, 150, 150000, 120000,
		"�巡���� ���̱� ���� ������� ��", 10, &tPlayer);
	// �ü�����
	tStoreWeaponArcher[0] = CreateItem("����Ȱ", IT_WEAPON, 4, 6, 700, 500,
		"����ü��� ����ϴ� ������ ����Ȱ", 1, &tPlayer);
	tStoreWeaponArcher[1] = CreateItem("ź�Ҽ���Ȱ", IT_WEAPON, 25, 35, 30000, 20000,
		"���ıü��� ����ϴ� Ȱ", 5, &tPlayer);
	tStoreWeaponArcher[2] = CreateItem("�巡�ﺸ��", IT_WEAPON, 110, 160, 150000, 120000,
		"�巡���� ���̱� ���� ������� Ȱ", 10, &tPlayer);
	// �����繫��
	tStoreWeaponWizard[0] = CreateItem("�ϵ�", IT_WEAPON, 7, 10, 700, 500,
		"���ึ���簡 ����ϴ� ������ �ϵ�", 1, &tPlayer);
	tStoreWeaponWizard[1] = CreateItem("������", IT_WEAPON, 35, 40, 30000, 20000,
		"���ĸ����簡 ����ϴ� ������", 5, &tPlayer);
	tStoreWeaponWizard[2] = CreateItem("�巡�ｺ����", IT_WEAPON, 150, 200, 150000, 120000,
		"�巡���� ���̱� ���� ������� ������", 10, &tPlayer);
	// ��
	tStoreArmor[0] = CreateItem("�⺻����", IT_ARMOR, 3, 5, 500, 300,
		"�����簡 ����ϴ� ��", 1, &tPlayer);
	tStoreArmor[1] = CreateItem("���İ���", IT_ARMOR, 20, 30, 20000, 15000,
		"���ı�簡 ����ϴ� ��", 5, &tPlayer);
	tStoreArmor[2] = CreateItem("�巡��Ƹ�", IT_ARMOR, 70, 100, 100000, 80000,
		"�巡���� ������� ������� ��", 10, &tPlayer);

	bool bLoop = true;

	while (bLoop)
	{
		switch (OutputMainMenu())
		{
		case MM_MAP:
			RunMap(&tPlayer, tMonsterArr);  // �� ���� ������ ó���Ѵ�.
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