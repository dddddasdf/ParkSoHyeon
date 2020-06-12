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

	cout << "* ��⿭ *";
	gotoxy(0, 2);
	cout << "                                   \n                                   ";
	gotoxy(0, 2);
	cout << "���� ��� �ο� ��\n: ";
	gotoxy(2, 3);
	cout << ReturnPeople(NewLine) << "��";
	gotoxy(0, 5);
	cout << "�����ϱ�: AŰ";

	while (1)
	{
		iRefreshTimer = clock();
		if (iRefreshTimer - iRefreshCounter >= 1000)
		{
			gotoxy(2, 3);
			cout << "                 ";
			gotoxy(2, 3);
			cout << ReturnPeople(NewLine) << "��";

			if (bIsStandby == true)
			{
				iWaitingPeople = SearchNode(NewLine, iMyCode);
				if (iWaitingPeople != -1)
				{
					gotoxy(0, 7);
					cout << "�� �տ� ��� ���� �ο� ��: " << iWaitingPeople << "��   ";
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
				cout << "��û ó�� �Ϸ�";
				bIsStandby = false;
			}
			iDeleteCounter = iDeleteTimer;
		}
	}
}