#pragma once
#include "MapDraw.h"

class Play
{
private:
	MapDraw GameInterface;
public:
	void PlayMain();	//�÷��� ���� �Լ� 
	void PrintSynopsis();
	void CleaningSynopsisArea();
	Play();
	~Play();
};

