#pragma once
#include "Weapon.h"
#include <vector>

#define ITEM_LIMIT 5	//무기는 각 무기 별로 5개까지 소지 제한

class Inventory
{
private:
	Inventory *Parent;
	const string sName;

public:
	Inventory() { }
	Inventory(string Name);

	void SetParent(Inventory *TemporaryParent);

	virtual void ViewContents() = 0;	//내용물 보여줌
	virtual void AddInventory(Inventory *TemporaryInventory) = 0;	//리스트에 추가
	virtual void DeleteInventory(Inventory *TemporaryInventory) = 0;	//지움

	~Inventory();
};

class Bag : public Inventory
{
private:
	vector <Inventory*> InventoryList;

	int m_iItemCount;	//갖고 있는 아이템 개수
public:
	Bag(string Name);

	void ViewContents() override;	//내용물 보여줌
	void AddInventory(Inventory *TemporaryInventory) override;
	void DeleteInventory(Inventory *TemporaryInventory) override;	//지움
	int ReturnItemCount() { return m_iItemCount; }

	~Bag();
};

class Item : public Inventory
{
private:
	int m_iItemIndex;	//무기 인덱스 받을 정수 변수
	string m_sItemName;	//무기 이름 받을 문자열
public:
	Item(WeaponStruct *BoughtWeapon);

	void AddInventory(Inventory *TemporaryInventory);
	void ViewContents();
	void DeleteInventory(Inventory *TemporaryInventory);

	~Item() {  }
};


//2월 5일 작업하던 내용
//아직 본문 구현은 제대로 못함... 어떻게 출력을 시킬 것인지 기존에 인벤토리 구현했던 코드는 어떘었나 비교 필요
//유저 인벤토리 간단하게 구현했던 걸 활용하기로 함 무기 전체 정보를 받아올 게 아니라 이름과 인덱스만

//아이템 보여줄때
//Game.cpp에서 인벤 탭 내 아이템 개수 리턴 받음
//순차적으로 각 아이템 보여줌??????