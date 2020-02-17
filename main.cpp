#include "Game.h"

void main()
{
	system("mode con lines=36 cols=102");
	srand(unsigned(time(NULL)));
	Game NowGaming;
	NowGaming.Menu();
}