#include "Game.h"
#define ROCK 1
#define SCISSORS 2
#define PAPER 3
#define OBJECT_Y 13
#define USER_ATTACK 10
#define MONSTER_ATTACK 11
#define WEAPON_OK 1
#define WEAPON_NO 0	//무기 갖고 있으면 1 아님 0
#define CLOSE -10	//무기 상점 탭 닫기

//몹 레벨업 시스템 제거 대신에 패배로 전투 종료시 몹 HP 풀 회복 및 골드 삥 뜯김
//해야 하는 거: 유저 데이터를 다른 클래스로 분리
//메모리 누수 잡았다

//디폴트 유저 파일과 초기화 하는 유저 파일 함수 구분해서 새로 만들 것

//4월 7일 추가한 점: 객체 포인터가 남발되는 경향이 있어 유저는 정적으로 불러옴, 인벤토리 기능 구현

Game::Game()
{
	
}

void Game::GetName(string name)
{
	Player.InitUserData();
	Player.ChangeName(name);
}

bool Game::LoadDefaultUserData()
{
	bool bIsOpen = Player.LoadDefaultUserData();

	if (bIsOpen == false)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		RED
			gotoxy(26, 14);
		cout << "에러 발생";
		gotoxy(6, 16);
		cout << "플레이어 정보 텍스트 파일을 읽어올 수 없습니다...";
		ORIGINAL

		system("pause>null");
	}

	return bIsOpen;
}

bool Game::InitMonsterData()
{
	//맨 위의 숫자는 등장하는 몬스터의 총 수
	//디폴트 몹 정보 텍스트 파일 읽어올 때 숫자가 의미하는 순서
	//몹이름, 공격력, 생명력, 렙업 하기 위한 경험치, 주는 경험치, 레벨, 주는 골드
	//코드에서 추가로 설정해줘야 하는 변수 현재경험치 몹한테 주는 경험치 현재생명력
	
	ifstream MonsterInfoLoad;
	MonsterInfoLoad.open("DefaultMonsterInfo.txt");
	if (MonsterInfoLoad.is_open())
	{
		MonsterInfoLoad >> m_iMonsterPopulation;
		MonsterArr = new Monster[m_iMonsterPopulation];

		int j = 0;

		while (!MonsterInfoLoad.eof())
		{
			MonsterInfoLoad >> MonsterArr[j].MonsterName;
			MonsterInfoLoad >> MonsterArr[j].MonsterAttck;
			MonsterInfoLoad >> MonsterArr[j].MonsterMaxLife;
			MonsterInfoLoad >> MonsterArr[j].MonsterMaxExp;
			MonsterInfoLoad >> MonsterArr[j].MonsterDropExp;
			MonsterInfoLoad >> MonsterArr[j].MonsterLevel;
			MonsterInfoLoad >> MonsterArr[j].MonsterDropGold;
			MonsterArr[j].MonsterCurrentExp = 0;
			MonsterArr[j].MonsterCurrentLife = MonsterArr[j].MonsterMaxLife;
			j++;
		}

		return true;
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
		return false;	//디폴트 몬스터 파일이 없을 경우 에러임을 표시하고 메인 화면으로 돌아간다
	}
}

bool Game::InitWeaponData()
{
	WeaponPtr = new Weapon;
	SwordPtr = new Sword;
	BowPtr = new Bow;
	DaggerPtr = new Dagger;
	GunPtr = new Gun;
	WandPtr = new Wand;
	HammerPtr = new Hammer;

	if ((WeaponPtr->InitWeaponCount()) == false)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		RED
		gotoxy(26, 14);
		cout << "에러 발생";
		gotoxy(8, 16);
		cout << "무기 정보 텍스트 파일을 읽어올 수 없습니다...";
		ORIGINAL

		system("pause>null");

		return false;
	}
	else
	{
		//정상적으로 파일을 읽었다면 각 무기 개수가 몇개인지 카운트 되어있음
		//작동 순서: 무기 배열 생성 함수->무기 배열에 지역 변수를 매개 변수로 넣어서 데이터 입력
		SwordPtr->CreateSwordArr();
		BowPtr->CreateBowArr();
		DaggerPtr->CreateDaggerArr();
		GunPtr->CreateGunArr();
		WandPtr->CreateWandArr();
		HammerPtr->CreateHammerArr();

		ifstream WeaponLoad;
		WeaponLoad.open("WeaponList.txt");
		if (WeaponLoad.is_open())
		{
			string sWeaponType;
			string sWeaponName;
			int iWeaponPrice;
			int iWeaponPower;

			while (!WeaponLoad.eof())
			{
				WeaponLoad >> sWeaponType;

				if (sWeaponType == "Sword")
				{
					WeaponLoad >> sWeaponName;
					WeaponLoad >> iWeaponPower;
					WeaponLoad >> iWeaponPrice;
					SwordPtr->InputSwordData(sWeaponName, iWeaponPrice, iWeaponPower);
				}
				else if (sWeaponType == "Bow")
				{
					WeaponLoad >> sWeaponName;
					WeaponLoad >> iWeaponPower;
					WeaponLoad >> iWeaponPrice;
					BowPtr->InputBowData(sWeaponName, iWeaponPrice, iWeaponPower);
				}
				else if (sWeaponType == "Dagger")
				{
					WeaponLoad >> sWeaponName;
					WeaponLoad >> iWeaponPower;
					WeaponLoad >> iWeaponPrice;
					DaggerPtr->InputDaggerData(sWeaponName, iWeaponPrice, iWeaponPower);
				}
				else if (sWeaponType == "Gun")
				{
					WeaponLoad >> sWeaponName;
					WeaponLoad >> iWeaponPower;
					WeaponLoad >> iWeaponPrice;
					GunPtr->InputGunData(sWeaponName, iWeaponPrice, iWeaponPower);
				}
				else if (sWeaponType == "Wand")
				{
					WeaponLoad >> sWeaponName;
					WeaponLoad >> iWeaponPower;
					WeaponLoad >> iWeaponPrice;
					WandPtr->InputWandData(sWeaponName, iWeaponPrice, iWeaponPower);
				}
				else if (sWeaponType == "Hammer")
				{
					WeaponLoad >> sWeaponName;
					WeaponLoad >> iWeaponPower;
					WeaponLoad >> iWeaponPrice;
					HammerPtr->InputHammerData(sWeaponName, iWeaponPrice, iWeaponPower);
				}
			}
		}

		return true;
	}
}

