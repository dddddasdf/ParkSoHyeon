#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include<Windows.h>
//////////////////////////////////////////////////////
#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//색상 지정
#define ORIGINAL SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );
//////////////////////////////////////////////////////
#define WALL 1
#define NULL 0
#define Y 0
#define X 1
#define CHARACTER 2
#define POTAL_MAX 9//포탈 갯수
#define ENTRY_START 10
#define EXIT_START 20
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define WIDTH 20
#define HEIGHT 20
#define ATTENTION 40
#define DOOR 45
#define DOOR_T 46
#define BREAKABLE 47
#define BROKEN 48
#define LAVA 90
#define MONSTER 50
#define DEADMAN 3
#define BRIDGE 95
#define SWITCH 100
#define KEY 110
#define EXIT 150
int map[HEIGHT][WIDTH] = {
	{ 1,	1,	1,	1,	1,	1,	1,	1,	1,	1,  47,  1,  1,	1,	1,	1,	1,	1,	1,	1 },
	{ 1,	2,	0,	40,	0,	0,	0,	0,	45,	0,	0,	0,	0,	0,	0,	0,	0,  0,  100,  1 },
	{ 1,	1,	1,	1,	1,	1,	1,	1,	1,	0,  0,	0,	0,	0,	0,	0,	0,	0,	0,  1 },
	{ 1,	0,	0,	0,	0,	0,	0,	0,	0,	0,  0,	0,	0,	0,	0,	0,	0,	0,	0,  1 },
	{ 1,	0,	0,	0,	0,	0,	0,	0,	0,	0,  0,	0,	0,	0,	0,	0,	0,	0,	0,  1 },
	{ 1,	10,	0,	0,	0,	0,	0,	11,	0,	0,  0,	0,	0,	0,	0,	0,	0,	0,	28,  1 },
	{ 1,	20,	0,	0,	0,	0,	0,	21,	0,	0,  0,	0,	0,	0,	0,	0,	0,	0,	0,  1 },
	{ 1,	0,	0,	0,	0,	0,	0,	0,	0,	0,  0,	0,	0,	0,	0,	0,	0,	0,	0,  1 },
	{ 1,	0,	0,	0,	0,	0,	0,	0,	0, 0,  0,	0,	0,	0,	0,	0,	0,	0,	0,  1 },
	{ 1,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,  90,  90,  1 },
	{ 1,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,  90,  90,  1 },
	{ 1,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,  90,  90,  1 },
	{ 1,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,  90,  90,  1 },
	{ 1,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,	90,  90,  90,  1 },
	{ 1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,  0,  0,  1 },
	{ 1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,  0,  0,  1 },
	{ 1,	13,	0,	0,	0,	0,	22,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,  0,  0,  1 },
	{ 1,	1,	1,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	1,	1,	1,	1,  1,  1,  1 },
	{ 1,	12,	110,0,	0,	0,	23,	1,	0,	0,	0,	0,	0,	46,	0,	0,	0,  0,  50,  150 },
	{ 1,	1,	1,	1,	1,	1,	1,	1,	1,	1,  1,  1,  1,	1,	1,	1,	1,	1,	1,	1 } };
