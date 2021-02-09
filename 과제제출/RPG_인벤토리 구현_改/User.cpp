#include "User.h"
#define WEAPON_OK 1
#define WEAPON_NO 0	//무기 갖고 있으면 1 아님 0

//4월 1일 진척도: 유저 클래스 분리 중 유저 데이터를 Game 에서 처리할지 User에서 처리해야 할지 고민 필요


User::User()
{
	
}

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

void User::ChangeName(string Name)
{
	m_sUserName = Name;
}

bool User::LoadDefaultUserData()
{
	//디폴트 유저 정보 텍스트 파일 읽어올 때 숫자가 의미하는 순서
	//공격력 최대생명력 렙업하기위한경험치 현재경험치 레벨 소지골드
	//코드에서 추가로 설정해줘야 하는 변수 현재경험치 몹한테 주는 경험치 현재생명력

	ifstream InfoLoad;
	InfoLoad.open("DefaultUserInfo.txt");
	if (InfoLoad.is_open())
	{
		InfoLoad >> m_iUserAttack;
		InfoLoad >> m_iUserMaxLife;
		InfoLoad >> m_iUserMaxExp;
		InfoLoad >> m_iUserCurrentExp;
		InfoLoad >> m_iUserLevel;
		InfoLoad >> m_iUserGold;
		m_iUserCurrentLife = m_iUserMaxLife;
		m_iHaveWeapon = WEAPON_NO;

		return true;
	}
	else	
		return false;	//디폴트 유저 파일이 없을 경우 에러임을 표시하고 메인 화면으로 돌아간다
}

bool User::LoadUserData(int DataNumber)
{
	//변수 순서->유저 이름, 공격력, 최대 생명력, 렙업하기 위한 경험치, 레벨, 골드, 현재 경험치, 현재 생명력
	//다음 줄은 무기 여부 무기 있으면 1 무기 타입, 무기 타입, 무기 인덱스 / 없으면 0
	//마지막 줄은 인벤토리 로드

	ifstream InfoLoad;
	string sFileName = "SavePlayer" + to_string(DataNumber) + ".txt";
	InfoLoad.open(sFileName);
	if (InfoLoad.is_open())
	{
		InfoLoad >> m_sUserName;
		InfoLoad >> m_iUserAttack;
		InfoLoad >> m_iUserMaxLife;
		InfoLoad >> m_iUserMaxExp;
		InfoLoad >> m_iUserLevel;
		InfoLoad >> m_iUserGold;
		InfoLoad >> m_iUserCurrentExp;
		InfoLoad >> m_iUserCurrentLife;
		InfoLoad >> m_iHaveWeapon;
		if (m_iHaveWeapon == WEAPON_OK)
		{
			InfoLoad >> m_iHaveWeaponType;
			InfoLoad >> m_iHaveWeaponIndex;
		}
		for (int i = 0; i < 5; i++)
		{
			InfoLoad >> m_iInventoryArr[0][i];
			InfoLoad >> m_iInventoryArr[1][i];
		}
		InfoLoad.close();
		return true;
	}
	else
		return false;	//디폴트 유저 파일이 없을 경우 에러임을 표시하고 메인 화면으로 돌아간다
}

void User::SaveUserData(int DataNumber)
{
	string sFileName = "SavePlayer" + to_string(DataNumber) + ".txt";
	ofstream DataSave(sFileName);
	DataSave << m_sUserName << " " << m_iUserAttack << " " << m_iUserMaxLife << " " << m_iUserMaxExp << " " << m_iUserLevel << " "
		<< m_iUserGold << " " << m_iUserCurrentExp << " " << m_iUserCurrentLife << "\n";

	if (m_iHaveWeapon == WEAPON_NO)
		DataSave << m_iHaveWeapon << "\n";
	else if (m_iHaveWeapon == WEAPON_OK)
		DataSave << m_iHaveWeapon << " " << m_iHaveWeaponType << " " << m_iHaveWeaponIndex << "\n";

	for (int i = 0; i < 5; i++)
	{
		DataSave << m_iInventoryArr[0][i] << " " << m_iInventoryArr[1][i];

		if (i == 4)
			break;
		DataSave << " ";
	}

	DataSave.close();
}

