#include "Game.h"



Game::Game()
{
	
}

void Game::GetName(string name)
{
	m_sUserName = name;
}

bool Game::InitUserInfo()
{
	//디폴트 유저 정보 텍스트 파일 읽어올 때 숫자가 의미하는 순서
	//공격력 최대생명력 렙업하기위한경험치 현재경험치 레벨 소지골드
	//코드에서 추가로 설정해줘야 하는 변수 현재경험치 몹한테 주는 경험치 현재생명력 공방상태
	
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
		m_iUserGetExp = 5;
		m_bUserStance = STANCE_DEFENCE;
		return true;
	}
	else
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

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

bool Game::InitMonsterInfo()
{
	//디폴트 몹 정보 텍스트 파일 읽어올 때 숫자가 의미하는 순서
	//몹이름 공격력 생명력 렙업하기위한경험치 주는경험치 레벨 주는 골드
	//코드에서 추가로 설정해줘야 하는 변수 현재경험치 몹한테 주는 경험치 현재생명력 공방상태
	//디폴트 파일에 딜레이 추가해줘야 함 추가하면 이 주석 지우셈
	
	ifstream MonsterInfoLoad;
	MonsterInfoLoad.open("DefaultMonsterInfo.txt");
	if (MonsterInfoLoad.is_open())
	{
		int i;
		MonsterInfoLoad >> i;
		MonsterArr = new Monster[i];

		int j = 0;

		while (!MonsterInfoLoad.eof())
		{

		}
	}
	else
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		RED
		gotoxy(26, 14);
		cout << "에러 발생";
		gotoxy(7, 16);
		cout << "몬스터 정보 텍스트 파일을 읽어올 수 없습니다...";
		ORIGINAL

			system("pause>null");
		return false;	//디폴트 유저 파일이 없을 경우 에러임을 표시하고 메인 화면으로 돌아간다
	}
}

//여기까지 인포 데이터 불러오기 영역

void Game::TownMenu()
{
	int iSelect;

	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		BLUE_GREEN
		gotoxy(23, 8);
		cout << "==== 마을 ====";
		ORIGINAL

		gotoxy(26, 11);
		cout << "던전 입구";
		gotoxy(26, 13);
		cout << "유저 정보";
		gotoxy(25, 15);
		cout << "몬스터 정보";
		gotoxy(26, 17);
		cout << "무기 상점";
		gotoxy(26, 19);
		cout << "저장한다";
		gotoxy(28, 21);
		cout << "종료";

		iSelect = GameMap.MenuSelectCursor(6, 2, 10, 11);

		switch (iSelect)
		{
		default:
			cout << "댕";
			break;
		case 1:
			NowBattle();
			break;
		case 2:
			ShowUserInfo();
			break;
		case 6:
			return;
		}
	}
}

//배틀 관련 함수 시작

void Game::NowBattle()
{
	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		ShowUserBattle();
		ShowMonsterBattle();

		gotoxy(26, 14);
		YELLOW
			cout << "너";
		ORIGINAL

		gotoxy(34, 14);
		cout << "몹";

		gotoxy(18, 16);
		cout << "시스템: 자폭하려면 아무키 ㄱㄱ";

		gotoxy(22, 17);
		cout << "태세 전환: SPACE키";

		if (_kbhit())
		{
			if (_getch() == KEYBOARD_SPACE)
			{
				//스페이스바 입력 받았을 경우 공방 전환
				if (m_bUserStance == STANCE_ATTACK)
					m_bUserStance = STANCE_DEFENCE;
				else
					m_bUserStance = STANCE_ATTACK;
			}
			else
				m_iUserCurrentLife = 0;	//이거는 사망 이벤트 확인을 위한 테스트용 코드입니다 실전시 삭제요망
		}

		if (m_iUserCurrentLife == 0)
		{
			//유저의 체력이 다할 경우 유저 사망
			gotoxy(26, 14);
			BLOOD
				cout << "너";
			ORIGINAL
			system("pause>null");

			m_iUserCurrentLife = m_iUserMaxLife;
			return;
		}

		Sleep(1000);
	}
}

void Game::ShowUserBattle()
{
	YELLOW
		gotoxy(18, 2);
	cout << "=======당신의 정보=======";
	ORIGINAL

	gotoxy(19, 3);
	cout << "이름: " << m_sUserName;
	gotoxy(19, 4);
	cout << "레벨: " << m_iUserLevel;
	gotoxy(19, 5);
	cout << "생명력: " << m_iUserCurrentLife << "/" << m_iUserMaxLife;
	gotoxy(19, 6);
	cout << "공격력: " << m_iUserAttack;
	gotoxy(19, 7);
	cout << "경험치: " << m_iUserCurrentExp << "/" << m_iUserMaxExp;
	gotoxy(19, 8);
	cout << "소지 골드: " << m_iUserGold;
	gotoxy(19, 9);
	cout << "현재 상태: ";
	if (m_bUserStance == STANCE_ATTACK)
		cout << "공격";
	else
		cout << "방어";
}

void Game::ShowMonsterBattle()
{
	gotoxy(18, 20);
	cout << "=======테스트 텍스트 출력=======";

	gotoxy(19, 21);
	cout << "이름: 테스트";
	gotoxy(19, 22);
	cout << "레벨: 테스트";
	gotoxy(19, 23);
	cout << "생명력: 테스트";
	gotoxy(19, 24);
	cout << "공격력: 테스트";
	gotoxy(19, 25);
	cout << "경험치: 테스트";
	gotoxy(19, 26);
	cout << "소지 골드: 테스트";
	gotoxy(19, 27);
	cout << "현재 상태: ";
	if (m_bUserStance == STANCE_ATTACK)
		cout << "공격";
	else
		cout << "방어";
}

//배틀 관련 함수 종료

void Game::ShowUserInfo()
{
	GameMap.BoxErase(WIDTH, HEIGHT);
	
	YELLOW
	gotoxy(18, 10);
	cout << "=======당신의 정보=======";
	ORIGINAL

	gotoxy(19, 13);
	cout << "이름: " << m_sUserName;
	gotoxy(19, 14);
	cout << "레벨: " << m_iUserLevel;
	gotoxy(19, 15);
	cout << "생명력: " << m_iUserCurrentLife << "/" << m_iUserMaxLife;
	gotoxy(19, 16);
	cout << "공격력: " << m_iUserAttack;
	gotoxy(19, 17);
	cout << "경험치: " << m_iUserCurrentExp << "/" << m_iUserMaxExp;
	gotoxy(19, 18);
	cout << "소지 골드: " << m_iUserGold;

	system("pause>null");
}

void Game::DeleteInfo()
{
	//정보들 싹다 죽엇어

}

Game::~Game()
{
}
