#include "Game.h"
#define ROCK 1
#define SCISSORS 2
#define PAPER 3
#define OBJECT_Y 13
#define USER_ATTACK 10
#define MONSTER_ATTACK 11

//�� ������ �ý��� ���� ��ſ� �й�� ���� ����� �� HP Ǯ ȸ�� �� ��� �� ���

Game::Game()
{
	
}

void Game::GetName(string name)
{
	m_sUserName = name;	//������ ������ �� �޴� Ŭ���� �ʿ��� �̸� �޾ƿ�
}

bool Game::InitUserInfo()
{
	//����Ʈ ���� ���� �ؽ�Ʈ ���� �о�� �� ���ڰ� �ǹ��ϴ� ����
	//���ݷ� �ִ����� �����ϱ����Ѱ���ġ �������ġ ���� �������
	//�ڵ忡�� �߰��� ��������� �ϴ� ���� �������ġ ������ �ִ� ����ġ �������� �������
	
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
		cout << "���� �߻�";
		gotoxy(6, 16);
		cout << "�÷��̾� ���� �ؽ�Ʈ ������ �о�� �� �����ϴ�...";
		ORIGINAL

		system("pause>null");
		return false;	//����Ʈ ���� ������ ���� ��� �������� ǥ���ϰ� ���� ȭ������ ���ư���
	}
}

bool Game::InitMonsterInfo()
{
	//�� ���� ���ڴ� �����ϴ� ������ �� ��
	//����Ʈ �� ���� �ؽ�Ʈ ���� �о�� �� ���ڰ� �ǹ��ϴ� ����
	//���̸�, ���ݷ�, �����, ���� �ϱ� ���� ����ġ, �ִ� ����ġ, ����, �ִ� ���
	//�ڵ忡�� �߰��� ��������� �ϴ� ���� �������ġ ������ �ִ� ����ġ �������� �������
	//����Ʈ ���Ͽ� ������ �߰������ �� �߰��ϸ� �� �ּ� �����
	
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
			MonsterArr[j].Stance = STANCE_DEFENCE;
			j++;
		}

		return true;
	}
	else
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		RED
		gotoxy(26, 14);
		cout << "���� �߻�";
		gotoxy(7, 16);
		cout << "���� ���� �ؽ�Ʈ ������ �о�� �� �����ϴ�...";
		ORIGINAL

		system("pause>null");
		return false;	//����Ʈ ���� ������ ���� ��� �������� ǥ���ϰ� ���� ȭ������ ���ư���
	}
}

//������� ���� ������ �ҷ����� ����

void Game::TownMenu()
{
	int iSelect;
	
	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);
		
		BLUE_GREEN
		gotoxy(23, 8);
		cout << "==== ���� ====";
		ORIGINAL

		gotoxy(26, 11);
		cout << "���� �Ա�";
		gotoxy(26, 13);
		cout << "���� ����";
		gotoxy(25, 15);
		cout << "���� ����";
		gotoxy(26, 17);
		cout << "���� ����";
		gotoxy(26, 19);
		cout << "�����Ѵ�";
		gotoxy(28, 21);
		cout << "����";

		iSelect = GameMap.MenuSelectCursor(6, 2, 10, 11);

		switch (iSelect)
		{
		default:
			cout << "��";
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
		cout << "=====���� �ȳ�=====";

		int i = 10;
		for (int j = 0; j < m_iMonsterPopulation; j++)
		{
			gotoxy(22, i);
			cout << (j + 1) << "��: " << MonsterArr[j].MonsterName;
			i += 2;
		}

		gotoxy(22, i);
		cout << "������ ���ư���";

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

//��Ʋ ���� �Լ� ����

void Game::NowBattle(int MonsterNumber)
{
	char iGetKey = 0;	//getch()��
	int iMonsterCard;	//���� �� �´��� �����

	GameMap.BoxErase(WIDTH, HEIGHT);

	ShowUserBattle();
	ShowMonsterBattle(MonsterNumber);

	PrintObject();

	//����: A    ����: S     ��: D

	while (1)
	{
		if (iGetKey == 0)
			iGetKey = _getch();	//���� �Է�

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
			cout << "����";
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
			cout << "����";
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
			cout << "��";
		}
		else
		{
			GameMap.BoxErase(WIDTH, HEIGHT);

			ShowUserBattle();
			ShowMonsterBattle(MonsterNumber);

			PrintObject();

			gotoxy(23, 16);
			cout << "��: ���� �� �ϳ�?";
			gotoxy(20, 17);
			cout << "���Ϳ��� �Ѵ� �¾Ҵ�...";

			Attack(MONSTER_ATTACK, MonsterNumber);
			//������ Ű �ܸ̿� �Է��ϸ� �Ѵ� ����
		}

		ShowUserBattle();
		ShowMonsterBattle(MonsterNumber);

		//�Ʒ� if���� ���Ͱ� �� �а� �������� ���
		if (iMonsterCard == ROCK)
		{
			gotoxy(34, OBJECT_Y - 1);
			cout << "����";
		}
		else if (iMonsterCard == SCISSORS)
		{
			gotoxy(34, OBJECT_Y - 1);
			cout << "����";
		}
		else
		{
			gotoxy(35, OBJECT_Y - 1);
			cout << "��";
		}

		if (MonsterArr[MonsterNumber].MonsterCurrentLife == 0)
		{
			BLOOD
			gotoxy(35, OBJECT_Y);
			cout << "��";
			ORIGINAL

			gotoxy(22, 17);
			cout << "�������� �¸��ߴ�.";
			system("pause>null");

			ShowResult(MonsterNumber);

			return;
		}

		if (m_iUserCurrentLife == 0)
		{
			//������ ü���� ���� ��� ���� ���
			gotoxy(25, OBJECT_Y);
			BLOOD
			cout << "��";
			gotoxy(8, 17);
			cout << "�������� �й��ߴ�. ����� �� ���� ����������...";
			gotoxy(20, 18);
			cout << "���� �� �Ϻθ� ���Ѱ��.";
			ORIGINAL


			system("pause>null");

			m_iUserCurrentLife = m_iUserMaxLife;
			MonsterArr[MonsterNumber].MonsterCurrentLife = MonsterArr[MonsterNumber].MonsterMaxLife;
			
			if (m_iUserGold > 0)
			{
				double dForfeitGold;	//���� ���
				dForfeitGold = static_cast<double>(m_iUserGold / 10) * 9;
				m_iUserGold -= static_cast<int>(dForfeitGold);	//���� �� 1/10�� �����
			}
				
			return;
		}

		iGetKey = _getch();
	}
}

