#pragma once

#define IMAGE_SIZE_X 240
#define IMAGE_SIZE_Y 400

#define MOVING_PIXEL 5

enum DIRECTION
{
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
	DIRECTION_UP,
	DIRECTION_DOWN
};

enum GESTURE
{
	GESTURE_FRONT_NEUTRAL1,
	GESTURE_FRONT_LEFT,
	GESTURE_FRONT_NEUTRAL2,
	GESTURE_FRONT_RIGHT,
	GESTURE_LEFT_NEUTRAL1,
	GESTURE_LEFT_LEFT,
	GESTURE_LEFT_NEUTRAL2,
	GESTURE_LEFT_RIGHT,
	GESTURE_BACK_NEUTRAL1,
	GESTURE_BACK_LEFT,
	GESTURE_BACK_NEUTRAL2,
	GESTURE_BACK_RIGHT,
	GESTURE_RIGHT_NEUTRAL1,
	GESTURE_RIGHT_LEFT,
	GESTURE_RIGHT_NEUTRAL2,
	GESTURE_RIGHT_RIGHT

	//캐릭터 스프라이트 불러올 때 사용할 용도
};