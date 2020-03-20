#pragma once
#include "Headers.h"
#include "MapDraw.h"

struct WeaponStruct
{
	string sWeaponName;	//���� �̸�
	int iWeaponPrice;	//���� ����
	int iWeaponPower;	//���� ���ݷ�
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
	int m_iBowNumber;
	int m_iDaggerNumber;
	int m_iGunNumber;
	int m_iSwordNumber;
	int m_iWandNumber;
	int m_iHammerNumber;
public:
	Weapon();
	bool InitWeaponList();	//���� ����Ʈ ������
	void InputWeaponData();	//����ü ����� ������ �Է�
	void PrintWeaponList(int WeaponType);	//���� ����Ʈ ���
	void FreeWeaopnList();	//���� ����Ʈ �����Ҵ� ����
	int ReturnWeaponPower();	//���� ���ݷ� ��ȯ
	~Weapon();
};

class Sword: public Weapon
{
private:
	WeaponStruct *SwordArr;
public:
	void CreateSwordArr();
	void InputSwordData(string WeaponName, int WeaponPrice, int WeaponPower);
	void PrintSwordList();
};

class Bow : public Weapon
{
private:
	WeaponStruct *BowStruct;
};

class Dagger : public Weapon
{
private:
	WeaponStruct *DaggerStruct;
};

class Gun : public Weapon
{
private:
	WeaponStruct *GunStruct;
};

class Wand : public Weapon
{
private:
	WeaponStruct *WandStruct;
};

class Hammer : public Weapon
{
private:
	WeaponStruct *HammerStruct;
};