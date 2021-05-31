#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>

#define CHARACTER_LOCATION_X 40
#define JUMP_TIME 1000
#define HORIZON_HEIGHT 400
#define HORIZON_CHARACTER 395
#define JUMP_HEIGHT 305
#define JUMP_LENGTH 15
#define PLAYER_LIFE 5
#define CROWD_PATTERN 7	//���� ����
#define MOVE_PIXEL 25	//�÷��̾ �� �� ������ �� �󸶳� �̵��ϴ°�

enum DIRECTION
{
	DIRECTION_DOWN = 0,
	DIRECTION_UP = 1,
	DIRECTION_LEFT = 2,
	DIRECTION_RIGHT = 3
};	//�ڸ� ��ġ ���� �� ���� ����

enum GESTURE
{
	GESTURE_FRONT_NEUTRAL1 = 0,
	GESTURE_FRONT_LEFTLEG = 1,
	GESTURE_FRONT_NEUTRAL2 = 2,
	GESTURE_FRONT_RIGHTLEG = 3
};	//�ڸ� ��ġ ���� �� ���� ����

enum MOTION
{
	MOTION_STAND = 1,
	MOTION_RUNNING = 2,
	MOTION_JUMPING = 3

	//ĳ������ ����� �����ϱ� ���� ��ȣ
};

enum BACKGROUND
{
	BACKGROUND_FLOOR = 1,
	BACKGROUND_ELEPHANT = 2,
	BACKGROUND_CROWD_FIRST = 3,
	BACKGROUND_CROWD_SECOND = 4

	//��׶��� Ÿ���� �����ϱ� ���� ��ȣ
};