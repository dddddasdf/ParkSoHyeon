#pragma once
#include "Headers.h"
#include "MapDraw.h"
#define PAGE_PREVIOUS -5
#define PAGE_NEXT -4
#define CANNOT_BUY -3

struct WeaponStruct
{
	string sWeaponName;	//무기 이름
	int iWeaponPrice;	//무기 가격
	int iWeaponPower;	//무기 공격력
	int iWeaponType;	//무기 타입
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
	static int m_iBowCount;
	static int m_iDaggerCount;
	static int m_iGunCount;
	static int m_iSwordCount;
	static int m_iWandCount;
	static int m_iHammerCount;
public:
	Weapon();
	bool InitWeaponCount();	//무기 리스트 가져옴
	void InputWeaponData(string WeaponName, int WeaponPrice, int WeaponPower, int WeaponNumber, WeaponStruct *InputWeaponStruct);	//데이터 입력
	void InitWeaponInt(WeaponStruct *MakeWeaponArr, int WeaponNumber, int WeaponType);
	int PrintWeaponList(int HaveGold, int WeaponType, int WeaponNumber, WeaponStruct *ChangeWeapon, WeaponStruct *TypeWeapon);	//무기 리스트 출력
	void BuyWeapon(WeaponStruct *ChangeWeapon, WeaponStruct TargetWeapon);	//무기 구매
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
	void CreateGunArr();
	void InputGunData(string WeaponName, int WeaponPrice, int WeaponPower);
	int PrintGunList(int HaveGold, WeaponStruct *ChangeWeapon);
	~Gun() { delete[] GunStruct; }
};

class Wand : public Weapon
{
private:
	WeaponStruct *WandStruct;
public:
	Wand() { }
	void CreateWandArr();
	void InputWandData(string WeaponName, int WeaponPrice, int WeaponPower);
	int PrintWandList(int HaveGold, WeaponStruct *ChangeWeapon);
	~Wand() { delete[] WandStruct; }
};

class Hammer : public Weapon
{
private:
	WeaponStruct *HammerStruct;
public:
	Hammer() { }
	void CreateHammerArr();
	void InputHammerData(string WeaponName, int WeaponPrice, int WeaponPower);
	int PrintHammerList(int HaveGold, WeaponStruct *ChangeWeapon);
	~Hammer() { delete[] HammerStruct; }
};