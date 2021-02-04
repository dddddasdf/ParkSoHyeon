#pragma once
#include "Weapon.h"
#include <vector>


class Inventory
{
private:
	Inventory *Parent;
	const string sName;

public:
	Inventory(string Name);





	~Inventory();
};

class Bag : public Inventory
{
private:
	vector <Inventory*> InventoryList;
public:
	Bag(string Name);

	~Bag();
	

};

class Item : public Inventory
{
private:
	WeaponStruct *PossessWeapon;
public:
	Item(WeaponStruct *BoughtWeapon);

	~Item();
};