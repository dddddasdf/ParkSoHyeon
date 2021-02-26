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
	virtual bool LoadInventoryData(int DataNumber) = 0;
	virtual void SaveInventoryData(int DataNumber) = 0;	//�κ� ������ �ε�� ����

	virtual void SetItemCount(int ItemCount) = 0;
	virtual void AddInventory(Inventory *TemporaryInventory) = 0;	//����Ʈ�� �߰�
	virtual void AddInventoryWhenItIsFull(Inventory *TemporaryInventory, int ArrayIndex) = 0;	//���� �� á�� �� ���� ���� �� ���� ������...
	virtual void AddLoadItem(Inventory *TemporaryItem) = 0;
	virtual void DeleteInventory(Inventory *TemporaryInventory) = 0;	//����
	virtual int ReturnItemCount() = 0;	//�ش� ���� ���� ���� ����
	virtual int ReturnWeaponIndex(int BagTap, int WeaponNumber) = 0;
	virtual int ReturnWeaponIndex(int WeaponNumber) = 0;
	virtual string ReturnItemName(int ItemNumber) = 0;	//�̸� ���ڿ� ��ȯ
	virtual bool IsFullInventory() = 0;

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

	bool IsFullInventory() override;
	void SetItemCount(int ItemCount) override;
	bool LoadInventoryData(int DataNumber) override;
	void SaveInventoryData(int DataNumber) override;
	void AddInventory(Inventory *TemporaryInventory) override;
	void AddInventoryWhenItIsFull(Inventory *TemporaryInventory, int ArrayIndex) override;
	void AddLoadItem(Inventory *TemporaryItem) override;
	void DeleteInventory(Inventory *TemporaryInventory) {};	//����
	int ReturnWeaponIndex(int BagTap, int WeaponNumber) { return InventoryList[BagTap]->ReturnWeaponIndex(WeaponNumber); }
	int ReturnItemCount() { return m_iItemCount; }	//�ش� ���� ���� ���� ����
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
	Item(int WeaponIndex, string WeaponName);

	void SetItemIndexDefault() { m_iItemIndex = NO_ITEM; }	//�ʱ�ȭ�� �� �ε��� ���ֹ��� �����Ⱚ ����
	void SetItemCount(int ItemCount) { };
	bool LoadInventoryData(int DataNumber) { return false; }
	void SaveInventoryData(int DataNumber) { };
	bool IsFullInventory() { return true; }
	string ReturnItemName(int ItemNumber) override;
	void AddInventory(Inventory *TemporaryInventory) { }
	void AddInventoryWhenItIsFull(Inventory *TemporaryInventory, int ArrayIndex) {  }
	void AddLoadItem(Inventory *TemporaryItem) { }
	void DeleteInventory(Inventory *TemporaryInventory) { }
	int ReturnWeaponIndex(int BagTap, int WeaponNumber) { return NULL; }
	int ReturnWeaponIndex(int WeaponNumber) override;
	int ReturnItemCount() { return NULL; }	//�ش� ���� ���� ���� ����

	~Item() {  }
};


//��� ����� ��ų ������ ������ �κ��丮 �����ߴ� �ڵ�� ����� �� �ʿ�
//���� �κ��丮 �����ϰ� �����ߴ� �� Ȱ���ϱ�� �� ���� ��ü ������ �޾ƿ� �� �ƴ϶� �̸��� �ε�����

//������ �����ٶ�
//Game.cpp���� �κ� �� �� ������ ���� ���� ����
//���������� �� ������ ������??????
