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

////////////////////////////////////////////////////////////////////////////////����


Bag::Bag(string Name) : Inventory(Name)
{

}

void Bag::AddInventory(Inventory *TemporaryInventory)
{
	TemporaryInventory->SetParent(this);
	InventoryList.push_back(TemporaryInventory);
}

////////////////////////////////////////////////////////////////////////////////����

Item::Item(WeaponStruct *BoughtWeapon) : PossessWeapon(BoughtWeapon)
{

}


////////////////////////////////////////////////////////////////////////////////������