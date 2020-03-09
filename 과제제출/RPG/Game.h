#pragma once
#include "Headers.h"
#include "MapDraw.h"

struct Monster
{
	string MonsterName;
	int MonsterLife;
	int MonsterAttck;
	int MonsterGold;
	int Delay;	//몬스터가 공격을 하기까지 걸리는 시간
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
	string m_sUserName;	//이름
	int m_iUserLife;	//생명력
	int m_iUserAttack;	//공격력
	int m_iUserExp;		//경험치
	int m_iUserGold;	//소지 골드
	int m_iUserLevel;	//레벨
	bool m_bUserStance;	//공방 상태
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

