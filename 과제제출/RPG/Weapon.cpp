#include "Weapon.h"



Weapon::Weapon()
{
}

bool Weapon::InitWeaponList()
{
	ifstream WeaponLoad;
	WeaponLoad.open("WeaponList.txt");
	if (WeaponLoad.is_open())
	{
		string sWeaponType;

		while (!WeaponLoad.eof())
		{
			WeaponLoad >> sWeaponType;

			if (sWeaponType == "Bow")
				m_iBowNumber++;
			else if (sWeaponType == "Dagger")
				m_iDaggerNumber++;
			else if (sWeaponType == "Gun")
				m_iGunNumber++;
			else if (sWeaponType == "Wand")
				m_iWandNumber++;
			else if (sWeaponType == "Hammer")
				m_iHammerNumber++;
			else if (sWeaponType == "Sword")
				m_iSwordNumber++;
		}

		WeaponLoad.close();
		return true;
	}
	else
	{
		return false;	//���� ������ ���� ��� �������� ǥ���ϰ� ���� ȭ������ ���ư���
	}
}

void Weapon::InputWeaponData()
{

}

void Sword::CreateSwordArr()
{
	SwordArr = new WeaponStruct[m_iSwordNumber];

	for (int i = 0; i < m_iSwordNumber; i++)
	{
		SwordArr[i].iWeaponPower = NULL;
		SwordArr[i].iWeaponPrice = NULL;
	}
}

void Sword::InputSwordData(string WeaponName, int WeaponPrice, int WeaponPower)
{
	int i = 0;
	for (; i < m_iSwordNumber; i++)
	{
		if (SwordArr[i].iWeaponPower == NULL)
			break;
	}

	SwordArr[i].sWeaponName = WeaponName;
	SwordArr[i].iWeaponPrice = WeaponPrice;
	SwordArr[i].iWeaponPower = WeaponPower;
}

void Sword::PrintSwordList()
{
	int iYPos = 6;

	for (int i = 0; i < m_iSwordNumber; i++)
	{
		gotoxy(10, iYPos);
		cout << "����: " << SwordArr[i].iWeaponPrice;
		gotoxy(35, iYPos);
		cout << "���� Ÿ��: �ܰ�";
		iYPos++;
		gotoxy(10, iYPos);
		cout << "�����: " << SwordArr[i].sWeaponName;
		gotoxy(35, iYPos);
		cout << "���ݷ�: " << SwordArr[i].iWeaponPower;

		iYPos += 2;
	}
	
	gotoxy(24, iYPos);
	cout << "���� ������";

	iYPos += 2;

	gotoxy(24, iYPos);
	cout << "���� ������";

	gotoxy(26, iYPos);
	cout << "���ư���";
}

Weapon::~Weapon()
{
}
