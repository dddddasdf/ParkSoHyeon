#include "Headers.h"
#include "Menu.h"
#include <crtdbg.h>


int main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_CrtSetBreakAlloc(565);
	//_CrtSetBreakAlloc(657);
	_CrtSetBreakAlloc(600);
	system("mode con lines=31 cols=62");
	srand((unsigned)time(NULL));

	Menu MainMenu;
	MainMenu.PrintMainMenu();

	return 0;
}