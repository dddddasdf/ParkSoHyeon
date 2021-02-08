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

	virtual void ViewContents() = 0;	//���빰 ������
	virtual void AddInventory(Inventory *TemporaryInventory) = 0;	//����Ʈ�� �߰�
	virtual void DeleteInventory(Inventory *TemporaryInventory) = 0;	//����

	~Inventory();
};

class Bag : public Inventory
{
private:
	vector <Inventory*> InventoryList;

	int m_iItemCount;	//���� �ִ� ������ ����
public:
	Bag(string Name);

	void ViewContents() override;	//���빰 ������
	void AddInventory(Inventory *TemporaryInventory) override;
	void DeleteInventory(Inventory *TemporaryInventory) override;	//����
	int ReturnItemCount() { return m_iItemCount; }

	~Bag();
};

class Item : public Inventory
{
private:
	int m_iItemIndex;	//���� �ε��� ���� ���� ����
	string m_sItemName;	//���� �̸� ���� ���ڿ�
public:
	Item(WeaponStruct *BoughtWeapon);

	void AddInventory(Inventory *TemporaryInventory);
	void ViewContents();
	void DeleteInventory(Inventory *TemporaryInventory);

	~Item() {  }
};


//2�� 5�� �۾��ϴ� ����
//���� ���� ������ ����� ����... ��� ����� ��ų ������ ������ �κ��丮 �����ߴ� �ڵ�� ����� �� �ʿ�
//���� �κ��丮 �����ϰ� �����ߴ� �� Ȱ���ϱ�� �� ���� ��ü ������ �޾ƿ� �� �ƴ϶� �̸��� �ε�����

//������ �����ٶ�
//Game.cpp���� �κ� �� �� ������ ���� ���� ����
//���������� �� ������ ������??????