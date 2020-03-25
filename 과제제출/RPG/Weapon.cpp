#include "Weapon.h"

Weapon::Weapon()
{
}

int Weapon::m_iBowNumber = 0;
int Weapon::m_iDaggerNumber = 0;
int Weapon::m_iGunNumber = 0;
int Weapon::m_iSwordNumber = 0;
int Weapon::m_iWandNumber = 0;
int Weapon::m_iHammerNumber = 0;

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
		return false;	//���� ������ ���� ��� �������� ǥ���ϰ� ���� ȭ������ ���ư���
}

void Weapon::InputWeaponData(string WeaponName, int WeaponPrice, int WeaponPower, int WeaponNumber, WeaponStruct *InputWeaponStruct)
{
	int i = 0;
	for (; i < WeaponNumber; i++)
	{
		if (InputWeaponStruct[i].iWeaponPower == NULL)
			break;
	}

	InputWeaponStruct[i].sWeaponName = WeaponName;
	InputWeaponStruct[i].iWeaponPrice = WeaponPrice;
	InputWeaponStruct[i].iWeaponPower = WeaponPower;
}

int Weapon::PrintWeaponList(int HaveGold, int WeaponType, int WeaponNumber, WeaponStruct *ChangeWeapon, WeaponStruct *TypeWeapon)
{
	int iSelect;

	while (1)
	{
		BoxErase(WIDTH, HEIGHT);

		int iYPos = 3;

		for (int i = 0; i < WeaponNumber; i++)
		{
			gotoxy(10, iYPos);
			cout << "����: " << TypeWeapon[i].iWeaponPrice;
			gotoxy(35, iYPos);
			cout << "���� Ÿ��: ";
			if (WeaponType == TYPE_DAGGER)
				cout << "�ܰ�";
			else if (WeaponType == TYPE_GUN)
				cout << "��";
			else if (WeaponType == TYPE_SWORD)
				cout << "Į";
			else if (WeaponType == TYPE_WAND)
				cout << "����";
			else if (WeaponType == TYPE_BOW)
				cout << "Ȱ";
			else if (WeaponType == TYPE_HAMMER)
				cout << "�б�";
			iYPos++;
			gotoxy(10, iYPos);
			cout << "�����: " << TypeWeapon[i].sWeaponName;
			gotoxy(35, iYPos);
			cout << "���ݷ�: " << TypeWeapon[i].iWeaponPower;

			iYPos += 2;
		}

		gotoxy(24, iYPos);
		cout << "���� ������";

		iYPos += 3;

		gotoxy(24, iYPos);
		cout << "���� ������";

		iYPos += 3;

		gotoxy(26, iYPos);
		cout << "���ư���";

		iSelect = MenuSelectCursor(WeaponNumber + 3, 3, 3, 3);

		if (iSelect == WeaponNumber + 3)
			return 0;
		else if (iSelect == WeaponNumber + 2)
			return PAGE_NEXT;
		else if (iSelect == WeaponNumber + 1)
			return PAGE_PREVIOUS;
		else
		{
			if (HaveGold >= TypeWeapon[iSelect -1].iWeaponPrice)
			{
				if (!ChangeWeapon->sWeaponName.empty())
				{
					ChangeWeapon->sWeaponName.clear();	//������ ���⸦ ��� ������ ���ڿ� �ʱ�ȭ�ϰ� ���� �־��...
				}
				ChangeWeapon->sWeaponName = TypeWeapon[iSelect - 1].sWeaponName;
				ChangeWeapon->iWeaponPower = TypeWeapon[iSelect - 1].iWeaponPower;
				ChangeWeapon->iWeaponPrice = TypeWeapon[iSelect - 1].iWeaponPrice;
				ChangeWeapon->iWeaponType = TypeWeapon[iSelect - 1].iWeaponType;

				return (TypeWeapon[iSelect - 1].iWeaponPrice);
			}
			else
				return CANNOT_BUY;	//���� ���� ��尡 ���� ���ݺ��� ������ ���� ������ ��ȯ
		}
	}
}

