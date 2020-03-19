#pragma once
#include "Headers.h"
#include "MapDraw.h"

struct Weaponstruct
{
	string m_sWeaponType;	//무기 종류
	string m_sWeaponName;	//무기 이름
	int m_iWeaponPrice;	//무기 가격
	int m_iWeaponPower;	//무기 공격력
	int m_iWeaponType;	//무기 종류, enum 테스트
};

enum TYPE
{
	TYPE_BOW,
	TYPE_DAGGER,
	TYPE_GUN,
	TYPE_SWORD,
	TYPE_WAND,
	TYPE_HAMMER
};

class Weapon: public MapDraw
{
private:
	string m_sWeaponType;	//무기 종류
	string m_sWeaponName;	//무기 이름
	int m_iWeaponPrice;	//무기 가격
	int m_iWeaponPower;	//무기 공격력
public:
	Weapon();
	bool InitWeaponList();	//무기 리스트 가져옴
	void PrintWeaponList(int WeaponType);	//무기 리스트 출력
	void FreeWeaopnList();	//무기 리스트 동적할당 해제
	~Weapon();
};