void Game::InitInventory()
{
	MainInventory = new Bag("메인 인벤토리");

	DaggerBag = new Bag("단검 가방");
	GunBag = new Bag("총 가방");
	SwordBag = new Bag("칼 가방");
	WandBag = new Bag("원드 가방");
	BowBag = new Bag("활 가방");
	HammerBag = new Bag("둔기 가방");

	MainInventory->AddInventory(DaggerBag);
	MainInventory->AddInventory(GunBag);
	MainInventory->AddInventory(SwordBag);
	MainInventory->AddInventory(WandBag);
	MainInventory->AddInventory(BowBag);
	MainInventory->AddInventory(HammerBag);
}

//여기까지 디폴트 인포 데이터 불러오기 영역

bool Game::LoadUserData(int DataNumber)
{
	//변수 순서->유저 이름, 공격력, 최대 생명력, 렙업하기 위한 경험치, 레벨, 골드, 현재 경험치, 현재 생명력
	//다음 줄은 무기 여부 무기 있으면 1 무기 타입, 무기 이름, 공격력, 가격 / 없으면 0
	Player.InitUserData();

	bool bIsOpen = Player.LoadUserData(DataNumber);

	if (bIsOpen == false)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		RED
			gotoxy(26, 14);
		cout << "에러 발생";
		gotoxy(6, 16);
		cout << "플레이어 정보 텍스트 파일을 읽어올 수 없습니다...";
		ORIGINAL

			system("pause>null");
	}

	return bIsOpen;
}

//아래부터 게임 메뉴 시작

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
			break;
		case 1:
			DungeonList();
			break;
		case 2:
			ShowUserInfo();
			break;
		case 3:
			ShowMonsterInfo();
			break;
		case 4:
			WeaponShop();
			break;
		case 5:
			SaveMenu();
			break;
		case 6:
			DeleteInfo();
			return;
		}
	}
}

void Game::DungeonList()
{
	int iSelect;
	int iSumMenuNum = m_iMonsterPopulation + 1;

	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);
		
		PUPPLE
		gotoxy(20, 7);
		cout << "=====층별 안내=====";

		int i = 10;
		for (int j = 0; j < m_iMonsterPopulation; j++)
		{
			gotoxy(22, i);
			cout << (j + 1) << "층: " << MonsterArr[j].MonsterName;
			i += 2;
		}

		gotoxy(22, i);
		cout << "마을로 돌아간다";

		ORIGINAL

		iSelect = GameMap.MenuSelectCursor(iSumMenuNum, 2, 7, 10);

		if (iSelect == iSumMenuNum)
			return;
		else
		{
			NowBattle(iSelect - 1);
			break;
		}
	}
}

//배틀 관련 함수 시작

