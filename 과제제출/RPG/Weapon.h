#pragma once
#include "Headers.h"
#include "MapDraw.h"

struct Weaponstruct
{
	string m_sWeaponType;	//���� ����
	string m_sWeaponName;	//���� �̸�
	int m_iWeaponPrice;	//���� ����
	int m_iWeaponPower;	//���� ���ݷ�
	int m_iWeaponType;	//���� ����, enum �׽�Ʈ
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
	string m_sWeaponType;	//���� ����
	string m_sWeaponName;	//���� �̸�
	int m_iWeaponPrice;	//���� ����
	int m_iWeaponPower;	//���� ���ݷ�
public:
	Weapon();
	bool InitWeaponList();	//���� ����Ʈ ������
	void PrintWeaponList(int WeaponType);	//���� ����Ʈ ���
	void FreeWeaopnList();	//���� ����Ʈ �����Ҵ� ����
	~Weapon();
};
