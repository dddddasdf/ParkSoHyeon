#include "User.h"
#define WEAPON_OK 1
#define WEAPON_NO 0	//무기 갖고 있으면 1 아님 0

//4월 1일 진척도: 유저 클래스 분리 중 유저 데이터를 Game 에서 처리할지 User에서 처리해야 할지 고민 필요


User::User()
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
	{
		UserMap.BoxErase(WIDTH, HEIGHT);

		RED
			gotoxy(26, 14);
		cout << "에러 발생";
		gotoxy(6, 16);
		cout << "플레이어 정보 텍스트 파일을 읽어올 수 없습니다...";
		ORIGINAL

		system("pause>null");
		return false;	//디폴트 유저 파일이 없을 경우 에러임을 표시하고 메인 화면으로 돌아간다
	}
}

bool User::LoadUserData(int DataNumber)
{
	//변수 순서->유저 이름, 공격력, 최대 생명력, 렙업하기 위한 경험치, 레벨, 골드, 현재 경험치, 현재 생명력
	//다음 줄은 무기 여부 무기 있으면 1 무기 타입, 무기 이름, 공격력, 가격 / 없으면 0

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
		if (m_iHaveWeapon == WEAPON_NO)
			InfoLoad.close();
		else if (m_iHaveWeapon == WEAPON_OK)
		{
			
		}
		return true;
	}
	else
	{
		UserMap.BoxErase(WIDTH, HEIGHT);

		RED
		gotoxy(26, 14);
		cout << "에러 발생";
		gotoxy(6, 16);
		cout << "플레이어 정보 텍스트 파일을 읽어올 수 없습니다...";
		ORIGINAL

		system("pause>null");
		return false;	//디폴트 유저 파일이 없을 경우 에러임을 표시하고 메인 화면으로 돌아간다
	}
}

void User::SaveUserData(int DataNumber)
{
	string sFileName = "SavePlayer" + to_string(DataNumber) + ".txt";
	ofstream DataSave(sFileName);
	DataSave << m_sUserName << " " << m_iUserAttack << " " << m_iUserMaxLife << " " << m_iUserMaxExp << " " << m_iUserLevel << " "
		<< m_iUserGold << " " << m_iUserCurrentExp << " " << m_iUserCurrentLife << "\n";

	if (m_iHaveWeapon == WEAPON_NO)
		DataSave << m_iHaveWeapon;
	else if (m_iHaveWeapon == WEAPON_OK)
		DataSave << m_iHaveWeapon << " ";

	DataSave.close();
}

User::~User()
{
}
