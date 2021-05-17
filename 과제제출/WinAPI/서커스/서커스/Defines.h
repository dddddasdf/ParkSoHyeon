#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>

#define IMAGE_SIZE_X 240
#define IMAGE_SIZE_Y 400

#define MOVING_PIXEL_WALKING 10
#define MOVING_PIXEL_RUNNING 20

#define CHARACTER_MAX_GESTURE 4

enum DIRECTION
{
	DIRECTION_DOWN = 0,
	DIRECTION_UP = 1,
	DIRECTION_LEFT = 2,
	DIRECTION_RIGHT = 3
};	//자를 위치 구할 때 행을 맡음

enum GESTURE
{
	GESTURE_FRONT_NEUTRAL1 = 0,
	GESTURE_FRONT_LEFTLEG = 1,
	GESTURE_FRONT_NEUTRAL2 = 2,
	GESTURE_FRONT_RIGHTLEG = 3
};	//자를 위치 구할 때 열을 맡음

