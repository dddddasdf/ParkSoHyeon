#pragma once
#include "MapDraw.h"
#include "Monsters.h"


enum OUTCOME
{
	OUTCOME_DRAW,
	OUTCOME_WIN,
	OUTCOME_LOSE	//승패 출력을 위한 enum
};


class Game
{
private:

public:
	Game();
	void CreateNewGame();
	void InitData();
	void GetName();
	bool LoadDefaultUserData();	//디폴트 유저 파일 읽어오기, 텍스트를 성공적으로 읽어들였을 경우 true를 반환 아닐시 false를 반환하고 새게임이 시작되지 못하게 막음
	bool InitMonsterData();	//몹 정보 초기화. InitUserInfo()와 똑같은 매커니즘
	bool InitWeaponData();	//무기 정보 초기화. 저 둘을 베이스로 하지만 조금 다르다
	bool LoadDefaultUserData();	//디폴트 유저 파일 읽어오기, 텍스트를 성공적으로 읽어들였을 경우 true를 반환 아닐시 false를 반환하고 새게임이 시작되지 못하게 막음
};