void Game::NowBattle(int MonsterNumber)
{
	char iGetKey = 0;	//getch()용
	int iMonsterCard;	//몹이 뭐 냈는지 저장용

	GameMap.BoxErase(WIDTH, HEIGHT);

	ShowUserBattle();
	ShowMonsterBattle(MonsterNumber);

	PrintObject();

	//가위: A    바위: S     보: D

	while (1)
	{
		if (iGetKey == 0)
			iGetKey = _getch();	//최초 입력

		iMonsterCard = (rand() % 3) + 1;

		if (iGetKey == 'S' || iGetKey == 's')
		{
			if (iMonsterCard == ROCK)
				PrintMessage(OUTCOME_DRAW, MonsterNumber);
			else if (iMonsterCard == SCISSORS)
				PrintMessage(OUTCOME_WIN, MonsterNumber);
			else
				PrintMessage(OUTCOME_LOSE, MonsterNumber);

			gotoxy(24, OBJECT_Y - 1);
			cout << "바위";
		}
		else if (iGetKey == 'A' || iGetKey == 'a')
		{
			if (iMonsterCard == SCISSORS)
				PrintMessage(OUTCOME_DRAW, MonsterNumber);
			else if (iMonsterCard == PAPER)
				PrintMessage(OUTCOME_WIN, MonsterNumber);
			else
				PrintMessage(OUTCOME_LOSE, MonsterNumber);

			gotoxy(24, OBJECT_Y - 1);
			cout << "가위";
		}
		else if (iGetKey == 'D' || iGetKey == 'd')
		{
			if (iMonsterCard == PAPER)
				PrintMessage(OUTCOME_DRAW, MonsterNumber);
			else if (iMonsterCard == ROCK)
				PrintMessage(OUTCOME_WIN, MonsterNumber);
			else
				PrintMessage(OUTCOME_LOSE, MonsterNumber);

			gotoxy(25, OBJECT_Y - 1);
			cout << "보";
		}
		else
		{
			GameMap.BoxErase(WIDTH, HEIGHT);

			ShowUserBattle();
			ShowMonsterBattle(MonsterNumber);

			PrintObject();

			gotoxy(23, 16);
			cout << "몹: 집중 안 하냐?";
			gotoxy(20, 17);
			cout << "몬스터에게 한대 맞았다...";

			Attack(MONSTER_ATTACK, MonsterNumber);
			//지정된 키 이외를 입력하면 한대 맞음
		}

		ShowUserBattle();
		ShowMonsterBattle(MonsterNumber);

		//아래 if문은 몬스터가 낸 패가 무엇인지 출력
		if (iMonsterCard == ROCK)
		{
			gotoxy(34, OBJECT_Y - 1);
			cout << "바위";
		}
		else if (iMonsterCard == SCISSORS)
		{
			gotoxy(34, OBJECT_Y - 1);
			cout << "가위";
		}
		else
		{
			gotoxy(35, OBJECT_Y - 1);
			cout << "보";
		}

		//승리 조건식
		if (MonsterArr[MonsterNumber].MonsterCurrentLife == 0)
		{
			BLOOD
			gotoxy(35, OBJECT_Y);
			cout << "몹";
			ORIGINAL

			gotoxy(22, 17);
			cout << "전투에서 승리했다.";
			system("pause>null");

			ShowResult(MonsterNumber);

			return;
		}

		//패배 조건식
		if (Player.ReturnUserInt(VARIABLE_CURRENTLIFE) == 0)
		{
			gotoxy(25, OBJECT_Y);
			BLOOD
			cout << "너";
			gotoxy(8, 17);
			cout << "전투에서 패배했다. 당신은 눈 앞이 깜깜해졌다...";
			gotoxy(20, 18);
			cout << "가진 돈 일부를 빼앗겼다.";
			ORIGINAL

			system("pause>null");

			MonsterArr[MonsterNumber].MonsterCurrentLife = MonsterArr[MonsterNumber].MonsterMaxLife;
			
			Player.ForFeitGold();
			Player.LifeReset();

			return;
		}

		iGetKey = _getch();
	}
}

void Game::PrintObject()
{
	gotoxy(25, OBJECT_Y);
	YELLOW
	cout << "너";
	ORIGINAL

	PUPPLE
	gotoxy(35, OBJECT_Y);
	cout << "몹";
	ORIGINAL

	gotoxy(27, 15);
	cout << "<시스템>";

	gotoxy(16, 19);
	cout << "가위: A    바위: S     보: D";
}

void Game::PrintMessage(int Outcome, int MonsterNumber)
{
	GameMap.BoxErase(WIDTH, HEIGHT);

	PrintObject();

	switch (Outcome)
	{
	case OUTCOME_DRAW:
		gotoxy(28, 16);
		cout << "비겼다";
		break;
	case OUTCOME_LOSE:
		gotoxy(24, 16);
		cout << "몬스터의 승리";
		Attack(MONSTER_ATTACK, MonsterNumber);
		break;
	case OUTCOME_WIN:
		gotoxy(25, 16);
		cout << "당신의 승리";
		Attack(USER_ATTACK, MonsterNumber);
		break;
	}
}

void Game::Attack(int Attacker, int MonsterNumber)
{
	if (Attacker == USER_ATTACK)
	{
		int iAttackSum;	//무기 공격력과 기존 공격력을 합한 것

		if (Player.ReturnUserInt(VARIABLE_HAVEWEAPON) == WEAPON_OK)
		{
			iAttackSum = Player.ReturnUserInt(VARIABLE_ATTACK) + GetWeaponPower();
		}
		else
			iAttackSum = Player.ReturnUserInt(VARIABLE_ATTACK);

		if (MonsterArr[MonsterNumber].MonsterCurrentLife - iAttackSum >= 0)
			MonsterArr[MonsterNumber].MonsterCurrentLife = MonsterArr[MonsterNumber].MonsterCurrentLife - iAttackSum;
		else
			MonsterArr[MonsterNumber].MonsterCurrentLife = 0;
	}
	else if (Attacker == MONSTER_ATTACK)
	{
		Player.LifeDamaged(MonsterArr[MonsterNumber].MonsterAttck);
	}
}

