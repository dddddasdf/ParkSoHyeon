#include "Queue.h"

using namespace std;

int main()
{
	Line *NewLine = new Line;
	InitLine(NewLine);

	int iMyCode = 5;
	bool bIsStandby = false;
	int iWaitingPeople = 0;
	int iAddTimer = 0, iAddCounter = clock();
	int iDeleteTimer = 0, iDeleteCounter = clock();
	int iRefreshTimer = 0, iRefreshCounter = clock();

	cout << "* 대기열 *";
	gotoxy(0, 2);
	cout << "                                   \n                                   ";
	gotoxy(0, 2);
	cout << "현재 대기 인원 수\n: ";
	gotoxy(2, 3);
	cout << ReturnPeople(NewLine) << "명";
	gotoxy(0, 5);
	cout << "참여하기: A키";

	while (1)
	{
		iRefreshTimer = clock();
		if (iRefreshTimer - iRefreshCounter >= 1000)
		{
			gotoxy(2, 3);
			cout << "                 ";
			gotoxy(2, 3);
			cout << ReturnPeople(NewLine) << "명";

			if (bIsStandby == true)
			{
				iWaitingPeople = SearchNode(NewLine, iMyCode);
				if (iWaitingPeople != -1)
				{
					gotoxy(0, 7);
					cout << "내 앞에 대기 중인 인원 수: " << iWaitingPeople << "명   ";
				}
			}

			iRefreshCounter = iRefreshTimer;
		}

		if (_kbhit())
		{
			if (_getch() == 'a')
			{
				bIsStandby = true;
				AddNode(NewLine, iMyCode);
				gotoxy(0, 7);
				cout << "                   ";
			}
		}

		if (ReturnPeople(NewLine) < 2000)
			iAddTimer = clock();

		if (iAddTimer - iAddCounter >= 379)
		{
			AddNode(NewLine, 3);
			iAddCounter = iAddTimer;
		}

		iDeleteTimer = clock();

		if (iDeleteTimer - iDeleteCounter >= 1700)
		{
			if (DeleteNode(NewLine) == iMyCode)
			{
				gotoxy(0, 7);
				cout << "                             ";
				gotoxy(0, 7);
				cout << "요청 처리 완료";
				bIsStandby = false;
			}
			iDeleteCounter = iDeleteTimer;
		}
	}
}