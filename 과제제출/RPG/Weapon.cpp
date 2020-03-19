#include "Weapon.h"



Weapon::Weapon()
{
}

bool Weapon::InitWeaponList()
{
	ifstream WeaponLoad;
	WeaponLoad.open("DefaultUserInfo.txt");
	if (WeaponLoad.is_open())
	{
		/*WeaponLoad >> m_iUserAttack;
		WeaponLoad >> m_iUserMaxLife;
		WeaponLoad >> m_iUserMaxExp;
		WeaponLoad >> m_iUserCurrentExp;
		WeaponLoad >> m_iUserLevel;
		WeaponLoad >> m_iUserGold;
		m_iUserCurrentLife = m_iUserMaxLife;
		m_iHaveWeapon = WEAPON_NO;*/
		return true;
	}
	else
	{
		BoxErase(WIDTH, HEIGHT);

		RED
			gotoxy(28, 14);
		cout << "에러 발생";
		gotoxy(6, 16);
		cout << "무기 정보 텍스트 파일을 읽어올 수 없습니다...";
		ORIGINAL

			system("pause>null");
		return false;	//무기 파일이 없을 경우 에러임을 표시하고 메인 화면으로 돌아간다
	}
}

Weapon::~Weapon()
{
}
