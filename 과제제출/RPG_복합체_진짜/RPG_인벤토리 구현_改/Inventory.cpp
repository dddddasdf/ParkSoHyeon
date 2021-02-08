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

}


void Bag::AddInventory(Inventory *TemporaryInventory)
{
	TemporaryInventory->SetParent(this);
	InventoryList.push_back(TemporaryInventory);
}

////////////////////////////////////////////////////////////////////////////////가방

Item::Item(WeaponStruct *BoughtWeapon) : m_iItemIndex(BoughtWeapon->iWeaponIndex), m_sItemName(BoughtWeapon->sWeaponName)
{

}


////////////////////////////////////////////////////////////////////////////////아이템