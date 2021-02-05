#pragma once
#include "Weapon.h"
#include <vector>

//���� ����ü�� ������ �޾ƿͼ� ���������� ����ְ�...


//�κ��丮 Ŭ������ �Լ� ��Ʋ����� ������ ���� ���� �� �𸣰ڴ�,,,
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
public:
	Bag(string Name);

	void AddInventory(Inventory *TemporaryInventory) override;

	~Bag();
};

class Item : public Inventory
{
private:
	WeaponStruct *PossessWeapon;
public:
	Item(WeaponStruct *BoughtWeapon);

	/*void AddInventory(Inventory *TemporaryInventory) override;
	void ViewContents() override;*/

	~Item();
};


//2�� 5�� �۾��ϴ� ����
//���� ���� ������ ����� ����... ��� ����� ��ų ������ ������ �κ��丮 �����ߴ� �ڵ�� ����� �� �ʿ