void Game::ShowUserBattle()
{
	//아래 마을에서 보여지는 유저 정보와는 다른 인터페이스라 그냥 분리함
	YELLOW
	gotoxy(19, 2);
	cout << "=======당신의 정보=======";
	ORIGINAL

	gotoxy(15, 4);
	cout << "이름: "; Player.ReturnUserName();
	gotoxy(34, 4);
	cout << "레벨: " << Player.ReturnUserInt(VARIABLE_LEVEL);
	gotoxy(15, 5);
	cout << "생명력: " << Player.ReturnUserInt(VARIABLE_CURRENTLIFE) << "/" << Player.ReturnUserInt(VARIABLE_MAXLIFE);
	gotoxy(34, 5);
	if (Player.ReturnUserInt(VARIABLE_HAVEWEAPON) == WEAPON_OK)
	{
		cout << "공격력: " << Player.ReturnUserInt(VARIABLE_ATTACK) << " + " << GetWeaponPower();
	}
	else
	{
		cout << "공격력: " << Player.ReturnUserInt(VARIABLE_ATTACK);
	}
	gotoxy(15, 6);
	cout << "경험치: " << Player.ReturnUserInt(VARIABLE_CURRENTEXP) << "/" << Player.ReturnUserInt(VARIABLE_MAXEXP);
	gotoxy(34, 6);
	cout << "소지 골드: " << Player.ReturnUserInt(VARIABLE_GOLD);
}

void Game::ShowMonsterBattle(int MonsterNumber)
{
	gotoxy(19, 22);
	cout << "=======몬스터 정보=======";

	gotoxy(15, 24);
	cout << "이름: " << MonsterArr[MonsterNumber].MonsterName;
	gotoxy(34, 24);
	cout << "레벨: " << MonsterArr[MonsterNumber].MonsterLevel;
	gotoxy(15, 25);
	cout << "생명력: " << MonsterArr[MonsterNumber].MonsterCurrentLife << "/" << MonsterArr[MonsterNumber].MonsterMaxLife;
	gotoxy(34, 25);
	cout << "공격력: " << MonsterArr[MonsterNumber].MonsterAttck;
	gotoxy(15, 26);
	cout << "경험치: " << MonsterArr[MonsterNumber].MonsterCurrentExp << "/" << MonsterArr[MonsterNumber].MonsterMaxExp;
	gotoxy(34, 26);
	cout << "획득 골드: " << MonsterArr[MonsterNumber].MonsterDropGold;
}

void Game::ShowResult(int MonsterNumber)
{
	GameMap.BoxErase(WIDTH, HEIGHT);

	GOLD
	gotoxy(21, 13);
	cout << MonsterArr[MonsterNumber].MonsterName << " 토벌 성공!";

	gotoxy(23, 15);
	cout << "획득 경험치: " << MonsterArr[MonsterNumber].MonsterDropExp;

	gotoxy(24, 17);
	cout << "획득 골드: " << MonsterArr[MonsterNumber].MonsterDropGold;
	ORIGINAL

	bool bIsLevelUp = Player.AcquireReward(MonsterArr[MonsterNumber].MonsterDropExp, MonsterArr[MonsterNumber].MonsterDropGold);
	
	system("pause>null");

	if (bIsLevelUp == true)
	{
		//유저 레벨업
		GameMap.BoxErase(WIDTH, HEIGHT);

		int iIncreaseAttack;
		int iIncreaseLife;

		Player.LevelUp(&iIncreaseAttack, &iIncreaseLife);

		GREEN
		gotoxy(21, 13);
		cout << Player.ReturnUserInt(VARIABLE_LEVEL) << "레벨로 레벨 업 했다";
		gotoxy(24, 15);
		cout << "공격력 " << iIncreaseAttack << " 증가";
		gotoxy(21, 17);
		cout << "최대 생명력 " << iIncreaseLife << " 증가";
		ORIGINAL

		system("pause>null");
	}

	MonsterArr[MonsterNumber].MonsterCurrentLife = MonsterArr[MonsterNumber].MonsterMaxLife;
}

//배틀 관련 함수 종료

