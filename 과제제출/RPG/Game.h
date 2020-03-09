#pragma once
#include "Headers.h"
#include "MapDraw.h"

struct Monster
{
	string MonsterName;
	int MonsterLife;
	int MonsterAttck;
	int MonsterGold;
	int Delay;	//���Ͱ� ������ �ϱ���� �ɸ��� �ð�
	bool Stance;
};

enum STANCE
{
	STANCE_ATTACK = true,
	STANCE_DEFENCE = false
};

class Game
{
private:
	MapDraw GameMap;
	string m_sUserName;	//�̸�
	int m_iUserLife;	//�����
	int m_iUserAttack;	//���ݷ�
	int m_iUserExp;		//����ġ
	int m_iUserGold;	//���� ���
	int m_iUserLevel;	//����
	bool m_bUserStance;	//���� ����
public:
	Game();
	void GetName(string name);
	void TownMenu();
	void ShowUserInfo();
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~Game();
};

