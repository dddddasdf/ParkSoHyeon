#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>

#define CHARACTER_LOCATION_X 50
#define JUMP_TIME 1000

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