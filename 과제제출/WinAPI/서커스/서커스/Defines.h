#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>

#define HORIZON_HEIGHT 400	//�� Ÿ���� �׸��� ���� ��
#define CHARACTER_LOCATION_X 40	//ĳ���Ͱ� ���� �Ǵ� X���� ��
#define HORIZON_CHARACTER 395	//ĳ���Ͱ� ���� �Ǵ� Y���� ��
#define JUMP_HEIGHT 305	//���� ���� ��
#define JUMP_PIXEL 13	//�÷��̾ �� �� ������ �� �� �ȼ��� Y���� �̵��ϴ°�
#define PLAYER_LIFE 5	//�÷��̾� ���
#define CROWD_PATTERN 7	//���� ����
#define MOVE_PIXEL 13	//�÷��̾ �� �� ������ �� �� �ȼ��� X���� �̵��ϴ°�

enum DIRECTION
{
	DIRECTION_STAND = 0,
	DIRECTION_LEFT = VK_LEFT,
	DIRECTION_RIGHT = VK_RIGHT

	//ĳ���Ͱ� ���� ���� ���� ���� �����
};	

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