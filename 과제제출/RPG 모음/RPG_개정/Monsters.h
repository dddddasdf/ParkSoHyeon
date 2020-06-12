#pragma once
#include "Headers.h"

struct Monster
{
	string MonsterName;	//몹 이름
	int MonsterCurrentLife;	//몹 현재 생명력
	int MonsterMaxLife;	//몹 최대 생명력
	int MonsterAttack;	//몹 공격력
	int MonsterDropGold;	//몹이 주는 골드
	int MonsterLevel;	//몹 현재 레벨
	int MonsterCurrentExp;	//몹 현재 경험치
	int MonsterMaxExp;	//다음 레벨 가기 위한 요구 경험치
	int MonsterDropExp;	//몹이 주는 경험치
};

struct MonsterNode
{
	Monster MonsterInformaiton;
	int iMonsterNumber;
	MonsterNode *Next;
};

struct MonsterList
{
	MonsterNode *Head;
	MonsterNode *Current;
	int iMonsterPopulation;
};

class Monsters
{
private:
	int m_iMonsterPopulation;
	MonsterList *NewMonsterList;
public:
	bool InitMonsterData();	//몹 정보 초기화. InitUserInfo()와 똑같은 매커니즘
	string ReturnMonsterName(int MonsterNumber);
	int ReturnMonsterStatus(int MonsterNumber, int StatusType);
	void DeleteMonsterList();
};

