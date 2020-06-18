#include "User.h"

void User::InitUserData()
{
	m_sUserName = "";
	m_iUserCurrentLife = NULL;
	m_iUserMaxLife = NULL;
	m_iUserAttack = NULL;
	m_iUserCurrentExp = NULL;
	m_iUserMaxExp = NULL;
	m_iUserGold = NULL;
	m_iUserLevel = NULL;
	m_iHaveWeapon = NULL;
	m_iHaveWeaponIndex = -1;	//안 갖고 잇으면 -1
	m_iHaveWeaponType = -1;	//마찬가지

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 5; j++)
			m_iInventoryArr[i][j] = { BLANK };
	}
};