#pragma once
#include "MapDraw.h"

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
	int Delay;	//몬스터가 공격을 하기까지 걸리는 시간
};

struct MonsterNode
{
	Monster MonsterInformaiton;
	MonsterNode *Next;
};

enum OUTCOME
{
	OUTCOME_DRAW,
	OUTCOME_WIN,
	OUTCOME_LOSE	//승패 출력을 위한 enum
};


class Game
{
private:
	Game();
	void GetName(string name);
	bool LoadDefaultUserData();	//디폴트 유저 파일 읽어오기, 텍스트를 성공적으로 읽어들였을 경우 true를 반환 아닐시 false를 반환하고 새게임이 시작되지 못하게 막음
};

