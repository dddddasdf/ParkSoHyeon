#include "Game.h"

void main()
{
	//_CrtSetBreakAlloc(408);
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	system("mode con lines=36 cols=102");
	srand(unsigned(time(NULL)));
	Game NowGaming;
	NowGaming.Menu();
}