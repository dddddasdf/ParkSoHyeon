#include "MainMenu.h"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_CrtSetBreakAlloc(154);
	//_CrtSetBreakAlloc(155);
	//_CrtSetBreakAlloc(156);
	//_CrtSetBreakAlloc(157);
	system("mode con lines=43 cols=130");
	srand((unsigned)time(NULL));

	MainMenu NewGame;
	NewGame.PrintMenu();

	return 0;
}
