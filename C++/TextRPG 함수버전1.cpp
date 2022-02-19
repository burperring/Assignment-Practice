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

	// �������� �ʿ��� ����� �����
	const int	iLevelUpExp[LEVEL_MAX] = { 4000, 10000, 20000, 35000, 50000, 70000, 100000, 150000,
	200000, 400000 };

	// JOB_END�� 4�̴�. �������� 3���̹Ƿ� -1���־� �迭�� �� �������� �����Ѵ�.
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

	// ������ �����Ҷ� �÷��̾� ������ �����ϰ� �Ѵ�.
	_tagPlayer tPlayer = {};

	// �÷��̾� �̸��� �Է¹޴´�.
	cout << "ĳ���͸� : ";
	cin.getline(tPlayer.strName, NAME_SIZE - 1);
	// -1�� �־��ִ� ������ ���ڿ� �νĿ� NULL���� �ʿ��ϱ� ������

	int iJob = iJobSelect(JOB_NONE);

	tPlayer.iLevel = 1;
	tPlayer.iExp = 0;
	tPlayer.eJob = (JOB)iJob;
	tPlayer.tInventory.iGold = 10000;
	tPlayer.tInventory.iItemCount = 0;

	switch (tPlayer.eJob)
	{
	case JOB_KNIGHT:
		strcpy_s(tPlayer.strJobName, "���");
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
		strcpy_s(tPlayer.strJobName, "�ü�");
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
		strcpy_s(tPlayer.strJobName, "������");
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

	// ���͸� �����Ѵ�.
	_tagMonster tMonsterArr[MT_BACK - 1] = {};

	// ��� ����
	strcpy_s(tMonsterArr[0].strName, "���");
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

	// Ʈ��
	strcpy_s(tMonsterArr[1].strName, "Ʈ��");
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

	// �巡��
	strcpy_s(tMonsterArr[2].strName, "�巡��");
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

	// �������� �Ǹ��� �����۸���� �����Ѵ�.
	_tagItem	tStoreWeaponKnight[STORE_WEAPON_MAX] = {};
	_tagItem	tStoreWeaponArcher[STORE_WEAPON_MAX] = {};
	_tagItem	tStoreWeaponWizard[STORE_WEAPON_MAX] = {};
	_tagItem	tStoreArmor[STORE_ARMOR_MAX] = {};

	// �� ������ ������ �������ش�."
	// ��繫��
	strcpy_s(tStoreWeaponKnight[0].strName, "�ܰ�");
	strcpy_s(tStoreWeaponKnight[0].strTypeName, "��繫��");
	strcpy_s(tStoreWeaponKnight[0].strDesc, "�����簡 ����ϴ� ������ �ܰ�");
	tStoreWeaponKnight[0].iMin = 3;
	tStoreWeaponKnight[0].iMax = 5;
	tStoreWeaponKnight[0].iPrice = 700;
	tStoreWeaponKnight[0].iSell = 500;
	tStoreWeaponKnight[0].iUseLevel = 1;
	tStoreWeaponKnight[0].eType = ITEM_TYPE(IT_WEAPON);

	strcpy_s(tStoreWeaponKnight[1].strName, "���");
	strcpy_s(tStoreWeaponKnight[1].strTypeName, "��繫��");
	strcpy_s(tStoreWeaponKnight[1].strDesc, "���ı�簡 ����ϴ� ��");
	tStoreWeaponKnight[1].iMin = 20;
	tStoreWeaponKnight[1].iMax = 30;
	tStoreWeaponKnight[1].iPrice = 30000;
	tStoreWeaponKnight[1].iSell = 20000;
	tStoreWeaponKnight[1].iUseLevel = 5;
	tStoreWeaponKnight[1].eType = ITEM_TYPE(IT_WEAPON);

	strcpy_s(tStoreWeaponKnight[2].strName, "�巡�ﳪ����");
	strcpy_s(tStoreWeaponKnight[2].strTypeName, "��繫��");
	strcpy_s(tStoreWeaponKnight[2].strDesc, "�巡���� ���̱����� ������� ��");
	tStoreWeaponKnight[2].iMin = 100;
	tStoreWeaponKnight[2].iMax = 150;
	tStoreWeaponKnight[2].iPrice = 150000;
	tStoreWeaponKnight[2].iSell = 120000;
	tStoreWeaponKnight[2].iUseLevel = 10;
	tStoreWeaponKnight[2].eType = ITEM_TYPE(IT_WEAPON);

	// �ü�����
	strcpy_s(tStoreWeaponArcher[0].strName, "����Ȱ");
	strcpy_s(tStoreWeaponArcher[0].strTypeName, "�ü�����");
	strcpy_s(tStoreWeaponArcher[0].strDesc, "����ü��� ����ϴ� ������ Ȱ");
	tStoreWeaponArcher[0].iMin = 4;
	tStoreWeaponArcher[0].iMax = 6;
	tStoreWeaponArcher[0].iPrice = 700;
	tStoreWeaponArcher[0].iSell = 500;
	tStoreWeaponArcher[0].iUseLevel = 1;
	tStoreWeaponArcher[0].eType = ITEM_TYPE(IT_WEAPON);

	strcpy_s(tStoreWeaponArcher[1].strName, "ź�Ҽ���Ȱ");
	strcpy_s(tStoreWeaponArcher[1].strTypeName, "�ü�����");
	strcpy_s(tStoreWeaponArcher[1].strDesc, "���ıü��� ����ϴ� Ȱ");
	tStoreWeaponArcher[1].iMin = 25;
	tStoreWeaponArcher[1].iMax = 35;
	tStoreWeaponArcher[1].iPrice = 30000;
	tStoreWeaponArcher[1].iSell = 20000;
	tStoreWeaponArcher[1].iUseLevel = 5;
	tStoreWeaponArcher[1].eType = ITEM_TYPE(IT_WEAPON);

	strcpy_s(tStoreWeaponArcher[2].strName, "�巡�ﺸ��");
	strcpy_s(tStoreWeaponArcher[2].strTypeName, "�ü�����");
	strcpy_s(tStoreWeaponArcher[2].strDesc, "�巡���� ������� ����ϴ� Ȱ");
	tStoreWeaponArcher[2].iMin = 110;
	tStoreWeaponArcher[2].iMax = 160;
	tStoreWeaponArcher[2].iPrice = 150000;
	tStoreWeaponArcher[2].iSell = 120000;
	tStoreWeaponArcher[2].iUseLevel = 10;
	tStoreWeaponArcher[2].eType = ITEM_TYPE(IT_WEAPON);

	// �����繫��
	strcpy_s(tStoreWeaponWizard[0].strName, "�ϵ�");
	strcpy_s(tStoreWeaponWizard[0].strTypeName, "�����繫��");
	strcpy_s(tStoreWeaponWizard[0].strDesc, "���ึ���簡 ����ϴ� ������ �ϵ�");
	tStoreWeaponWizard[0].iMin = 7;
	tStoreWeaponWizard[0].iMax = 10;
	tStoreWeaponWizard[0].iPrice = 700;
	tStoreWeaponWizard[0].iSell = 500;
	tStoreWeaponWizard[0].iUseLevel = 1;
	tStoreWeaponWizard[0].eType = ITEM_TYPE(IT_WEAPON);

	strcpy_s(tStoreWeaponWizard[1].strName, "������");
	strcpy_s(tStoreWeaponWizard[1].strTypeName, "�����繫��");
	strcpy_s(tStoreWeaponWizard[1].strDesc, "���ĸ����簡 ����ϴ� ������");
	tStoreWeaponWizard[1].iMin = 35;
	tStoreWeaponWizard[1].iMax = 40;
	tStoreWeaponWizard[1].iPrice = 30000;
	tStoreWeaponWizard[1].iSell = 20000;
	tStoreWeaponWizard[1].iUseLevel = 5;
	tStoreWeaponWizard[1].eType = ITEM_TYPE(IT_WEAPON);

	strcpy_s(tStoreWeaponWizard[2].strName, "�巡�ｺ����");
	strcpy_s(tStoreWeaponWizard[2].strTypeName, "�����繫��");
	strcpy_s(tStoreWeaponWizard[2].strDesc, "�巡���� ������� ����ϴ� ������");
	tStoreWeaponWizard[2].iMin = 150;
	tStoreWeaponWizard[2].iMax = 200;
	tStoreWeaponWizard[2].iPrice = 150000;
	tStoreWeaponWizard[2].iSell = 120000;
	tStoreWeaponWizard[2].iUseLevel = 10;
	tStoreWeaponWizard[2].eType = ITEM_TYPE(IT_WEAPON);

	// ��
	strcpy_s(tStoreArmor[0].strName, "�⺻����");
	strcpy_s(tStoreArmor[0].strTypeName, "��");
	strcpy_s(tStoreArmor[0].strDesc, "�����簡 ����ϴ� ��");
	tStoreArmor[0].iMin = 3;
	tStoreArmor[0].iMax = 5;
	tStoreArmor[0].iPrice = 500;
	tStoreArmor[0].iSell = 300;
	tStoreArmor[0].iUseLevel = 1;
	tStoreArmor[0].eType = ITEM_TYPE(IT_ARMOR);

	strcpy_s(tStoreArmor[1].strName, "���İ���");
	strcpy_s(tStoreArmor[1].strTypeName, "��");
	strcpy_s(tStoreArmor[1].strDesc, "���ı�簡 ����ϴ� ��");
	tStoreArmor[1].iMin = 20;
	tStoreArmor[1].iMax = 30;
	tStoreArmor[1].iPrice = 20000;
	tStoreArmor[1].iSell = 15000;
	tStoreArmor[1].iUseLevel = 5;
	tStoreArmor[1].eType = ITEM_TYPE(IT_ARMOR);

	strcpy_s(tStoreArmor[2].strName, "�巡��Ƹ�");
	strcpy_s(tStoreArmor[2].strTypeName, "��");
	strcpy_s(tStoreArmor[2].strDesc, "�巡���� ������� ����ϴ� ��");
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

				// �� if���� ���� break�� �ʸ޴��� �����ֱ� ���� while���� ���������Ƿ�
				// �� while���� ������.
				if (iMenu == MT_BACK)
					break;

				// ������ �޴����� -1�� ���ָ� ���� �迭�� �ε����� �ȴ�.
				// �׷��� �ؼ� �ش� ���� ���͸� �������ش�.
				_tagMonster tMonster = tMonsterArr[iMenu - 1];

				while (true)
				{
					system("cls");
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

					// �÷��̾� ������ ����Ѵ�.
					cout << "=================== Player ===================" << endl;
					OutputPlayer(tPlayer, iLevelUpExp);
					cout << endl;

					// ���� ���� ���
					cout << "================== Monster ===================" << endl;
					OutputMonster(tMonster);
					cout << endl;

					cout << "1. ����" << endl;
					cout << "2. ��������" << endl;
					cout << "�޴��� �����ϼ��� : ";
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
						// ���׿����� : ���ǽ� ? true�϶��� : false�϶���;
						iDamage = iDamage < 1 ? 1 : iDamage;

						// ���� HP�� ���ҽ�Ų��.
						tMonster.iHP -= iDamage;

						cout << tPlayer.strName << "�� " << tMonster.strName << "���� "
							<< iDamage << "��ŭ ���ظ� �������ϴ�." << endl;

						// ���Ͱ� �׾��� ��츦 ó���Ѵ�.
						if (tMonster.iHP <= 0)
						{
							cout << tMonster.strName << "�� ����߽��ϴ�." << endl;

							tPlayer.iExp += tMonster.iGetExp;
							int iGold =
								rand() % (tMonster.iGetGoldMax - tMonster.iGetGoldMin + 1)
								+ tMonster.iGetGoldMin;
							tPlayer.tInventory.iGold += iGold;

							cout << tMonster.iGetExp << "����ġ�� ȹ���Ͽ����ϴ�." << endl;
							cout << iGold << "Gold�� ȹ���Ͽ����ϴ�." << endl;

							tMonster.iHP = tMonster.iHPMax;
							tMonster.iMP = tMonster.iMPMax;

							// �������� �ߴ��� üũ�غ���.
							if (tPlayer.iExp >= iLevelUpExp[tPlayer.iLevel - 1])
							{
								// �÷��̾� ����ġ�� �������� �ʿ��� ����ġ��ŭ �����Ѵ�.
								tPlayer.iExp -= iLevelUpExp[tPlayer.iLevel - 1];

								// ������ ������Ų��.
								tPlayer.iLevel++;

								cout << "������ �Ͽ����ϴ�." << endl;

								// �ɷ�ġ�� ��½�Ų��.
								// �����ε����� ���Ѵ�.
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

								// ü�°� ������ ȸ�������ش�.
								tPlayer.iHP = tPlayer.iHPMax;
								tPlayer.iMP = tPlayer.iMPMax;
							}

							system("pause");
							break;
						}

						// ���Ͱ� ����ִٸ� �÷��̾ �����Ѵ�.
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

						// �÷��̾��� HP�� ���ҽ�Ų��.
						tPlayer.iHP -= iDamage;

						cout << tMonster.strName << "�� " << tPlayer.strName << "���� "
							<< iDamage << "��ŭ ���ظ� �������ϴ�." << endl;

						// �÷��̾ �׾������
						if (tPlayer.iHP <= 0)
						{
							cout << tPlayer.strName << "�÷��̾ ����Ͽ����ϴ�." << endl;

							int iExp = tPlayer.iExp * 0.1f;
							int iGold = tPlayer.tInventory.iGold * 0.1f;

							tPlayer.iExp -= iExp;
							tPlayer.tInventory.iGold -= iGold;

							cout << iExp << "����ġ�� �Ҿ����ϴ�." << endl;
							cout << iGold << "Gold�� �Ҿ����ϴ�." << endl;

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
						// �ǸŸ���� �����ش�.
						OutputWeaponStore(tPlayer, tStoreWeaponKnight, 
							tStoreWeaponArcher, tStoreWeaponWizard);

						cout << STORE_WEAPON_MAX + 1 << ". �ڷΰ���" << endl << endl;
						cout << "�����ݾ� : " << tPlayer.tInventory.iGold << "Gold" << endl;
						cout << "�������� : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
						cout << "������ �������� �����ϼ��� : ";
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
							cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
							system("pause");
							continue;
						}

						// �����Ǹ� ��� �ε����� �����ش�.
						int iWeaponIndex = iMenu - 1;

						// �κ��丮�� �� á���� �˻��Ѵ�.
						if (tPlayer.tInventory.iItemCount == INVENTORY_MAX)
						{
							cout << "������ �� á���ϴ�." << endl;
							system("pause");
							continue;
						}
						// ���� ������ ���
						else if (tPlayer.tInventory.iGold < tStoreWeaponKnight[iWeaponIndex].iPrice ||
							tPlayer.tInventory.iGold < tStoreWeaponArcher[iWeaponIndex].iPrice ||
							tPlayer.tInventory.iGold < tStoreWeaponWizard[iWeaponIndex].iPrice)
						{
							cout << "�����ݾ��� �����մϴ�." << endl;
							system("pause");
							continue;
						}

						// ó������ iItemCount�� �ϳ��� �߰��Ǿ����� �ʱ� ������ 0���� �ʱ�ȭ �Ǿ�
						// �����Ƿ� 0�� �ε����� ������ �������� �߰��ϰ� �ȴ�. �׸��� ī��Ʈ�� 1��
						// �ȴ�. �������� �߰��Ҷ��� 1�� �ε����� �߰��ϰ� �ȴ�.
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

						// ��带 �����Ѵ�.
						if (tPlayer.eJob == JOB_KNIGHT)
						{
							tPlayer.tInventory.iGold -= tStoreWeaponKnight[iWeaponIndex].iPrice;
							cout << tStoreWeaponKnight[iWeaponIndex].strName
								<< " �������� �����Ͽ����ϴ�." << endl;
							system("pause");
						}
						else if (tPlayer.eJob == JOB_ARCHER)
						{
							tPlayer.tInventory.iGold -= tStoreWeaponArcher[iWeaponIndex].iPrice;
							cout << tStoreWeaponArcher[iWeaponIndex].strName
								<< " �������� �����Ͽ����ϴ�." << endl;
							system("pause");
						}
						else if (tPlayer.eJob == JOB_WIZARD)
						{
							tPlayer.tInventory.iGold -= tStoreWeaponWizard[iWeaponIndex].iPrice;
							cout << tStoreWeaponWizard[iWeaponIndex].strName
								<< " �������� �����Ͽ����ϴ�." << endl;
							system("pause");
						}

					}
					break;
				case SM_ARMOR:
					while (true)
					{
						system("cls");
						OutputArmorStore(tPlayer, tStoreArmor);

						cout << STORE_ARMOR_MAX + 1 << ". �ڷΰ���" << endl << endl;
						cout << "�����ݾ� : " << tPlayer.tInventory.iGold << "Gold" << endl;
						cout << "�������� : " << INVENTORY_MAX - tPlayer.tInventory.iItemCount << endl;
						cout << "������ �������� �����ϼ��� : ";
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
							cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
							system("pause");
							continue;
						}

						// �����Ǹ� ��� �ε����� �����ش�.
						int iAmorIndex = iMenu - 1;

						// �κ��丮�� �� á���� �˻��Ѵ�.
						if (tPlayer.tInventory.iItemCount == INVENTORY_MAX)
						{
							cout << "������ �� á���ϴ�." << endl;
							system("pause");
							continue;
						}
						// ���� ������ ���
						else if (tPlayer.tInventory.iGold < tStoreArmor[iAmorIndex].iPrice)
						{
							cout << "�����ݾ��� �����մϴ�." << endl;
							system("pause");
							continue;
						}

						tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount]
							= tStoreArmor[iAmorIndex];

						tPlayer.tInventory.iItemCount++;

						tPlayer.tInventory.iGold -= tStoreArmor[iAmorIndex].iPrice;
						cout << tStoreArmor[iAmorIndex].strName << " �������� �����Ͽ����ϴ�." << endl;
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
				cout << "******************** ���� ********************" << endl;
				cout << "=================== Player ===================" << endl;
				OutputPlayer(tPlayer, iLevelUpExp);
				cout << "==============================================" << endl << endl;

				OutputInventory(tPlayer);

				cout << tPlayer.tInventory.iItemCount + 1 << ". �ڷΰ���" << endl;
				cout << "������ �������� �����ϼ��� : ";
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
					cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
					system("pause");
					continue;
				}

				// ������ �ε����� �����ش�.
				int idx = iMenu - 1;

				// ����� �������� ��� �ش�������� ������ ���� ���� ������ �����Ѵ�.
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

				// �������� �����Ǿ� �ִ� ��� �����Ǿ��ִ� �����۰� ������ �������� ��ü���־�� �Ѵ�.
				// Swap �˰����� Ȱ���Ѵ�.
				if (tPlayer.bEquip[eq] == true)
				{
					_tagItem	tSwap = tPlayer.tEquip[eq];
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];
					tPlayer.tInventory.tItem[idx] = tSwap;
				}

				// �����Ǿ����� ���� ��� �κ��丮 �������� ���������� �ű�� �κ��丮 1ĭ�� �������.
				else
				{
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];

					for (int i = idx; i < tPlayer.tInventory.iItemCount - 1; i++)
					{
						tPlayer.tInventory.tItem[i] = tPlayer.tInventory.tItem[i + 1];
					}

					tPlayer.tInventory.iItemCount--;

					// ������ �߱� ������ true�� ������ش�.
					tPlayer.bEquip[eq] = true;
				}

				cout << tPlayer.tEquip[eq].strName << "�������� �����߽��ϴ�." << endl;

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
						cout << "ü���� ��δ� ���ֽ��ϴ�." << endl;
						system("pause");
					}
					else
					{
						cout << "ü���� ȸ���Ͽ����ϴ�." << endl;
						tPlayer.iHP = tPlayer.iHPMax;
						tPlayer.iMP = tPlayer.iMPMax;
						tPlayer.tInventory.iGold -= 1000;
						cout << "������� : " << tPlayer.tInventory.iGold << endl;
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
		cout << "1. ���" << endl;
		cout << "2. �ü�" << endl;
		cout << "3. ������" << endl;
		cout << "���ϴ� ������ �����ϼ��� : ";
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
		cout << "******************** �κ� ********************" << endl;
		cout << "1. ��" << endl;
		cout << "2. ����" << endl;
		cout << "3. ����" << endl;
		cout << "4. ü��ȸ��" << endl;
		cout << "5. ����" << endl;
		cout << "�޴��� �����ϼ��� : ";
		cin >> iMenu;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (iMenu < MM_NONE || iMenu > MM_EXIT)
		{
			cout << "�߸� �����ϼ̽��ϴ�." << endl;
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

		cout << "********************* �� *********************" << endl;
		cout << "1, ����" << endl;
		cout << "2, ����" << endl;
		cout << "3, �����" << endl;
		cout << "4, �ڷΰ���" << endl;
		cout << "���� �����ϼ��� : ";
		cin >> iMenu;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (iMenu < MT_NONE || iMenu > MT_BACK)
		{
			cout << "�߸� �����ϼ̽��ϴ�." << endl;
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
	cout << "�̸� : " << tPlayer.strName << "\t\t���� : "
		<< tPlayer.strJobName << endl;
	cout << "���� : " << tPlayer.iLevel << "\t\t����ġ : "
		<< tPlayer.iExp << " / " << iLevelUpExp[tPlayer.iLevel-1] << endl;

	// ���⸦ �����ϰ� ������� ���ݷ¿� ������ݷ��� �߰��Ͽ� ����Ѵ�.
	if (tPlayer.bEquip[EQ_WEAPON] == true)
	{
		cout << "���ݷ� : " << tPlayer.iAttackMin << "+" << tPlayer.tEquip[EQ_WEAPON].iMin
			<< " ~ " << tPlayer.iAttackMax << "+" << tPlayer.tEquip[EQ_WEAPON].iMax;
	}
	else
	{
		cout << "���ݷ� : " << tPlayer.iAttackMin << " ~ " << tPlayer.iAttackMax;
	}

	// ���� �����ϰ� ������
	if (tPlayer.bEquip[EQ_ARMOR] == true)
	{
		cout << "\t���� : " << tPlayer.iArmorMin << "+" << tPlayer.tEquip[EQ_ARMOR].iMin
			<< " ~ " << tPlayer.iArmorMax << "+" << tPlayer.tEquip[EQ_ARMOR].iMax << endl;
	}
	else
	{
		cout << "\t���� : " << tPlayer.iArmorMin << " ~ " << tPlayer.iArmorMax << endl;
	}

	cout << "ü�� : " << tPlayer.iHP << " / " << tPlayer.iHPMax
		<< "\t���� : " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;

	if (tPlayer.bEquip[EQ_WEAPON])
		cout << "�������� : " << tPlayer.tEquip[EQ_WEAPON].strName;
	else
		cout << "�������� : ����";

	if (tPlayer.bEquip[EQ_ARMOR])
		cout << "\t\t������ : " << tPlayer.tEquip[EQ_ARMOR].strName << endl;
	else
		cout << "\t\t������ : ����" << endl;

	cout << "������� : " << tPlayer.tInventory.iGold << "Gold" << endl;
}

void OutputMonster(_tagMonster tMonster)
{
	cout << "�̸� : " << tMonster.strName << "\t\t���� : "
		<< tMonster.iLevel << endl;
	cout << "���ܰ� : " << tMonster.iAttackMin << " ~ " << tMonster.iArmorMax
		<< "\t\t���� : " << tMonster.iArmorMin << " ~ " << tMonster.iArmorMax << endl;
	cout << "ü�� : " << tMonster.iHP << " / " << tMonster.iHPMax
		<< "\t���� : " << tMonster.iMP << " / " << tMonster.iMPMax << endl;
	cout << "ȹ�����ġ : " << tMonster.iGetExp << "\tȹ���� : "
		<< tMonster.iGetGoldMin << " ~ " << tMonster.iGetGoldMax << endl;
}

STORE_MENU SelectStore()
{
	int iMenu;

	while (true)
	{
		system("cls");
		cout << "******************** ���� ********************" << endl;
		cout << "1. �������" << endl;
		cout << "2. ������" << endl;
		cout << "3. �ڷΰ���" << endl;
		cout << "������ �����ϼ��� : ";
		cin >> iMenu;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (iMenu < SM_NONE || iMenu > SM_BACK)
		{
			cout << "�߸��� �����Դϴ�." << endl;
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
	cout << "****************** ������� ******************" << endl;
	if (tPlayer.eJob == JOB_KNIGHT)
	{
		for (int i = 0; i < STORE_WEAPON_MAX; i++)
		{
			cout << i + 1 << ". �̸� : " << tStoreWeaponKnight[i].strName <<
				"\t���� : " << tStoreWeaponKnight[i].strTypeName << endl;
			cout << "���뷹�� : " << tStoreWeaponKnight[i].iUseLevel << endl;
			cout << "���ݷ� : " << tStoreWeaponKnight[i].iMin << " ~ " <<
				tStoreWeaponKnight[i].iMax << endl;
			cout << "���Ű��� : " << tStoreWeaponKnight[i].iPrice <<
				"\t�ǸŰ��� : " << tStoreWeaponKnight[i].iSell << endl;
			cout << "���� : " << tStoreWeaponKnight[i].strDesc << endl << endl;
		}
	}
	else if (tPlayer.eJob == JOB_ARCHER)
	{
		for (int i = 0; i < STORE_WEAPON_MAX; i++)
		{
			cout << i + 1 << ". �̸� : " << tStoreWeaponArcher[i].strName <<
				"\t���� : " << tStoreWeaponArcher[i].strTypeName << endl;
			cout << "���뷹�� : " << tStoreWeaponArcher[i].iUseLevel << endl;
			cout << "���ݷ� : " << tStoreWeaponArcher[i].iMin << " ~ " <<
				tStoreWeaponArcher[i].iMax << endl;
			cout << "���Ű��� : " << tStoreWeaponArcher[i].iPrice <<
				"\t�ǸŰ��� : " << tStoreWeaponArcher[i].iSell << endl;
			cout << "���� : " << tStoreWeaponArcher[i].strDesc << endl << endl;
		}
	}
	else if (tPlayer.eJob == JOB_WIZARD)
	{
		for (int i = 0; i < STORE_WEAPON_MAX; i++)
		{
			cout << i + 1 << ". �̸� : " << tStoreWeaponWizard[i].strName <<
				"\t���� : " << tStoreWeaponWizard[i].strTypeName << endl;
			cout << "���뷹�� : " << tStoreWeaponWizard[i].iUseLevel << endl;
			cout << "���ݷ� : " << tStoreWeaponWizard[i].iMin << " ~ " <<
				tStoreWeaponWizard[i].iMax << endl;
			cout << "���Ű��� : " << tStoreWeaponWizard[i].iPrice <<
				"\t�ǸŰ��� : " << tStoreWeaponWizard[i].iSell << endl;
			cout << "���� : " << tStoreWeaponWizard[i].strDesc << endl << endl;
		}
	}
}

void OutputArmorStore(_tagPlayer tPlayer, _tagItem* tStoreArmor)
{
	cout << "***************** ������ *****************" << endl;
	for (int i = 0; i < STORE_ARMOR_MAX; i++)
	{
		cout << i + 1 << ". �̸� : " << tStoreArmor[i].strName <<
			"\t���� : " << tStoreArmor[i].strTypeName << endl;
		cout << "���뷹�� : " << tStoreArmor[i].iUseLevel << endl;
		cout << "���� : " << tStoreArmor[i].iMin << " ~ " <<
			tStoreArmor[i].iMax << endl;
		cout << "���Ű��� : " << tStoreArmor[i].iPrice <<
			"\t�ǸŰ��� : " << tStoreArmor[i].iSell << endl;
		cout << "���� : " << tStoreArmor[i].strDesc << endl << endl;
	}
}

void OutputInventory(_tagPlayer tPlayer)
{
	for (int i = 0; i < tPlayer.tInventory.iItemCount; i++)
	{
		cout << i + 1 << ".�̸� : " << tPlayer.tInventory.tItem[i].strName <<
			"\t���� : " << tPlayer.tInventory.tItem[i].strTypeName << endl;
		if (tPlayer.tInventory.tItem[i].eType == IT_WEAPON)
		{
			cout << "���ݷ� : " << tPlayer.tInventory.tItem[i].iMin <<
				" ~ " << tPlayer.tInventory.tItem[i].iMax << endl;
		}
		else if (tPlayer.tInventory.tItem[i].eType == IT_ARMOR)
		{
			cout << "���� : " << tPlayer.tInventory.tItem[i].iMin <<
				" ~ " << tPlayer.tInventory.tItem[i].iMax << endl;
		}
		cout << "���� : " << tPlayer.tInventory.tItem[i].strDesc << endl << endl;
	}
}

int SelectHospital()
{
	int iMenu;
	while (true)
	{
		system("cls");
		cout << "******************** ���� ********************" << endl;
		cout << "1000Gold�� �����ϰ� ü���� ȸ���ϰڽ��ϱ�?" << endl;
		cout << "1. Yes" << endl;
		cout << "2. ���ư���" << endl;
		cout << "�޴��� �����ϼ��� : ";
		cin >> iMenu;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (iMenu > 2 || iMenu < 1)
		{
			cout << "�߸��� �Է��Դϴ�." << endl;
			system("pause");
			continue;
		}
		else
			break;
	}

	return iMenu;
}