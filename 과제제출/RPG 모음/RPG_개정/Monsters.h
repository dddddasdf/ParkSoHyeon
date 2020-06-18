#pragma once
#include "Headers.h"

struct Monster
{
	string sMonsterName;	//몹 이름
	int iMonsterCurrentLife;	//몹 현재 생명력
	int iMonsterMaxLife;	//몹 최대 생명력
	int iMonsterAttack;	//몹 공격력
	int iMonsterDropGold;	//몹이 주는 골드
	int iMonsterLevel;	//몹 현재 레벨
	int iMonsterCurrentExp;	//몹 현재 경험치
	int iMonsterMaxExp;	//다음 레벨 가기 위한 요구 경험치
	int iMonsterDropExp;	//몹이 주는 경험치
	int iMonsterNumber;	//몹 번호
};

struct MonsterNode
{
	Monster MonsterInformation;
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