void Game::ShowUserInfo()
{
	int iSelect;

	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);
		int iXPos = 16;
		int iYPos = 7;

		YELLOW
			gotoxy(18, iYPos);
		cout << "=======당신의 정보=======";
		ORIGINAL

			iYPos += 3;

		gotoxy(iXPos, iYPos);
		cout << "이름: "; Player.ReturnUserName();
		iYPos++;
		gotoxy(iXPos, iYPos);
		cout << "레벨: " << Player.ReturnUserInt(VARIABLE_LEVEL);
		iYPos++;
		gotoxy(iXPos, iYPos);
		cout << "생명력: " << Player.ReturnUserInt(VARIABLE_CURRENTLIFE) << "/" << Player.ReturnUserInt(VARIABLE_MAXLIFE);
		iYPos++;

		gotoxy(iXPos, iYPos);
		if (Player.ReturnUserInt(VARIABLE_HAVEWEAPON) == WEAPON_OK)
		{
			int iWeaponPower = GetWeaponPower();
			cout << "공격력: " << Player.ReturnUserInt(VARIABLE_ATTACK) << " + " << iWeaponPower;
		}
		else
		{
			cout << "공격력: " << Player.ReturnUserInt(VARIABLE_ATTACK);
		}
		iYPos++;

		gotoxy(iXPos, iYPos);
		cout << "경험치: " << Player.ReturnUserInt(VARIABLE_CURRENTEXP) << "/" << Player.ReturnUserInt(VARIABLE_MAXEXP);
		iYPos++;
		gotoxy(iXPos, iYPos);
		cout << "소지 골드: " << Player.ReturnUserInt(VARIABLE_GOLD);
		iYPos++;

		gotoxy(iXPos, iYPos);
		int iWeaponType = Player.ReturnUserInt(VARIABLE_WEAPONTYPE);
		cout << "장착 중인 무기: ";

		if (Player.ReturnUserInt(VARIABLE_HAVEWEAPON) == WEAPON_OK)
		{
			GetWeaponName(Player.ReturnUserInt(VARIABLE_WEAPONTYPE), Player.ReturnUserInt(VARIABLE_WEAPONINDEX));
		}
		else
			cout << "없음";

		iYPos += 3;

		gotoxy(iXPos, iYPos);
		cout << "인벤토리 열기";
		iYPos += 2;

		gotoxy(iXPos, iYPos);
		cout << "마을로 돌아간다";

		iSelect = GameMap.MenuSelectCursor(2, 2, 5, iYPos - 2);
		
		switch (iSelect)
		{
		case 1:
			ShowInventory();
			break;
		case 2:
			return;
		}
	}
}

//인벤 보여주는 함수
void Game::ShowInventory()
{
	int iTmpType, iTmpIndex;
	int iSelect;

	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		YELLOW
		gotoxy(20, 7);
		cout << "=======인벤토리=======";
		ORIGINAL


		gotoxy(18, 10);
		cout << "1. 단검";
		
		gotoxy(18, 12);
		cout << "2. 총";

		gotoxy(18, 14);
		cout << "3. 칼";

		gotoxy(18, 16);
		cout << "4. 원드";

		gotoxy(18, 18);
		cout << "5. 활";

		gotoxy(18, 20);
		cout << "6. 둔기";

		gotoxy(26, 22);
		cout << "돌아간다";

		iSelect = GameMap.MenuSelectCursor(7, 2, 7, 10);

		switch (iSelect)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
			ShowInvenotryTap(iSelect);
			break;
		break;
		case 7:
			return;
		}
		

		//아래가 기존 함수 파트...	
		/*int iYPos = 10;
		for (int i = 0; i <= 4; i++)
		{
			gotoxy(18, iYPos);
			Player.ReturnInventoryArr(iTmpType, iTmpIndex, i);
			cout << i + 1 << ". ";
			GetWeaponName(iTmpType, iTmpIndex);
			iYPos += 2;
		}

		gotoxy(26, iYPos);
		cout << "돌아간다";

		iSelect = GameMap.MenuSelectCursor(6, 2, 7, 10);

		switch (iSelect)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		{
			if (Player.EquipWeaopn(iSelect) == false)
			{
				GameMap.BoxErase(WIDTH, HEIGHT);
				gotoxy(13, 14);
				YELLOW
				cout << "해당 인벤토리 슬롯에 무기가 없습니다.";
				ORIGINAL
				system("pause>null");
				break;
			}
			GameMap.BoxErase(WIDTH, HEIGHT);
			gotoxy(24, 14);
			YELLOW
			cout << "무기 장착 완료";
			ORIGINAL
			Sleep(1000);
		}
			break;
		case 6:
			return;
		}*/
	}
}

