#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>

#define HORIZON_HEIGHT 400	//맵 타일을 그리는 기준 점
#define CHARACTER_LOCATION_X 40	//캐릭터가 서게 되는 X축의 값
#define HORIZON_CHARACTER 395	//캐릭터가 서게 되는 Y축의 값
#define JUMP_HEIGHT 305	//점프 제한 고도
#define JUMP_PIXEL 13	//플레이어가 한 번 점프할 때 몇 픽셀씩 Y축을 이동하는가
#define PLAYER_LIFE 5	//플레이어 목숨
#define CROWD_PATTERN 7	//군중 패턴
#define MOVE_PIXEL 13	//플레이어가 한 번 움직일 때 몇 픽셀씩 X축을 이동하는가

enum DIRECTION
{
	DIRECTION_STAND = 0,
	DIRECTION_LEFT = VK_LEFT,
	DIRECTION_RIGHT = VK_RIGHT

	//캐릭터가 현재 진행 중인 방향 저장용
};	

enum MOTION
{
	MOTION_STAND = 1,
	MOTION_RUNNING = 2,
	MOTION_JUMPING = 3

	//캐릭터의 모션을 관리하기 위한 번호
};

enum BACKGROUND
{
	BACKGROUND_FLOOR = 1,
	BACKGROUND_ELEPHANT = 2,
	BACKGROUND_CROWD_FIRST = 3,
	BACKGROUND_CROWD_SECOND = 4

	//백그라운드 타일을 관리하기 위한 번호
};