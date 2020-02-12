#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <string>
#include <conio.h>

#define MAX_FEED 10	//먹이 최대 개수
#define MAX_OBS 20	//장애물 최대 개수
#define MAP_WIDTH 50
#define MAP_HEIGHT 30

enum DIRECITON
{
	DIRECTION_LEFT = 75,
	DIRECTION_RIGHT = 77,
	DIRECTION_UP = 72,
	DIRECITON_DOWN = 80,
	DIRECTION_NEUTRAL
};

enum BLOCK_ATTRIBUTE
{
	BLOCK_ATTRIBUTE_WALL,
	BLOCK_ATTRIBUTE_OBS,
	BLOCK_ATTRIBUTE_HEAD,
	BLOCK_ATTRIBUTE_TAIL,
	BLOCK_ATTRIBUTE_FEED
};