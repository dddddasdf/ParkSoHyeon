#pragma once
#include "Weapon.h"
#include <vector>

//무기 구조체의 정보를 받아와서 아이템으로 집어넣게...


//인벤토리 클래스는 함수 셔틀말고는 역할이 없는 건지 잘 모르겠다,,,
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


//2월 5일 작업하던 내용
//아직 본문 구현은 제대로 못함... 어떻게 출력을 시킬 것인지 기존에 인벤토리 구현했던 코드는 어떘었나 비교 필요