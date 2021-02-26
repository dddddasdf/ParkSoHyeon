#pragma once
#include "Weapon.h"
#include <vector>

#define ITEM_LIMIT 5	//무기는 각 무기 별로 5개까지 소지 제한
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
	virtual void SaveInventoryData(int DataNumber) = 0;	//인벤 데이터 로드랑 저장

	virtual void SetItemCount(int ItemCount) = 0;
	virtual void AddInventory(Inventory *TemporaryInventory) = 0;	//리스트에 추가
	virtual void AddInventoryWhenItIsFull(Inventory *TemporaryInventory, int ArrayIndex) = 0;	//가방 다 찼을 때 어디다 새로 템 넣을 건지를...
	virtual void AddLoadItem(Inventory *TemporaryItem) = 0;
	virtual void DeleteInventory(Inventory *TemporaryInventory) = 0;	//지움
	virtual int ReturnItemCount() = 0;	//해당 탭의 무기 개수 리턴
	virtual int ReturnWeaponIndex(int BagTap, int WeaponNumber) = 0;
	virtual int ReturnWeaponIndex(int WeaponNumber) = 0;
	virtual string ReturnItemName(int ItemNumber) = 0;	//이름 문자열 반환
	virtual bool IsFullInventory() = 0;

	~Inventory();
};

class Bag : public Inventory
{
private:
	vector <Inventory*> InventoryList;

	int m_iItemCount;	//갖고 있는 아이템 개수
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
	void DeleteInventory(Inventory *TemporaryInventory) {};	//지움
	int ReturnWeaponIndex(int BagTap, int WeaponNumber) { return InventoryList[BagTap]->ReturnWeaponIndex(WeaponNumber); }
	int ReturnItemCount() { return m_iItemCount; }	//해당 탭의 무기 개수 리턴
	int ReturnWeaponIndex(int WeaponNumber) override;	//무기 인덱스 넘겨주는 함수
	string ReturnItemName(int ItemNumber) override;

	~Bag();
};

class Item : public Inventory
{
private:
	int m_iItemIndex;	//무기 인덱스 받을 정수 변수
	string m_sItemName;	//무기 이름 받을 문자열
public:
	Item(int WeaponIndex, string WeaponName);

	void SetItemIndexDefault() { m_iItemIndex = NO_ITEM; }	//초기화할 때 인덱스 없애버림 쓰레기값 방지
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
	int ReturnItemCount() { return NULL; }	//해당 탭의 무기 개수 리턴

	~Item() {  }
};


//어떻게 출력을 시킬 것인지 기존에 인벤토리 구현했던 코드는 어떘었나 비교 필요
//유저 인벤토리 간단하게 구현했던 걸 활용하기로 함 무기 전체 정보를 받아올 게 아니라 이름과 인덱스만

//아이템 보여줄때
//Game.cpp에서 인벤 탭 내 아이템 개수 리턴 받음
//순차적으로 각 아이템 보여줌??????
