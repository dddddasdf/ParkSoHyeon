#pragma once
#include "MapDraw.h"
#include "Play.h"
#include "Rank.h"

class MainMenu
{
private:
	MapDraw MenuInterface;
	Play NowPlaying;
	Rank Ranking;
public:
	MainMenu();
	void PrintMenu();
	~MainMenu();
};

