#pragma once
#include "MapDraw.h"

class Play
{
private:
	MapDraw GameInterface;
public:
	void PlayMain();	//플레이 메인 함수 
	void PrintSynopsis();
	void CleaningSynopsisArea();
	Play();
	~Play();
};

