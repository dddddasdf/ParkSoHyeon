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
#define MOVE_PIXEL 15	//플레이어가 한 번 움직일 때 몇 픽셀씩 X축을 이동하는가
#define PLAYER_LIFE 5	//플레이어 목숨
#define CROWD_PATTERN 7	//군중 패턴
#define HORIZON_FIRE 398	//화로 놓여 있는 Y축의 값
#define FIRE_DISTANCE 700	//화로가 놓여져 있는 X축 간격
#define LITTLERING_DISTANCE 500	//작은 고리가 젠 되는 간격
#define RING_LOCATION_Y 217	//고리가 놓이는 Y축의 값
#define RING_MOVE_PIXEL 300	//고리가 움직이는 X축의 간격
#define LITTLERING_MOVE_PIXEL 450	//작은 고리가 움직이는 X축의 간격
#define DEFAULT_RING1_START 700	//첫번째 고리 시작 위치
#define DEFAULT_RING2_START 2000	//두번째 고리 시작 위치
#define DEFAULT_LITTLERING_START 3500	//작은 고리 시작 위치
#define RING_BACK 2600	//링이 화면 뒤쪽으로 돌아갈때 얼마나 보내버릴지
#define LITTLERING_BACK 3500	//작은 고리가 화면 뒤쪽으로 돌아갈때 얼마나 보내버릴지
#define LIFE_LOCATION_Y 500
#define LIFE_LOCATION_X 950
#define SCORE_LOCATION_Y 475
#define SCORE_LOCATION_X 150
#define CRASHED_NOT 0	//아무것도 안 부딪침
#define CRASHED_OBJECT -1	//화로나 고리와 부딪침
#define GOAL_LOCATION_X 20000	//골인 지점 위치

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
	MOTION_JUMPING = 3,
	MOTION_DEAD = 6

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

enum OBSTACLE
{
	OBSTACLE_FIRE_1 = 1,
	OBSTACLE_FIRE_2 = 2,
	OBSTACLE_RING_FIRST_1 = 3,
	OBSTACLE_RING_FIRST_2 = 4,
	OBSTACLE_RING_SECOND_1 = 5,
	OBSTACLE_RING_SECOND_2 = 6,
	OBSTACLE_LITTLERING_1 = 7,
	OBSTACLE_LITTLERING_2 = 8,
	OBSTACLE_CASH = 9

	//장애물 타일을 관리하기 위한 번호 - 이거 폐기할 듯
};

enum HINDRANCE
{
	HINDRANCE_FIRE_1 = 1,
	HINDRANCE_FIRE_2 = 2,
	HINDRANCE_RING_FIRST_1 = 1,
	HINDRANCE_RING_FIRST_2 = 2,
	HINDRANCE_RING_SECOND_1 = 3,
	HINDRANCE_RING_SECOND_2 = 4,
	HINDRANCE_LITTLERING_1 = 1,
	HINDRANCE_LITTLERING_2 = 2,
	HINDRANCE_CASH
};

enum OBSTACLE_ANIMATION
{
	ANIMATION_RING_1 = 0,
	ANIMATION_RING_2 = 1,
	ANIMATION_FIRE_1 = 0,
	ANIMATION_FIRE_2 = 1
};

enum HITBOX
{
	HITBOX_RING_WIDTH = 5,	//고리 충돌 판정을 갖는 좌우 픽셀 길이
	HITBOX_RING_HEIGHT = 5,	//고리 충돌 판정을 갖는 상하 픽셀 길이
	HITBOX_CHARACTER_WIDTH = 20,
	HITBOX_CHARACTER_HEIGHT_UP = 20,
	HITBOX_CHARACTER_HEIGHT_DOWN = 25,
	//히트박스 크기 관리를 위한 곳
};

enum SCORE
{
	SCORE_RING = 100,
	SCORE_FIRE = 100,
	SCORE_CASH = 200

	//뭐 했느냐에 따라 점수 올리기
};

enum LOCATION
{

	//매크로로 설정해둔 위치 좌표들 전부 여기다가 박아둘 예정
};