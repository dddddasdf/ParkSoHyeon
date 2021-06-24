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
#define END_OF_MAP 10000	//���� �� ���� ����
#define HORIZON_FIRE 398	//ȭ�� ���� �ִ� Y���� ��
#define FIRE_DISTANCE 700	//ȭ�ΰ� ������ �ִ� X�� ����
#define RING_DISTANCE 500	//���� �� �Ǵ� ����
#define LITTLERING_DISTANCE 500	//���� ���� �� �Ǵ� ����
#define RING_LOCATION_Y 217	//���� ���̴� Y���� ��
#define RING_MOVE_PIXEL 300	//���� �����̴� X���� ����
#define LITTLERING_MOVE_PIXEL 450	//���� ���� �����̴� X���� ����
#define RING_COLLISION_WIDTH_PIEXL 5	//�� �浹 ������ ���� �¿� �ȼ� ����
#define RING_COLLISION_HEIGHT_PIEXL 14	//�� �浹 ������ ���� ���� �ȼ� ����
#define DEFAULT_RING1_START 700	//ù��° �� ���� ��ġ
#define DEFAULT_RING2_START 2000	//�ι�° �� ���� ��ġ
#define DEFAULT_LITTLERING_START 3500	//���� �� ���� ��ġ
#define RING_BACK 1300	//���� ȭ�� �������� ���ư��� �󸶳� ����������
#define LITTLERING_BACK 3500	//���� ���� ȭ�� �������� ���ư��� �󸶳� ����������

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
	MOTION_JUMPING = 3,
	MOTION_DEAD = 6

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

	//��ֹ� Ÿ���� �����ϱ� ���� ��ȣ - �̰� ����� ��
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