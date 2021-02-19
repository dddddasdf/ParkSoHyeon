#pragma once
#include "Headers.h"
#include "MapDraw.h"
#include "Weapon.h"
#include "User.h"
#include "Inventory.h"

struct Monster
{
	string MonsterName;	//�� �̸�
	int MonsterCurrentLife;	//�� ���� �����
	int MonsterMaxLife;	//�� �ִ� �����
	int MonsterAttck;	//�� ���ݷ�
	int MonsterDropGold;	//���� �ִ� ���
	int MonsterLevel;	//�� ���� ����
	int MonsterCurrentExp;	//�� ���� ����ġ
	int MonsterMaxExp;	//���� ���� ���� ���� �䱸 ����ġ
	int MonsterDropExp;	//���� �ִ� ����ġ
	int Delay;	//���Ͱ� ������ �ϱ���� �ɸ��� �ð�
};

enum OUTCOME
{
	OUTCOME_DRAW,
	OUTCOME_WIN,
	OUTCOME_LOSE	//���� ����� ���� enum
};

class Game
{
private:
	MapDraw GameMap;
	
	User Player;
	//������� ���� ���� ����

	int m_iMonsterPopulation;	//�� ��ü��
	Monster *MonsterArr;
	Weapon *WeaponPtr;
	Sword *SwordPtr;
	Bow *BowPtr;
	Dagger *DaggerPtr;
	Gun *GunPtr;
	Wand *WandPtr;
	Hammer *HammerPtr;

	//�Ʒ��� �κ� ����
	Inventory *MainInventory;
	Inventory *DaggerBag;
	Inventory *GunBag;
	Inventory *SwordBag;
	Inventory *WandBag;
	Inventory *BowBag;
	Inventory *HammerBag;
	
public:
	Game();
	void GetName(string name);
	bool LoadDefaultUserData();	//����Ʈ ���� ���� �о����, �ؽ�Ʈ�� ���������� �о�鿴�� ��� true�� ��ȯ �ƴҽ� false�� ��ȯ�ϰ� �������� ���۵��� ���ϰ� ����
	bool InitMonsterData();	//�� ���� �ʱ�ȭ. InitUserInfo()�� �Ȱ��� ��Ŀ����
	bool InitWeaponData();	//���� ���� �ʱ�ȭ. �� ���� ���̽��� ������ ���� �ٸ���
	void InitInventory();	//�κ� �ʱ�ȭ
	bool LoadUserData(int DataNumber);	//����� ���� ���� �ҷ�����
	void TownMenu();	//���� ���
	void DungeonList();	//���� ���
	void NowBattle(int MonsterNumber);	//���� ȭ��
	void PrintObject();
	void PrintMessage(int Outcome, int MonsterNumber);	//�ý��� �޽��� ���
	void Attack(int Attacker, int MonsterNumber);	//���� �Լ�
	void ShowUserBattle();	//���� �� ���� ���� ������
	void ShowMonsterBattle(int MonsterNumber);	//���� �� �� ���� ������
	void ShowResult(int MonsterNumber);	//�� ��� �� �������ͽ� ������
	void ShowUserInfo();
	void ShowInventory();
	void ShowInvenotryTap(int WeaponType);	//�� �� ���� ���� �����ִ� �Լ�
	void GetWeaponName(int iWeaponType, int iWeaponIndex);
	int GetWeaponPower();	//�� ���� Weapon Ŭ�����κ��� �̸��� ���ݷ��� �������� �Ѵ�
	void ShowMonsterInfo();
	void WeaponShop();
	int BuyScript(int iBuyOrNot, int iGetWeaponType, int iGetWeaponIndex, string WeaponName);
	void PrintBuyMessage(int YesOrNo);
	void SaveMenu();
	void DeleteInfo();
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~Game();
};