void Game::ShowInvenotryTap(int WeaponType)
{
	int iSelect;
	string sTemporaryString;	//무기 이름 받아오는 용도
	int iTemporaryIndex;	//무기 인덱스 받아오는 용도 선택시 해당 번호로 찾아가서 인덱스를 받아온다

	Inventory *BagTmp = new Bag;


	//생각해보니 해당 배열에 제대로 템이 들어가있는지 아니면 null인지 체크하는 것도 필요한 듯

	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		gotoxy(15, 8);

		switch (WeaponType)	//탭 이름 출력
		{
		case TYPE_DAGGER:
			sTemporaryString = "=====소지 중인 단검=====";
			BagTmp = DaggerBag;
			break;
		case TYPE_GUN:
			sTemporaryString = "=====소지 중인 총=====";
			BagTmp = GunBag;
			break;
		case TYPE_WAND:
			sTemporaryString = "=====소지 중인 원드=====";
			BagTmp = WandBag;
			break;
		case TYPE_SWORD:
			sTemporaryString = "=====소지 중인 칼=====";
			BagTmp = SwordBag;
			break;
		case TYPE_HAMMER:
			sTemporaryString = "=====소지 중인 둔기=====";
			BagTmp = HammerBag;
			break;
		case TYPE_BOW:
			sTemporaryString = "=====소지 중인 활=====";
			BagTmp = BowBag;
			break;
		}

		gotoxy(WIDTH - (sTemporaryString.length() / 2), 8);
		cout << sTemporaryString;

	
		//아래부터 무기 이름 출력

		for (int i = 1; i <= ITEM_LIMIT; i++)
		{
			if (i <= BagTmp->ReturnItemCount())
			{
				sTemporaryString = BagTmp->ReturnItemName(i);

				gotoxy(WIDTH - (sTemporaryString.length() / 2), 8 + (i * 2));
				cout << sTemporaryString;
			}
			else
			{
				gotoxy(28, 8 + (i * 2));
				cout << "없음";
			}
		}

		gotoxy(26, 20);
		cout << "돌아간다";
		
		iSelect = GameMap.MenuSelectCursor(6, 2, 10, 10);

		switch (iSelect)
		{
		default:
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		{
			if (iSelect > BagTmp->ReturnItemCount())
			{
				GameMap.BoxErase(WIDTH, HEIGHT);
				gotoxy(13, 14);
				YELLOW
				cout << "해당 인벤토리 슬롯에 무기가 없습니다.";
				ORIGINAL
				system("pause>null");
				break;
			}
			Player.EquipWeapon(MainInventory[WeaponType - 1].ReturnWeaponIndex(iSelect - 1), WeaponType);
			GameMap.BoxErase(WIDTH, HEIGHT);
			gotoxy(24, 14);
			YELLOW
			cout << "무기 장착 완료";
			ORIGINAL
			Sleep(1000);
		}
		case 6:
			return;
		}
	}
}

void Game::GetWeaponName(int iWeaponType, int iWeaponIndex)
{
	string sWeaponName;

	switch (iWeaponType)
	{
	case TYPE_DAGGER:
		sWeaponName = DaggerPtr->ReturnDaggerName(iWeaponIndex) + "(단검)";
		break;
	case TYPE_GUN:
		sWeaponName = GunPtr->ReturnGunName(iWeaponIndex) + "(총)";
		break;
	case TYPE_WAND:
		sWeaponName = WandPtr->ReturnWandName(iWeaponIndex) + "(원드)";
		break;
	case TYPE_SWORD:
		sWeaponName = SwordPtr->ReturnSwordName(iWeaponIndex) + "(칼)";
		break;
	case TYPE_HAMMER:
		sWeaponName = HammerPtr->ReturnHammerName(iWeaponIndex) + "(둔기)";
		break;
	case TYPE_BOW:
		sWeaponName = BowPtr->ReturnBowName(iWeaponIndex) + "(활)";
		break;
	case BLANK:
		sWeaponName = "없음";
		break;
	}

	cout << sWeaponName;
}

int Game::GetWeaponPower()
{
	int iWeaponType = Player.ReturnUserInt(VARIABLE_WEAPONTYPE);
	int iWeaponIndex = Player.ReturnUserInt(VARIABLE_WEAPONINDEX);

	if (iWeaponType == TYPE_DAGGER)
		return DaggerPtr->ReturnDaggerPower(iWeaponIndex);
	else if (iWeaponType == TYPE_GUN)
		return GunPtr->ReturnGunPower(iWeaponIndex);
	else if (iWeaponType == TYPE_WAND)
		return WandPtr->ReturnWandPower(iWeaponIndex);
	else if (iWeaponType == TYPE_SWORD)
		return SwordPtr->ReturnSwordPower(iWeaponIndex);
	else if (iWeaponType == TYPE_HAMMER)
		return HammerPtr->ReturnHammerPower(iWeaponIndex);
	else
		return BowPtr->ReturnBowPower(iWeaponIndex);
}

void Game::ShowMonsterInfo()
{
	GameMap.BoxErase(WIDTH, HEIGHT);

	int i = 3;

	for (int j = 0; j < m_iMonsterPopulation; j++)
	{
		gotoxy(20, i);
		cout << "=====" << MonsterArr[j].MonsterName << "(" << MonsterArr[j].MonsterLevel << "Lv)=====";
		i++;

		gotoxy(14, i);
		cout << "공격력: " << MonsterArr[j].MonsterAttck;
		gotoxy(34, i);
		cout << "생명력: " << MonsterArr[j].MonsterCurrentLife << "/" << MonsterArr[j].MonsterMaxLife;
		i++;
		gotoxy(14, i);
		cout << "경험치: " << MonsterArr[j].MonsterCurrentExp << "/" << MonsterArr[j].MonsterMaxExp;
		gotoxy(34, i);
		cout << "획득 경험치: " << MonsterArr[j].MonsterDropExp;
		i++;
		gotoxy(14, i);
		cout << "획득 골드: " << MonsterArr[j].MonsterDropGold;
		i++;
	}
	
	system("pause>null");
}

