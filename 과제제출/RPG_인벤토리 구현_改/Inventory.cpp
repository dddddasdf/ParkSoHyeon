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

bool Bag::LoadInventoryData(int DataNumber) 
{
	ifstream InfoLoad;
	string sFileName = "SaveInventory" + to_string(DataNumber) + ".txt";
	InfoLoad.open(sFileName);

	if (InfoLoad.is_open())
	{
		int iItemCountTmp = 0;
		for (int i = 0; i < 6; i++)
		{
			InfoLoad >> iItemCountTmp;
			InfoLoad >> iItemCountTmp;
			InventoryList[i]->SetItemCount(iItemCountTmp);
			
			for (int j = 0; j < iItemCountTmp; j++)
			{
				int iIntTmp;
				string sStringTmp;

				InfoLoad >> sStringTmp;
				InfoLoad >> iIntTmp;
				Inventory *LoadItem = new Item(iIntTmp, sStringTmp);

				InventoryList[i]->AddLoadItem(LoadItem);
			}
		}
		
		InfoLoad.close();
		return true;
	}
	else
		return false;	//디폴트 유저 파일이 없을 경우 에러임을 표시하고 메인 화면으로 돌아간다
}

void Bag::SetItemCount(int ItemCount) 
{ 
	m_iItemCount = ItemCount; 
}

void Bag::SaveInventoryData(int DataNumber)
{
	string sFileName = "SaveInventory" + to_string(DataNumber) + ".txt";
	ofstream DataSave(sFileName);

	for (int i = 0; i < 6; i++)
	{
		DataSave << i << " " << InventoryList[i]->ReturnItemCount() << " ";

		for (int j = 0; j < InventoryList[i]->ReturnItemCount(); j++)
		{
			DataSave << InventoryList[i]->ReturnItemName(j + 1) << " " << InventoryList[i]->ReturnWeaponIndex(j + 1) << " ";
		}
		DataSave << "\n";
	}

	DataSave.close();
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

void Bag::AddLoadItem(Inventory *TemporaryItem)
{
	TemporaryItem->SetParent(this);
	InventoryList.push_back(TemporaryItem);
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