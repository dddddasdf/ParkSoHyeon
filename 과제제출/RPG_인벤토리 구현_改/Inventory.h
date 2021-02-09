#pragma once
#include "Weapon.h"
#include <vector>

#define ITEM_LIMIT 5	//����� �� ���� ���� 5������ ���� ����

class Inventory
{
private:
	Inventory *Parent;
	const string sName;

public:
	Inventory() { }
	Inventory(string Name);

	void SetParent(Inventory *TemporaryParent);

	virtual void AddInventory(Inventory *TemporaryInventory) = 0;	//����Ʈ�� �߰�
	virtual void DeleteInventory(Inventory *TemporaryInventory) = 0;	//����
	virtual int ReturnWeaponIndex(int WeaponNumber) = 0;

	~Inventory();
};

class Bag : public Inventory
{
private:
	vector <Inventory*> InventoryList;

	int m_iItemCount;	//���� �ִ� ������ ����
public:
	Bag(string Name);

	void AddInventory(Inventory *TemporaryInventory) override;
	void DeleteInventory(Inventory *TemporaryInventory) override;	//����
	int ReturnItemCount() { return m_iItemCount; }	//�ش� ���� ���� ���� ����
	int ReturnWeaponIndex(int WeaponNumber) override;	//���� �ε��� �Ѱ��ִ� �Լ�

	~Bag();
};

class Item : public Inventory
{
private:
	int m_iItemIndex;	//���� �ε��� ���� ���� ����
	string m_sItemName;	//���� �̸� ���� ���ڿ�
public:
	Item(WeaponStruct *BoughtWeapon);

	void AddInventory(Inventory *TemporaryInventory) { };
	void DeleteInventory(Inventory *TemporaryInventory) { };
	int ReturnWeaponIndex(int WeaponNumber) override;

	~Item() {  }
};


//��� ����� ��ų ������ ������ �κ��丮 �����ߴ� �ڵ�� ����� �� �ʿ�
//���� �κ��丮 �����ϰ� �����ߴ� �� Ȱ���ϱ�� �� ���� ��ü ������ �޾ƿ� �� �ƴ϶� �̸��� �ε�����

//������ �����ٶ�
//Game.cpp���� �κ� �� �� ������ ���� ���� ����
//���������� �� ������ ������??????

//���� �ڵ忡�� �� ���� �� �κе�
//���� ������ ������ �� �κ� �����ϴ� ��Ʈ
//���� ������ �ε��� �� �κ� �ҷ����� ��Ʈ
//�κ� �����ִ� ��Ʈ
//���� ������ �� �� �κ����� ���� �κ�
//�κ� �� �� �� Ȯ���ϴ� �κ�

//�ٸ� �Լ����� Item ���� Bag�� ����Τ� ���� �� Ȯ����
//���̷��� �Ǹ� ���浵 game.h���� �ϳ��ϳ� �� ������� �� �ƴ϶� �Լ����� ����� ���� ���濡 ���������� �Ǵ� �� �ƴѰ�?? �ƴԸ���