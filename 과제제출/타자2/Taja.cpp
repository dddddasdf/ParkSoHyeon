#include "MainMenu.h"


int main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	//_CrtSetBreakAlloc(70390);
	//_CrtSetBreakAlloc(308); //대체 뭐가 메모리 누수 발생시키는지 모르겠음
	//_CrtSetBreakAlloc(155);
	//_CrtSetBreakAlloc(156);
	//_CrtSetBreakAlloc(157);
	system("mode con lines=42 cols=130");
	srand((unsigned)time(NULL));

	MainMenu NewGame;
	NewGame.PrintMenu();

	return 0;
}
