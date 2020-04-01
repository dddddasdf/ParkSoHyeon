#pragma once
#include "Headers.h"
#include "Weapon.h"
#include "MapDraw.h"

class User
{
private:
	string m_sUserName;	//이름
	int m_iUserCurrentLife;	//현재생명력
	int m_iUserMaxLife;	//최대생명력
	int m_iUserAttack;	//공격력
	int m_iUserCurrentExp;		//현재경험치
	int m_iUserMaxExp;	//다음 레벨로 넘어가기 위한 최대 경험치
	int m_iUserGold;	//소지 골드
	int m_iUserLevel;	//레벨
	int m_iHaveWeapon;	//무기 갖고 있나 아닌가...
	int m_iHaveWeaponIndex;	//갖고 있는 무기의 인덱스 넘버
	int m_iHaveWeaponType;	//갖고 있는 무기의 종류

	MapDraw UserMap;
public:
	User();
	bool LoadDefaultUserData();	//디폴트 유저 파일 읽어오기, 텍스트를 성공적으로 읽어들였을 경우 true를 반환 아닐시 false를 반환하고 새게임이 시작되지 못하게 막음
	bool LoadUserData(int DataNumber);	//저장된 유저 정보 불러오기
	void SaveUserData(int DataNumber);
	void ChangeWeapon(int WeaponIndex, int iHeaveWeaponType);
	string ReturnUserName()
	{
		return m_sUserName;
	}
	int ReturnUserCurrentLife()
	{
		return m_iUserCurrentLife;
	}

	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~User();
};