void Game::PrintObject()
{
	gotoxy(25, OBJECT_Y);
	YELLOW
	cout << "��";
	ORIGINAL

	PUPPLE
	gotoxy(35, OBJECT_Y);
	cout << "��";
	ORIGINAL

	gotoxy(27, 15);
	cout << "<�ý���>";

	gotoxy(16, 19);
	cout << "����: A    ����: S     ��: D";
}

void Game::PrintMessage(int Outcome, int MonsterNumber)
{
	GameMap.BoxErase(WIDTH, HEIGHT);

	PrintObject();

	switch (Outcome)
	{
	case OUTCOME_DRAW:
		gotoxy(28, 16);
		cout << "����";
		break;
	case OUTCOME_LOSE:
		gotoxy(24, 16);
		cout << "������ �¸�";
		Attack(MONSTER_ATTACK, MonsterNumber);
		break;
	case OUTCOME_WIN:
		gotoxy(25, 16);
		cout << "����� �¸�";
		Attack(USER_ATTACK, MonsterNumber);
		break;
	}
}

void Game::Attack(int Attacker, int MonsterNumber)
{
	if (Attacker == USER_ATTACK)
	{
		if (MonsterArr[MonsterNumber].MonsterCurrentLife - m_iUserAttack >= 0)
			MonsterArr[MonsterNumber].MonsterCurrentLife = MonsterArr[MonsterNumber].MonsterCurrentLife - m_iUserAttack;
		else
			MonsterArr[MonsterNumber].MonsterCurrentLife = 0;
	}
	else if (Attacker == MONSTER_ATTACK)
	{
		if (m_iUserCurrentLife - MonsterArr[MonsterNumber].MonsterAttck >= 0)
			m_iUserCurrentLife = m_iUserCurrentLife - MonsterArr[MonsterNumber].MonsterAttck;
		else
			m_iUserCurrentLife = 0;
	}
}

void Game::ShowUserBattle()
{
	YELLOW
	gotoxy(19, 2);
	cout << "=======����� ����=======";
	ORIGINAL

	gotoxy(15, 4);
	cout << "�̸�: " << m_sUserName;
	gotoxy(34, 4);
	cout << "����: " << m_iUserLevel;
	gotoxy(15, 5);
	cout << "�����: " << m_iUserCurrentLife << "/" << m_iUserMaxLife;
	gotoxy(34, 5);
	cout << "���ݷ�: " << m_iUserAttack;
	gotoxy(15, 6);
	cout << "����ġ: " << m_iUserCurrentExp << "/" << m_iUserMaxExp;
	gotoxy(34, 6);
	cout << "���� ���: " << m_iUserGold;
}

