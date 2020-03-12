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
	//����Ʈ �� ���� �ؽ�Ʈ ���� �о�� �� ���ڰ� �ǹ��ϴ� ����
	//���̸� ���ݷ� ����� �����ϱ����Ѱ���ġ �ִ°���ġ ���� �ִ� ���
	//�ڵ忡�� �߰��� ��������� �ϴ� ���� �������ġ ������ �ִ� ����ġ �������� �������
	//����Ʈ ���Ͽ� ������ �߰������ �� �߰��ϸ� �� �ּ� �����
	
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

//��Ʋ ���� �Լ� ����

void Game::NowBattle()
{
	while (1)
	{
		GameMap.BoxErase(WIDTH, HEIGHT);

		ShowUserBattle();
		ShowMonsterBattle();

		gotoxy(26, 14);
		YELLOW
			cout << "��";
		ORIGINAL

		gotoxy(34, 14);
		cout << "��";

		gotoxy(18, 16);
		cout << "�ý���: �����Ϸ��� �ƹ�Ű ����";

		gotoxy(22, 17);
		cout << "�¼� ��ȯ: SPACEŰ";

		if (_kbhit())
		{
			if (_getch() == KEYBOARD_SPACE)
			{
				//�����̽��� �Է� �޾��� ��� ���� ��ȯ
				if (m_bUserStance == STANCE_ATTACK)
					m_bUserStance = STANCE_DEFENCE;
				else
					m_bUserStance = STANCE_ATTACK;
			}
			else
				m_iUserCurrentLife = 0;	//�̰Ŵ� ��� �̺�Ʈ Ȯ���� ���� �׽�Ʈ�� �ڵ��Դϴ� ������ �������
		}

		if (m_iUserCurrentLife == 0)
		{
			//������ ü���� ���� ��� ���� ���
			gotoxy(26, 14);
			BLOOD
				cout << "��";
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
	cout << "=======����� ����=======";
	ORIGINAL

	gotoxy(19, 3);
	cout << "�̸�: " << m_sUserName;
	gotoxy(19, 4);
	cout << "����: " << m_iUserLevel;
	gotoxy(19, 5);
	cout << "�����: " << m_iUserCurrentLife << "/" << m_iUserMaxLife;
	gotoxy(19, 6);
	cout << "���ݷ�: " << m_iUserAttack;
	gotoxy(19, 7);
	cout << "����ġ: " << m_iUserCurrentExp << "/" << m_iUserMaxExp;
	gotoxy(19, 8);
	cout << "���� ���: " << m_iUserGold;
	gotoxy(19, 9);
	cout << "���� ����: ";
	if (m_bUserStance == STANCE_ATTACK)
		cout << "����";
	else
		cout << "���";
}

void Game::ShowMonsterBattle()
{
	gotoxy(18, 20);
	cout << "=======�׽�Ʈ �ؽ�Ʈ ���=======";

	gotoxy(19, 21);
	cout << "�̸�: �׽�Ʈ";
	gotoxy(19, 22);
	cout << "����: �׽�Ʈ";
	gotoxy(19, 23);
	cout << "�����: �׽�Ʈ";
	gotoxy(19, 24);
	cout << "���ݷ�: �׽�Ʈ";
	gotoxy(19, 25);
	cout << "����ġ: �׽�Ʈ";
	gotoxy(19, 26);
	cout << "���� ���: �׽�Ʈ";
	gotoxy(19, 27);
	cout << "���� ����: ";
	if (m_bUserStance == STANCE_ATTACK)
		cout << "����";
	else
		cout << "���";
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

void Game::DeleteInfo()
{
	//������ �ϴ� �׾���

}

Game::~Game()
{
}
