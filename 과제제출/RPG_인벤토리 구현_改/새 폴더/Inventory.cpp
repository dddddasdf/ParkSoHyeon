#include "Inventory.h"

Inventory::Inventory(string Name) : sName(Name)
{
	Parent = NULL;
}

void Inventory::SetParent(Inventory *TemporaryParent)
{
	Parent = TemporaryParent;
}



Inventory::~Inventory()
{

}

////////////////////////////////////////////////////////////////////////////////메인


Bag::Bag(string Name) : Inventory(Name), m_iItemCount(0)
{
	m_iItemCount = 0;
	
}


void Bag::AddInventory(Inventory *TemporaryInventory)
{
	TemporaryInventory->SetParent(this);
	InventoryList.push_back(TemporaryInventory);
}

int Bag::ReturnWeaponIndex(int WeaponNumber)
{
	int iTemporary = InventoryList[(WeaponNumber - 1)]->ReturnWeaponIndex(WeaponNumber);
	
	return iTemporary;
}

string Bag::ReturnItemName(int ItemNumber)
{
	string Tmp = InventoryList[(ItemNumber - 1)]->ReturnItemName(ItemNumber);

	return Tmp;
}

////////////////////////////////////////////////////////////////////////////////가방

Item::Item(WeaponStruct *BoughtWeapon) : m_iItemIndex(BoughtWeapon->iWeaponIndex), m_sItemName(BoughtWeapon->sWeaponName)
{

}

int Item::ReturnWeaponIndex(int WeaponNumber)
{
	return m_iItemIndex;
}

string Item::ReturnItemName(int ItemNumber)
{
	return m_sItemName;
}

////////////////////////////////////////////////////////////////////////////////아이템