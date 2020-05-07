#pragma once
#include "Headers.h"

class Rank
{
private:
public:
	void LoadRankingFile();	//랭킹 텍스트 파일 불러온다
	void GetNameAndScore(string Name, int Score, int Stage);	//플레이가 완료되면 이름과 점수를 받아와서 데이터 파일에 저장한다
	
	Rank();
	~Rank();
};

