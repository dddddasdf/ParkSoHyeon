#pragma once
#include "Weapon.h"
#include <vector>

#define ITEM_LIMIT 5	//����� �� ���� ���� 5������ ���� ����
#define NO_ITEM -1

class Inventory
{
private:
	Inventory *Parent;
	const string sName;

public:
	Inventory() { }
	Inventory(string Name);

	void SetParent(Inventory *TemporaryParent);

	virtual vector<Inventory*> ReturnInventoryList() = 0;

	virtual void AddInventory(Inventory *TemporaryInventory) = 0;	//����Ʈ�� �߰�
	virtual void DeleteInventory(Inventory *TemporaryInventory) = 0;	//����
	virtual int ReturnItemCount(int BagTap) = 0;
	virtual int ReturnItemCount() = 0;
	virtual int ReturnWeaponIndex(int BagTap, int WeaponNumber) = 0;
	virtual int ReturnWeaponIndex(int WeaponNumber) = 0;
	virtual string ReturnItemName(int ItemNumber) = 0;	//�̸� ���ڿ� ��ȯ

	~Inventory();
};

class Bag : public Inventory
{
private:
	vector <Inventory*> InventoryList;

	int m_iItemCount;	//���� �ִ� ������ ����
public:
	Bag() {  }
	Bag(string Name);

	vector<Inventory*> ReturnInventoryList() { return InventoryList; }

	int ReturnItemCount(int BagTap) { 
		return InventoryList[BagTap]->ReturnItemCount(); }
	int ReturnItemCount() { return m_iItemCount; }	//�ش� ���� ���� ���� ����
	
	void AddInventory(Inventory *TemporaryInventory) override;
	void DeleteInventory(Inventory *TemporaryInventory) {};	//����
	int ReturnWeaponIndex(int BagTap, int WeaponNumber) { return InventoryList[BagTap]->ReturnWeaponIndex(WeaponNumber); }
	int ReturnWeaponIndex(int WeaponNumber) override;	//���� �ε��� �Ѱ��ִ� �Լ�
	string ReturnItemName(int ItemNumber) override;

	~Bag();
};

class Item : public Inventory
{
private:
	int m_iItemIndex;	//���� �ε��� ���� ���� ����
	string m_sItemName;	//���� �̸� ���� ���ڿ�
public:
	Item(WeaponStruct *BoughtWeapon);

	void SetItemIndexDefault() { m_iItemIndex = NO_ITEM; }	//�ʱ�ȭ�� �� �ε��� ���ֹ��� �����Ⱚ ����

	vector<Inventory*> ReturnInventoryList() = 0;

	int ReturnItemCount(int BagTap) { return NULL; }
	int ReturnItemCount() { return NULL; }
	string ReturnItemName(int ItemNumber) override;
	void AddInventory(Inventory *TemporaryInventory) { }
	void DeleteInventory(Inventory *TemporaryInventory) { };
	int ReturnWeaponIndex(int BagTap, int WeaponNumber) { return NULL; }
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

//2/15 ��� ���� �κ� �ҷ��� �� �����Ⱚ ������ �������� ù ������ �κ� ������ �ε����� �����Ⱚ ���� �ʿ