bool User::StockUpWeapon(int WeaponType, int WeaponIndex)
{
	//아무튼 무기 카운트 inventory에서 리턴 받고... LIMIT에 도달하면 false 반납하기로
	//무기 종류 숫자 받음->무기 종류 숫자로 메인 인벤토리에서 가방 벡터의 해당 원소 호출->해당 가방 호출됨->거기서 무기 카운트 반환 함수 사용... 이렇게 하면 될 듯
	

	//아래가 기존 함수
	for (int i = 0; i < 5; i++)
	{
		if (m_iInventoryArr[0][i] == BLANK)
		{
			m_iInventoryArr[0][i] = WeaponType;
			m_iInventoryArr[1][i] = WeaponIndex;

			return true;
		}
	}

	return false;
}

void User::StockUpWeapon(int WeaponIndex, int WeaponType, int ArrIndex)
{
	//여긴 인벤이 다 차서 물건 버리고 구매하는 걸 선택했을 때 동작하는 무기 재고 채우기 함수

	m_iInventoryArr[0][ArrIndex - 1] = WeaponIndex;
	m_iInventoryArr[1][ArrIndex - 1] = WeaponType;
}

void User::LifeDamaged(int Damage)
{
	if (m_iUserCurrentLife - Damage >= 0)
		m_iUserCurrentLife -= Damage;
	else
		m_iUserCurrentLife = 0;
}

void User::LifeReset()
{
	m_iUserCurrentLife = m_iUserMaxLife;
}

bool User::AcquireReward(int GetExp, int GetGold)
{
	m_iUserCurrentExp += GetExp;
	m_iUserGold += GetGold;

	if (m_iUserCurrentExp >= m_iUserMaxExp)
		return true;
	
	return false;
}

void User::LevelUp(int *IncreaseAttack, int *IncreaseLife)
{
	m_iUserLevel++;

	//공격력은 1~5, 생명력은 1~10 중 랜덤한 숫자로 증가
	int iAttackPlus = (rand() % 4) + 1;
	int iLifePlus = (rand() % 9) + 1;

	m_iUserAttack += iAttackPlus;
	m_iUserMaxLife += iLifePlus;
	m_iUserCurrentExp = 0;
	m_iUserMaxExp += 3;
	m_iUserCurrentLife = m_iUserMaxLife;

	*IncreaseAttack = iAttackPlus;
	*IncreaseLife = iLifePlus;
}

void User::ForFeitGold()
{
	if (m_iUserGold >= 10)
	{
		double dForfeitGold;	//몰수 골드
		dForfeitGold = static_cast<double>(m_iUserGold / 10);
		m_iUserGold -= static_cast<int>(dForfeitGold);	//가진 돈 1/10이 뺏긴다
	}
	else if (m_iUserGold > 0 && m_iUserGold < 10)
	{
		m_iUserGold--;
	}
}

void User::DeductGold(int WeaponPrice)
{
	m_iUserGold -= WeaponPrice;
}

void User::ReturnInventoryArr(int &TmpType, int &TmpIndex, int x)
{
	TmpType = m_iInventoryArr[0][x];
	TmpIndex = m_iInventoryArr[1][x];
}

bool User::EquipWeaopn(int ArrIndex)
{
	if (m_iInventoryArr[0][ArrIndex - 1] != BLANK)
	{
		m_iHaveWeaponType = m_iInventoryArr[0][ArrIndex - 1];
		m_iHaveWeaponIndex = m_iInventoryArr[1][ArrIndex - 1];

		if (m_iHaveWeapon == WEAPON_NO)
			m_iHaveWeapon = WEAPON_OK;	//겸사겸사 무기 소지 여부 변수도 토글되게 변경

		return true;
	}
	else
		return false;
}

int User::ReturnUserInt(int VariableName)
{
	switch (VariableName)
	{
	case VARIABLE_ATTACK:
		return m_iUserAttack;
	case VARIABLE_CURRENTLIFE:
		return m_iUserCurrentLife;
	case VARIABLE_MAXLIFE:
		return m_iUserMaxLife;
	case VARIABLE_GOLD:
		return m_iUserGold;
	case VARIABLE_HAVEWEAPON:
		return m_iHaveWeapon;
	case VARIABLE_LEVEL:
		return m_iUserLevel;
	case VARIABLE_MAXEXP:
		return m_iUserMaxExp;
	case VARIABLE_WEAPONINDEX:
		return m_iHaveWeaponIndex;
	case VARIABLE_WEAPONTYPE:
		return m_iHaveWeaponType;
	case VARIABLE_CURRENTEXP:
		return m_iUserCurrentExp;
	default:
		return 0;
	}
}

User::~User()
{
}
