#include "Inventory.h"

Inventory::Inventory(string Name) : sName(Name)
{
	Parent = NULL;
}

void Inventory::SetParent(Inventory *TemporaryParent)
{
	Parent = TemporaryParent;
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

	m_iItemCount++;
}

void Bag::AddInventoryWhenItIsFull(Inventory *TemporaryInventory, int ArrayIndex)
{
	InventoryList[ArrayIndex - 1] = TemporaryInventory;

	m_iItemCount++;
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

bool Bag::IsFullInventory()
{
	if (m_iItemCount < ITEM_LIMIT)
		return true;
	else
		return false;
}

Bag::~Bag()
{
	vector<Inventory*>::iterator iter = InventoryList.begin();
	vector<Inventory*>::iterator endler = InventoryList.end();

	for (; iter != InventoryList.end(); iter++)
	{
		delete (*iter);
	}

	InventoryList.clear();
}

////////////////////////////////////////////////////////////////////////////////가방

Item::Item(int WeaponIndex, string WeaponName) : m_iItemIndex(WeaponIndex), m_sItemName(WeaponName)
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