//인포 관련 함수 종료

void Game::WeaponShop()
{
	int iSelect;

	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		gotoxy(24, 6);
		GREEN
		cout << "◆무기 상점◆";
		ORIGINAL

		gotoxy(27, 9);
		cout << "→단검";
		gotoxy(28, 11);
		cout << "→총";
		gotoxy(28, 13);
		cout << "→칼";
		gotoxy(27, 15);
		cout << "→원드";
		gotoxy(28, 17);
		cout << "→활";
		gotoxy(27, 19);
		cout << "→둔기";
		gotoxy(23, 21);
		cout << "마을로 돌아간다";

		iSelect = GameMap.MenuSelectCursor(7, 2, 9, 9);

		int iBuyOrNot;
		int iGesture = NULL;

		int iGetWeaponIndex = 0;
		int iGetWeaponType = 0;	//Weapon.cpp에서 무기 인덱스와 타입을 가져올 놈들

		int iUserGold = Player.ReturnUserInt(VARIABLE_GOLD);	//가독성을 높이기 위해 지역 변수 만들어서 대입

		while (iGesture != CLOSE)
		{
			switch (iSelect)
			{
			case 1:
				iBuyOrNot = DaggerPtr->PrintDaggerList(iUserGold, &iGetWeaponType, &iGetWeaponIndex);
				iGesture = BuyScript(iBuyOrNot, iGetWeaponType, iGetWeaponIndex);
				if (iGesture == PAGE_NEXT)
					iSelect = 2;
				else if (iGesture == PAGE_PREVIOUS)
					iSelect = 6;
				break;
			case 2:
				iBuyOrNot = GunPtr->PrintGunList(iUserGold, &iGetWeaponType, &iGetWeaponIndex);
				iGesture = BuyScript(iBuyOrNot, iGetWeaponType, iGetWeaponIndex);
				if (iGesture == PAGE_NEXT)
					iSelect = 3;
				else if (iGesture == PAGE_PREVIOUS)
					iSelect = 1;
				break;
			case 3:
				iBuyOrNot = SwordPtr->PrintSwordList(iUserGold, &iGetWeaponType, &iGetWeaponIndex);
				iGesture = BuyScript(iBuyOrNot, iGetWeaponType, iGetWeaponIndex);
				if (iGesture == PAGE_NEXT)
					iSelect = 4;
				else if (iGesture == PAGE_PREVIOUS)
					iSelect = 2;
				break;
			case 4:
				iBuyOrNot = WandPtr->PrintWandList(iUserGold, &iGetWeaponType, &iGetWeaponIndex);
				iGesture = BuyScript(iBuyOrNot, iGetWeaponType, iGetWeaponIndex);
				if (iGesture == PAGE_NEXT)
					iSelect = 5;
				else if (iGesture == PAGE_PREVIOUS)
					iSelect = 3;
				break;
			case 5:
				iBuyOrNot = BowPtr->PrintBowList(iUserGold, &iGetWeaponType, &iGetWeaponIndex);
				iGesture = BuyScript(iBuyOrNot, iGetWeaponType, iGetWeaponIndex);
				if (iGesture == PAGE_NEXT)
					iSelect = 6;
				else if (iGesture == PAGE_PREVIOUS)
					iSelect = 4;
				break;
			case 6:
				iBuyOrNot = HammerPtr->PrintHammerList(iUserGold, &iGetWeaponType, &iGetWeaponIndex);
				iGesture = BuyScript(iBuyOrNot, iGetWeaponType, iGetWeaponIndex);
				if (iGesture == PAGE_NEXT)
					iSelect = 1;
				else if (iGesture == PAGE_PREVIOUS)
					iSelect = 5;
				break;
			case 7:
				return;
			}
		}
	}
}

