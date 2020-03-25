#pragma once
#include "Headers.h"
#include "MapDraw.h"
#define PAGE_PREVIOUS -5
#define PAGE_NEXT -4
#define CANNOT_BUY -3

struct WeaponStruct
{
	string sWeaponName;	//���� �̸�
	int iWeaponPrice;	//���� ����
	int iWeaponPower;	//���� ���ݷ�
	int iWeaponType;	//���� Ÿ��
};

enum TYPE
{
	TYPE_DAGGER = 1,
	TYPE_GUN = 2,
	TYPE_SWORD = 3,
	TYPE_WAND = 4,
	TYPE_BOW = 5,
	TYPE_HAMMER = 6
};

class Weapon: public MapDraw
{
protected:
	static int m_iBowNumber;
	static int m_iDaggerNumber;
	static int m_iGunNumber;
	static int m_iSwordNumber;
	static int m_iWandNumber;
	static int m_iHammerNumber;
public:
	Weapon();
	bool InitWeaponList();	//���� ����Ʈ ������
	void InputWeaponData(string WeaponName, int WeaponPrice, int WeaponPower, int WeaponNumber, WeaponStruct *InputWeaponStruct);	//������ �Է�
	int PrintWeaponList(int HaveGold, int WeaponType, int WeaponNumber, WeaponStruct *ChangeWeapon, WeaponStruct *TypeWeapon);	//���� ����Ʈ ���
	void FreeWeaopnList();	//���� ����Ʈ �����Ҵ� ����
	void BuyWeapon(WeaponStruct *ChangeWeapon, WeaponStruct TargetWeapon);	//���� ����
	~Weapon();
};

class Sword: public Weapon
{
private:
	WeaponStruct *SwordStruct;
public:
	Sword() { }
	void CreateSwordArr();
	void InputSwordData(string WeaponName, int WeaponPrice, int WeaponPower);
	int PrintSwordList(int HaveGold, WeaponStruct *ChangeWeapon);
	~Sword() { delete[] SwordStruct; }
};

class Bow : public Weapon
{
private:
	WeaponStruct *BowStruct;
public:
	Bow() { }
	void CreateBowArr();
	void InputBowData(string WeaponName, int WeaponPrice, int WeaponPower);
	int PrintBowList(int HaveGold, WeaponStruct *ChangeWeapon);
	~Bow() { delete[] BowStruct; }
};

class Dagger : public Weapon
{
private:
	WeaponStruct *DaggerStruct;
public:
	Dagger() { }
	void CreateDaggerArr();
	void InputDaggerData(string WeaponName, int WeaponPrice, int WeaponPower);
	int PrintDaggerList(int HaveGold, WeaponStruct *ChangeWeapon);
	~Dagger() { delete[] DaggerStruct; }
};

class Gun : public Weapon
{
private:
	WeaponStruct *GunStruct;
public:
	Gun() { }
	~Gun() { }
};

class Wand : public Weapon
{
private:
	WeaponStruct *WandStruct;
public:
	Wand() { }
	~Wand() { }
};

class Hammer : public Weapon
{
private:
	WeaponStruct *HammerStruct;
public:
	Hammer() { }
	~Hammer() { }
};