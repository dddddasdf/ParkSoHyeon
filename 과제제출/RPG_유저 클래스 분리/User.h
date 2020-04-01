#pragma once
#include "Headers.h"
#include "Weapon.h"
#include "MapDraw.h"

class User
{
private:
	string m_sUserName;	//�̸�
	int m_iUserCurrentLife;	//��������
	int m_iUserMaxLife;	//�ִ�����
	int m_iUserAttack;	//���ݷ�
	int m_iUserCurrentExp;		//�������ġ
	int m_iUserMaxExp;	//���� ������ �Ѿ�� ���� �ִ� ����ġ
	int m_iUserGold;	//���� ���
	int m_iUserLevel;	//����
	int m_iHaveWeapon;	//���� ���� �ֳ� �ƴѰ�...
	int m_iHaveWeaponIndex;	//���� �ִ� ������ �ε��� �ѹ�
	int m_iHaveWeaponType;	//���� �ִ� ������ ����

	MapDraw UserMap;
public:
	User();
	bool LoadDefaultUserData();	//����Ʈ ���� ���� �о����, �ؽ�Ʈ�� ���������� �о�鿴�� ��� true�� ��ȯ �ƴҽ� false�� ��ȯ�ϰ� �������� ���۵��� ���ϰ� ����
	bool LoadUserData(int DataNumber);	//����� ���� ���� �ҷ�����
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