void Game::ShowMonsterBattle(int MonsterNumber)
{
	gotoxy(19, 22);
	cout << "=======���� ����=======";

	gotoxy(15, 24);
	cout << "�̸�: " << MonsterArr[MonsterNumber].MonsterName;
	gotoxy(34, 24);
	cout << "����: " << MonsterArr[MonsterNumber].MonsterLevel;
	gotoxy(15, 25);
	cout << "�����: " << MonsterArr[MonsterNumber].MonsterCurrentLife << "/" << MonsterArr[MonsterNumber].MonsterMaxLife;
	gotoxy(34, 25);
	cout << "���ݷ�: " << MonsterArr[MonsterNumber].MonsterAttck;
	gotoxy(15, 26);
	cout << "����ġ: " << MonsterArr[MonsterNumber].MonsterCurrentExp << "/" << MonsterArr[MonsterNumber].MonsterMaxExp;
	gotoxy(34, 26);
	cout << "ȹ�� ���: " << MonsterArr[MonsterNumber].MonsterDropGold;
}

void Game::ShowResult(int MonsterNumber)
{
	GameMap.BoxErase(WIDTH, HEIGHT);

	GOLD
	gotoxy(21, 13);
	cout << MonsterArr[MonsterNumber].MonsterName << " ��� ����!";

	gotoxy(23, 15);
	cout << "ȹ�� ����ġ: " << MonsterArr[MonsterNumber].MonsterDropExp;

	gotoxy(24, 17);
	cout << "ȹ�� ���: " << MonsterArr[MonsterNumber].MonsterDropGold;
	ORIGINAL

	m_iUserCurrentExp += MonsterArr[MonsterNumber].MonsterDropExp;
	m_iUserGold += MonsterArr[MonsterNumber].MonsterDropGold;

	system("pause>null");

	if (m_iUserCurrentExp >= m_iUserMaxExp)
	{
		//���� ������
		GameMap.BoxErase(WIDTH, HEIGHT);

		GREEN
		gotoxy(21, 13);
		m_iUserLevel++;
		cout << m_iUserLevel <<"������ ���� �� �ߴ�";

		//���ݷ��� 1~5, ������� 1~10 �� ������ ���ڷ� ����
		int iAttackPlus = (rand() % 4) + 1;
		int iLifePlus = (rand() % 9) + 1;

		gotoxy(24, 15);
		cout << "���ݷ� "<< iAttackPlus << " ����";
		gotoxy(21, 17);
		cout << "�ִ� ����� "<< iLifePlus << " ����";
		ORIGINAL

		m_iUserAttack += iAttackPlus;
		m_iUserMaxLife += iLifePlus;
		m_iUserCurrentExp = 0;
		m_iUserMaxExp += 3;
		m_iUserCurrentLife = m_iUserMaxLife;

		system("pause>null");
	}

	MonsterArr[MonsterNumber].MonsterCurrentLife = MonsterArr[MonsterNumber].MonsterMaxLife;
}

//��Ʋ ���� �Լ� ����

void Game::ShowUserInfo()
{
	GameMap.BoxErase(WIDTH, HEIGHT);
	
	YELLOW
	gotoxy(18, 10);
	cout << "=======����� ����=======";
	ORIGINAL

	gotoxy(19, 13);
	cout << "�̸�: " << m_sUserName;
	gotoxy(19, 14);
	cout << "����: " << m_iUserLevel;
	gotoxy(19, 15);
	cout << "�����: " << m_iUserCurrentLife << "/" << m_iUserMaxLife;
	gotoxy(19, 16);
	cout << "���ݷ�: " << m_iUserAttack;
	gotoxy(19, 17);
	cout << "����ġ: " << m_iUserCurrentExp << "/" << m_iUserMaxExp;
	gotoxy(19, 18);
	cout << "���� ���: " << m_iUserGold;

	system("pause>null");
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
		cout << "���ݷ�: " << MonsterArr[j].MonsterAttck;
		gotoxy(34, i);
		cout << "�����: " << MonsterArr[j].MonsterCurrentLife << "/" << MonsterArr[j].MonsterMaxLife;
		i++;
		gotoxy(14, i);
		cout << "����ġ: " << MonsterArr[j].MonsterCurrentExp << "/" << MonsterArr[j].MonsterMaxExp;
		gotoxy(34, i);
		cout << "ȹ�� ����ġ: " << MonsterArr[j].MonsterDropExp;
		i++;
		gotoxy(14, i);
		cout << "ȹ�� ���: " << MonsterArr[j].MonsterDropGold;
		i++;
	}
	
	system("pause>null");
}

void Game::DeleteInfo()
{
	delete[] MonsterArr;
}

Game::~Game()
{
}
