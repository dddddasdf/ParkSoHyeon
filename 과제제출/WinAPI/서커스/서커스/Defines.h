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
#define MOVE_PIXEL 15	//�÷��̾ �� �� ������ �� �� �ȼ��� X���� �̵��ϴ°�
#define PLAYER_LIFE 5	//�÷��̾� ���
#define CROWD_PATTERN 7	//���� ����
#define END_OF_MAP 5000	//���� �� ���� ����
#define HORIZON_FIRE 398	//ȭ�� ���� �ִ� Y���� ��
#define FIRE_DISTANCE 500	//ȭ�ΰ� ������ �ִ� X�� ����

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

	//��ֹ� Ÿ���� �����ϱ� ���� ��ȣ
};