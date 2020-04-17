#pragma once
#include "MapDraw.h"
#include "Play.h"

class MainMenu
{
private:
	MapDraw MenuInterface;
	Play NowPlaying;
public:
	MainMenu();
	void PrintMenu();
	~MainMenu();
};