void Weapon::BuyWeapon(WeaponStruct *ChangeWeapon, WeaponStruct TargetWeapon)
{
	//������ �� ���� �Լ� Ȥ�ó� �; ���� �״µ� �� ���� �� Ȯ�� �Ǹ� ������ �� ����
	
	if (!ChangeWeapon->sWeaponName.empty())
	{
		ChangeWeapon->sWeaponName.clear();	//������ ���⸦ ��� ������ ���ڿ� �ʱ�ȭ�ϰ� ���� �־��...
	}
	ChangeWeapon->sWeaponName = TargetWeapon.sWeaponName;
	ChangeWeapon->iWeaponPower = TargetWeapon.iWeaponPower;
	ChangeWeapon->iWeaponPrice = TargetWeapon.iWeaponPrice;
}

void Sword::CreateSwordArr()
{
	SwordStruct = new WeaponStruct[m_iSwordNumber];

	for (int i = 0; i < m_iSwordNumber; i++)
	{
		SwordStruct[i].iWeaponPower = NULL;
		SwordStruct[i].iWeaponPrice = NULL;
		SwordStruct[i].iWeaponType = TYPE_SWORD;
	}
}

void Sword::InputSwordData(string WeaponName, int WeaponPrice, int WeaponPower)
{
	//���� �������� ����� �̳��� �������,,,
	//Weapon Ŭ������ ����� �Լ� �������. ������ ���� ���� �Լ� ��Ʈ �ּ� ó���� ���� 
	//Game.cpp���� �о���� ���ڿ�, ���� �ΰ��� ���� �̸��� ���� �� ���ݷ����� ����

	/*int i = 0;
	for (; i < m_iSwordNumber; i++)
	{
		if (SwordArr[i].iWeaponPower == NULL)
			break;
	}

	SwordArr[i].sWeaponName = WeaponName;
	SwordArr[i].iWeaponPrice = WeaponPrice;
	SwordArr[i].iWeaponPower = WeaponPower;*/

	InputWeaponData(WeaponName, WeaponPrice, WeaponPower, m_iSwordNumber, SwordStruct);
}

int Sword::PrintSwordList(int HaveGold, WeaponStruct *ChangeWeapon)
{
	int iReturnConstant;
	iReturnConstant = PrintWeaponList(HaveGold, TYPE_SWORD, m_iSwordNumber, ChangeWeapon, SwordStruct);

	return iReturnConstant;
}

void Bow::CreateBowArr()
{
	BowStruct = new WeaponStruct[m_iBowNumber];

	for (int i = 0; i < m_iBowNumber; i++)
	{
		BowStruct[i].iWeaponPower = NULL;
		BowStruct[i].iWeaponPrice = NULL;
		BowStruct[i].iWeaponType = TYPE_BOW;
	}
}

void Bow::InputBowData(string WeaponName, int WeaponPrice, int WeaponPower)
{
	InputWeaponData(WeaponName, WeaponPrice, WeaponPower, m_iBowNumber, BowStruct);
}

int Bow::PrintBowList(int HaveGold, WeaponStruct *ChangeWeapon)
{
	int iReturnConstant;
	iReturnConstant = PrintWeaponList(HaveGold, TYPE_BOW, m_iBowNumber, ChangeWeapon, BowStruct);

	return iReturnConstant;
}

void Dagger::CreateDaggerArr()
{
	DaggerStruct = new WeaponStruct[m_iDaggerNumber];

	for (int i = 0; i < m_iDaggerNumber; i++)
	{
		DaggerStruct[i].iWeaponPower = NULL;
		DaggerStruct[i].iWeaponPrice = NULL;
		DaggerStruct[i].iWeaponType = TYPE_DAGGER;
	}
}

void Dagger::InputDaggerData(string WeaponName, int WeaponPrice, int WeaponPower)
{
	InputWeaponData(WeaponName, WeaponPrice, WeaponPower, m_iDaggerNumber, DaggerStruct);
}

int Dagger::PrintDaggerList(int HaveGold, WeaponStruct *ChangeWeapon)
{
	int iReturnConstant;
	iReturnConstant = PrintWeaponList(HaveGold, TYPE_DAGGER, m_iDaggerNumber, ChangeWeapon, DaggerStruct);

	return iReturnConstant;
}

Weapon::~Weapon()
{
}