int Game::BuyScript(int iBuyOrNot, int iGetWeaponType, int iGetWeaponIndex)
{
	//가게에서 물건 살때 동작... 이전 페이지 다음 페이지 구현을 위해 만들었음
	if (iBuyOrNot == PAGE_NEXT)
		return PAGE_NEXT;
	else if (iBuyOrNot == PAGE_PREVIOUS)
		return PAGE_PREVIOUS;
	else if (iBuyOrNot == 0)	//돌아가기 버튼 눌렀다
		return CLOSE;
	else if (iBuyOrNot == CANNOT_BUY)
	{
		PrintBuyMessage(false);
		return CLOSE;
	}
	else
	{
		//여기 바꿔야 됨 이제 인벤이 플레이어한테 있는 게 아니므로
		if (Player.StockUpWeapon(iGetWeaponType, iGetWeaponIndex) == false)
		{
			GameMap.BoxErase(WIDTH, HEIGHT);
			int iSelect;
			while (1)
			{
				//인벤 다 찼을 때
				YELLOW
				gotoxy(14, 11);
				cout << "인벤토리가 가득 찬 상태입니다.";
				gotoxy(4, 13);
				cout << "소지 중인 무기 하나를 버리고 새로 구매하시겠습니까?";
				ORIGINAL

				gotoxy(29, 16);
				cout << "예";
				gotoxy(27, 18);
				cout << "아니오";

				iSelect = GameMap.MenuSelectCursor(2, 2, 11, 16);

				if (iSelect == 1)
				{
					while (1)
					{
						GameMap.BoxErase(WIDTH, HEIGHT);
						gotoxy(15, 7);
						cout << "버릴 무기를 선택하십시오.";

						int iTmpType, iTmpIndex;

						int iYPos = 10;
						for (int i = 0; i <= 4; i++)
						{
							gotoxy(18, iYPos);
							Player.ReturnInventoryArr(iTmpType, iTmpIndex, i);
							cout << i + 1 << ". ";
							GetWeaponName(iTmpType, iTmpIndex);
							iYPos += 2;
						}

						gotoxy(20, iYPos);
						cout << "버리는 걸 포기한다";

						iSelect = GameMap.MenuSelectCursor(6, 2, 7, 10);

						if (iSelect == 6)
							return CLOSE;
						else
						{
							Player.StockUpWeapon(iGetWeaponType, iGetWeaponIndex, iSelect);
							return CLOSE;
						}
					}
				}
				else
					return CLOSE;
			}
		}
		PrintBuyMessage(true);
		Player.DeductGold(iBuyOrNot);
		
		return CLOSE;
	}
}

void Game::PrintBuyMessage(int YesOrNo)
{
	if (YesOrNo == 1)
	{
		gotoxy(26, 28);
		YELLOW
			cout << "구매 성공";
		ORIGINAL
	}
	else if (YesOrNo == 0)
	{
		gotoxy(17, 28);
		YELLOW
			cout << "소지 중인 골드가 부족합니다.";
		ORIGINAL
	}
	Sleep(1000);

	//아이템 구매 성공 실패 여부에 따라 메시지 출력
}

void Game::SaveMenu()
{
	int iSelect;
	
	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		int iXPos = 19, iYPos = 4;

		for (int i = 1; i <= 10; i++)
		{
			ifstream DataCheck;	//슬롯의 공란 여부
			string sFileName = "SavePlayer" + to_string(i) + ".txt";

			DataCheck.open(sFileName);
			
			gotoxy(iXPos, iYPos);
			
			if (DataCheck.is_open())
				cout << i << "번 슬롯(파일 여부: O)";
			else
				cout << i << "번 슬롯(파일 여부: X)";

			iYPos += 2;

			DataCheck.close();
		}
		
		gotoxy(26, iYPos);
		cout << "돌아간다";

		iSelect = GameMap.MenuSelectCursor(11, 2, 7, 4);

		switch (iSelect)
		{
		default:
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
		{
			GameMap.BoxErase(WIDTH, HEIGHT);
			ifstream DataCheck;	//슬롯의 공란 여부
			string sFileName = "SavePlayer" + to_string(iSelect) + ".txt";
			DataCheck.open(sFileName);
			if (DataCheck.is_open())
			{
				int iAnotherSelect;

				YELLOW
				gotoxy(9,11);
				cout << "이미 해당 슬롯에 데이터가 저장되어 있습니다.";
				gotoxy(22, 13);
				cout << "덮어씌우시겠습니까?";
				ORIGINAL

				gotoxy(29, 16);
				cout << "예";
				gotoxy(27, 18);
				cout << "아니오";

				iAnotherSelect = GameMap.MenuSelectCursor(2, 2, 11, 16);

				if (iAnotherSelect == 1)
				{
					DataCheck.close();
					Player.SaveUserData(iSelect);
				}
				else
					break;
			}
			else
			{
				DataCheck.close();
				Player.SaveUserData(iSelect);
			}
			GameMap.BoxErase(WIDTH, HEIGHT);
			gotoxy(20, 15);
			YELLOW
			cout << "데이터 저장하기 성공";
			ORIGINAL
			Sleep(1000);
			return;
		}
		case 11:
			return;
		}
	}
}

void Game::DeleteInfo()
{
	delete[] MonsterArr;

	delete WeaponPtr;
	delete SwordPtr;
	delete BowPtr;
	delete DaggerPtr;
	delete GunPtr;
	delete WandPtr;
	delete HammerPtr;

	//동적 할당된 놈들 해제
	//동적할당 된 클래스를 동적해제 하면 알아서 소멸자가 호출되기 때문에 굳이 소멸자를 사전에 불러줘야 할 필요가 업엇다
}

Game::~Game()
{
}
