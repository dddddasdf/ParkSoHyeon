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
		cout << "���� �߻�";
		gotoxy(6, 16);
		cout << "���� ���� �ؽ�Ʈ ������ �о�� �� �����ϴ�...";
		ORIGINAL

			system("pause>null");
		return false;	//���� ������ ���� ��� �������� ǥ���ϰ� ���� ȭ������ ���ư���
	}
}

Weapon::~Weapon()
{
}