int character[2];
int Entry_Potal[POTAL_MAX][2];
int Exit_Potal[POTAL_MAX][2];
int LastObjectIndex = NULL;
int weapon = 0;
int flag = 0;
int key = 0;
int undo = NULL;
void Init()
{
	int Width = (WIDTH * 2) + 1;
	int Height = HEIGHT + 8;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", Height, Width);
	system(buf);
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == CHARACTER)
			{
				character[X] = x;
				character[Y] = y;
			}
			else if (map[y][x] >= ENTRY_START && map[y][x] < ENTRY_START + POTAL_MAX)
			{
				Entry_Potal[map[y][x] - ENTRY_START][X] = x;
				Entry_Potal[map[y][x] - ENTRY_START][Y] = y;
			}
			else if (map[y][x] >= EXIT_START && map[y][x] < EXIT_START + POTAL_MAX)
			{
				Exit_Potal[map[y][x] - EXIT_START][X] = x;
				Exit_Potal[map[y][x] - EXIT_START][Y] = y;
			}
		}
	}
}
void MapDraw()
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == WALL)
				printf("▩");
			else if (map[y][x] == CHARACTER)
			{
				RED
					printf("♣");
				ORIGINAL
			}
			else if (map[y][x] >= ENTRY_START && map[y][x] < ENTRY_START + POTAL_MAX)
			{
				BLUE
					printf("◎");
				ORIGINAL
			}
			else if (map[y][x] >= EXIT_START && map[y][x] < EXIT_START + POTAL_MAX)
			{
				YELLOW
					printf("●");
				ORIGINAL
			}
			else if (map[y][x] == MONSTER)
			{
				PLUM
					printf("＆");
				ORIGINAL
			}
			else if (map[y][x] == ATTENTION)
			{
				printf("★");
			}
			else if (map[y][x] == DOOR || map[y][x] == DOOR_T)
			{
				GOLD
					printf("■");
				ORIGINAL
			}
			else if (map[y][x] == LAVA)
			{
				BLOOD
					printf("■");
				ORIGINAL
			}
			else if (map[y][x] == BRIDGE)
			{
				GRAY
					printf("■");
				ORIGINAL
			}
			else if (map[y][x] == SWITCH)
			{
				SKY_BLUE
					printf("◈");
				ORIGINAL
			}
			else if (map[y][x] == KEY)
			{
				YELLOW
					printf("＊");
				ORIGINAL
			}
			else if (map[y][x] == DEADMAN)
				printf("♧");
			else if (map[y][x] == BREAKABLE)
				printf("▨");
			else if (map[y][x] == BROKEN)
				printf("□");
			else if (map[y][x] == NULL)
				printf("  ");
			else if (map[y][x] == EXIT)
				printf("  ");
		}
		printf("\n");
	}
	RED
		printf("유저: ♧   ");
	ORIGINAL
		PLUM
		printf("몹: ＆   ");
	ORIGINAL
		printf("표지판: ★\n");
	GOLD
		printf("문: ■   ");
	ORIGINAL
		BLUE
		printf("입구: ◎   ");
	ORIGINAL
		YELLOW
		printf("출구: ●\n");
	ORIGINAL
		printf("결정키: z\n");
	printf("메시지: ");
	if (flag == 1)
		printf("←↑↓→");
	else if (flag == 2)
		printf("벽이 부서지고 무기를 획득했다.");
	else if (flag == 3)
		printf("무기로 몹을 죽였다.");
	else if (flag == 4)
	{
		printf("몹에게 맞아 죽었다.\n");
	}
	else if (flag == 5)
	{
		printf("용암에 다가갔다가 타 죽었다.\n");
	}
	else if (flag == 6)
	{
		printf("다리가 생겨 용암 지대를 건널 수 있게 되었다.");
	}
	else if (flag == 7)
	{
		printf("열쇠를 획득하였다.");
	}
	else if (flag == 8)
	{
		printf("문이 열리지 않는다.");
	}
	else if (flag == 9)
	{
		printf("열쇠로 문을 열었다.");
	}
	else if (flag == 10)
	{
		printf("문제. 2019년 10월 1일은 수요일인가? O - z키 X - x키\n");
	}
	else if (flag == 11)
	{
		printf("문제를 틀려 죽었다.\n");
	}
	else if (flag == 12)
	{
		printf("문이 열렸다.");
	}
	else if (flag == 15)
	{
		printf("탈출에 성공하셨습니다.\n");
		system("pause");
		exit(0);
	}
}
void MoveCheck()
{
	int index = map[character[Y]][character[X]];
	if (index >= ENTRY_START && index < ENTRY_START + POTAL_MAX)
	{
		character[X] = Exit_Potal[index - ENTRY_START][X];
		character[Y] = Exit_Potal[index - ENTRY_START][Y];
	}
	else if (index == ATTENTION)
		flag = 1;
	else if (index == MONSTER)
	{
		if (weapon == 1)	//무기 있으면
		{
			flag = 3;
			map[character[Y]][character[X]] = NULL;
		}
		else //무기 없으면
		{
			flag = 4;
		}
	}
	else if (index == LAVA)	//용암에 뛰어들었을 때
		flag = 5;
	else if (index == SWITCH)	//스위치 작동
	{
		flag = 6;
		map[character[Y]][character[X]] = NULL;
		for (int i = 9; i < 14; i++)
		{
			for (int j = 14; j < 16; j++)
				map[i][j] = BRIDGE;
		}
	}
	else if (index == KEY)	//열쇠 획득
	{
		flag = 7;
		map[character[Y]][character[X]] = NULL;
		key++;
	}
	else if (index == EXIT)
		flag = 15;
}
void Move()
{
	char ch;
	ch = _getch();
	system("cls");
	map[character[Y]][character[X]] = LastObjectIndex;
	undo = map[character[Y]][character[X]];
	switch (ch)
	{
	case LEFT:
		if (map[character[Y]][character[X] - 1] != WALL &&
			map[character[Y]][character[X] - 1] != BREAKABLE &&
			map[character[Y]][character[X] - 1] != BROKEN)
		{
			character[X]--;
			flag = 0;
		}
		break;
	case RIGHT:
		if (map[character[Y]][character[X] + 1] != WALL &&
			map[character[Y]][character[X] + 1] != BREAKABLE &&
			map[character[Y]][character[X] + 1] != BROKEN &&
			map[character[Y]][character[X] + 1] != DOOR_T)
		{
			character[X]++;
			flag = 0;
		}
		break;
	case UP:
		if (map[character[Y] - 1][character[X]] != WALL &&
			map[character[Y] - 1][character[X]] != BREAKABLE &&
			map[character[Y] - 1][character[X]] != BROKEN)
		{
			character[Y]--;
			flag = 0;
		}
		break;
	case DOWN:
		if (map[character[Y] + 1][character[X]] != WALL &&
			map[character[Y] + 1][character[X]] != BREAKABLE &&
			map[character[Y] + 1][character[X]] != BROKEN)
		{
			character[Y]++;
			flag = 0;
		}
		break;
	case 'z':
		if (map[character[Y] - 1][character[X]] == BREAKABLE)
		{
			flag = 2;
			map[character[Y] - 1][character[X]] = BROKEN;
			weapon++;
		}
		if (map[character[Y]][character[X] + 1] == DOOR_T)
		{
			if (key == 0)
			{
				flag = 8;
			}
			else
			{
				flag = 9;
				map[character[Y]][character[X] + 1] = NULL;
			}
		}
		else if (map[character[Y]][character[X] + 1] == DOOR)
		{
			flag = 10;
		}
		break;
	}
	MoveCheck();
	LastObjectIndex = map[character[Y]][character[X]];
	map[character[Y]][character[X]] = CHARACTER;
}
void main()
{
	Init();
	while (1)
	{
		MapDraw();

		if (flag == 10)
		{
			char ch = _getch();
			switch (ch)
			{
			case 'z':
				flag = 11;
				break;
			case 'x':
				flag = 12;
				map[character[Y]][character[X] + 1] = NULL;
				break;
			default:
				break;
			}
		}
		else if (flag == 4 || flag == 5 || flag == 11)	//사망시 게임 오버 이벤트 발생
		{
			system("pause");
			exit(0);
		}
		else
			Move();
	}
}