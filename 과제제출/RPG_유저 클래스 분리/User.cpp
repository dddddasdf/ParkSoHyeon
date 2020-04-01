#include "User.h"
#define WEAPON_OK 1
#define WEAPON_NO 0	//���� ���� ������ 1 �ƴ� 0

//4�� 1�� ��ô��: ���� Ŭ���� �и� �� ���� �����͸� Game ���� ó������ User���� ó���ؾ� ���� ��� �ʿ�


User::User()
{
	m_sUserName = "";
	m_iUserCurrentLife = NULL;
	m_iUserMaxLife = NULL;
	m_iUserAttack = NULL;
	m_iUserCurrentExp = NULL;
	m_iUserMaxExp = NULL;
	m_iUserGold = NULL;
	m_iUserLevel = NULL;
	m_iHaveWeapon = NULL;
	m_iHaveWeaponIndex = -1;	//�� ���� ������ -1
	m_iHaveWeaponType = -1;	//��������
}

bool User::LoadDefaultUserData()
{
	//����Ʈ ���� ���� �ؽ�Ʈ ���� �о�� �� ���ڰ� �ǹ��ϴ� ����
	//���ݷ� �ִ����� �����ϱ����Ѱ���ġ �������ġ ���� �������
	//�ڵ忡�� �߰��� ��������� �ϴ� ���� �������ġ ������ �ִ� ����ġ ��������

	ifstream InfoLoad;
	InfoLoad.open("DefaultUserInfo.txt");
	if (InfoLoad.is_open())
	{
		InfoLoad >> m_iUserAttack;
		InfoLoad >> m_iUserMaxLife;
		InfoLoad >> m_iUserMaxExp;
		InfoLoad >> m_iUserCurrentExp;
		InfoLoad >> m_iUserLevel;
		InfoLoad >> m_iUserGold;
		m_iUserCurrentLife = m_iUserMaxLife;
		m_iHaveWeapon = WEAPON_NO;
		return true;
	}
	else
	{
		UserMap.BoxErase(WIDTH, HEIGHT);

		RED
			gotoxy(26, 14);
		cout << "���� �߻�";
		gotoxy(6, 16);
		cout << "�÷��̾� ���� �ؽ�Ʈ ������ �о�� �� �����ϴ�...";
		ORIGINAL

		system("pause>null");
		return false;	//����Ʈ ���� ������ ���� ��� �������� ǥ���ϰ� ���� ȭ������ ���ư���
	}
}

bool User::LoadUserData(int DataNumber)
{
	//���� ����->���� �̸�, ���ݷ�, �ִ� �����, �����ϱ� ���� ����ġ, ����, ���, ���� ����ġ, ���� �����
	//���� ���� ���� ���� ���� ������ 1 ���� Ÿ��, ���� �̸�, ���ݷ�, ���� / ������ 0

	ifstream InfoLoad;
	string sFileName = "SavePlayer" + to_string(DataNumber) + ".txt";
	InfoLoad.open(sFileName);
	if (InfoLoad.is_open())
	{
		InfoLoad >> m_sUserName;
		InfoLoad >> m_iUserAttack;
		InfoLoad >> m_iUserMaxLife;
		InfoLoad >> m_iUserMaxExp;
		InfoLoad >> m_iUserLevel;
		InfoLoad >> m_iUserGold;
		InfoLoad >> m_iUserCurrentExp;
		InfoLoad >> m_iUserCurrentLife;
		InfoLoad >> m_iHaveWeapon;
		if (m_iHaveWeapon == WEAPON_NO)
			InfoLoad.close();
		else if (m_iHaveWeapon == WEAPON_OK)
		{
			
		}
		return true;
	}
	else
	{
		UserMap.BoxErase(WIDTH, HEIGHT);

		RED
		gotoxy(26, 14);
		cout << "���� �߻�";
		gotoxy(6, 16);
		cout << "�÷��̾� ���� �ؽ�Ʈ ������ �о�� �� �����ϴ�...";
		ORIGINAL

		system("pause>null");
		return false;	//����Ʈ ���� ������ ���� ��� �������� ǥ���ϰ� ���� ȭ������ ���ư���
	}
}

void User::SaveUserData(int DataNumber)
{
	string sFileName = "SavePlayer" + to_string(DataNumber) + ".txt";
	ofstream DataSave(sFileName);
	DataSave << m_sUserName << " " << m_iUserAttack << " " << m_iUserMaxLife << " " << m_iUserMaxExp << " " << m_iUserLevel << " "
		<< m_iUserGold << " " << m_iUserCurrentExp << " " << m_iUserCurrentLife << "\n";

	if (m_iHaveWeapon == WEAPON_NO)
		DataSave << m_iHaveWeapon;
	else if (m_iHaveWeapon == WEAPON_OK)
		DataSave << m_iHaveWeapon << " ";

	DataSave.close();
}

User::~User()
{
}
