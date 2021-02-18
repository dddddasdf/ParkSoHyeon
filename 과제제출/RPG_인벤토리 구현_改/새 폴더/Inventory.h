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

	virtual vector<Inventory*> ReturnInventoryList() = 0;

	virtual void AddInventory(Inventory *TemporaryInventory) = 0;	//리스트에 추가
	virtual void DeleteInventory(Inventory *TemporaryInventory) = 0;	//지움
	virtual int ReturnItemCount(int BagTap) = 0;
	virtual int ReturnItemCount() = 0;
	virtual int ReturnWeaponIndex(int BagTap, int WeaponNumber) = 0;
	virtual int ReturnWeaponIndex(int WeaponNumber) = 0;
	virtual string ReturnItemName(int ItemNumber) = 0;	//이름 문자열 반환

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

	vector<Inventory*> ReturnInventoryList() { return InventoryList; }

	int ReturnItemCount(int BagTap) { 
		return InventoryList[BagTap]->ReturnItemCount(); }
	int ReturnItemCount() { return m_iItemCount; }	//해당 탭의 무기 개수 리턴
	
	void AddInventory(Inventory *TemporaryInventory) override;
	void DeleteInventory(Inventory *TemporaryInventory) {};	//지움
	int ReturnWeaponIndex(int BagTap, int WeaponNumber) { return InventoryList[BagTap]->ReturnWeaponIndex(WeaponNumber); }
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
	Item(WeaponStruct *BoughtWeapon);

	void SetItemIndexDefault() { m_iItemIndex = NO_ITEM; }	//초기화할 때 인덱스 없애버림 쓰레기값 방지

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


//어떻게 출력을 시킬 것인지 기존에 인벤토리 구현했던 코드는 어떘었나 비교 필요
//유저 인벤토리 간단하게 구현했던 걸 활용하기로 함 무기 전체 정보를 받아올 게 아니라 이름과 인덱스만

//아이템 보여줄때
//Game.cpp에서 인벤 탭 내 아이템 개수 리턴 받음
//순차적으로 각 아이템 보여줌??????

//기존 코드에서 손 봐야 할 부분들
//유저 데이터 저장할 때 인벤 저장하던 파트
//유저 데이터 로드할 때 인벤 불러오던 파트
//인벤 보여주던 파트
//상점 구매할 때 템 인벤으로 들어가는 부분
//인벤 다 찬 거 확인하던 부분

//다른 함수에서 Item 만들어서 Bag에 제대로ㅓ 들어가는 거 확인함
//ㄴ이렇게 되면 가방도 game.h에서 하나하나 탭 만들어줄 게 아니라 함수에서 만들고 메인 가방에 때려박으면 되는 거 아닌가?? 아님말고

//2/15 경과 지금 인벤 불러올 때 쓰레기값 때문에 난리났음 첫 생성시 인벤 아이템 인덱스에 쓰레기값 제거 필요