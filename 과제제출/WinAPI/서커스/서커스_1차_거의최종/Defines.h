#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>

#define HORIZON_HEIGHT 400	//�� Ÿ���� �׸��� ���� ��
#define JUMP_HEIGHT 305	//���� ���� ��
#define MOVE_PIXEL 15	//�÷��̾ �� �� ������ �� �� �ȼ��� X���� �̵��ϴ°�
#define JUMP_PIXEL 13	//�÷��̾ �� �� ������ �� �� �ȼ��� Y���� �̵��ϴ°�
#define PLAYER_LIFE 5	//�÷��̾� ���
#define CROWD_PATTERN 7	//���� ����
#define FIRE_DISTANCE 700	//ȭ�ΰ� ������ �ִ� X�� ����
#define RING_BACK 2600	//ū ���� �� �Ǵ� ����
#define LITTLERING_DISTANCE 500	//���� ���� �� �Ǵ� ����
#define RING_MOVE_PIXEL 300	//���� �����̴� X���� ����
#define LITTLERING_MOVE_PIXEL 450	//���� ���� �����̴� X���� ����
#define LITTLERING_BACK 3500	//���� ���� ȭ�� �������� ���ư��� �󸶳� ����������
#define CRASHED_NOT 0	//�ƹ��͵� �� �ε�ħ
#define CRASHED_OBJECT -1	//ȭ�γ� ���� �ε�ħ

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

enum HITBOX
{
	HITBOX_RING_WIDTH = 5,	//�� �浹 ������ ���� �¿� �ȼ� ����
	HITBOX_RING_HEIGHT = 5,	//�� �浹 ������ ���� ���� �ȼ� ����
	HITBOX_CHARACTER_WIDTH = 20,
	HITBOX_CHARACTER_HEIGHT_UP = 20,
	HITBOX_CHARACTER_HEIGHT_DOWN = 25,
	//��Ʈ�ڽ� ũ�� ������ ���� ��
};

enum SCORE
{
	SCORE_RING = 100,
	SCORE_FIRE = 100,
	SCORE_CASH = 200

	//�� �ߴ��Ŀ� ���� ���� �ø���
};

enum LOCATION
{
	LOCATION_CHARACTER_VERTICAL = 40,	//ĳ���Ͱ� ���� �Ǵ� X���� ��
	LOCATION_CHARACTER_HORIZON = 395,	//ĳ���Ͱ� ���� �Ǵ� Y���� ��
	LOCATION_RING_Y = 217,	//���� ���̴� Y���� ��
	LOCATION_LIFE_X = 950,	//��� ǥ�� ��ġ X��ǥ
	LOCATION_LIFE_Y = 500,	//��� ǥ�� ��ġ Y��ǥ
	LOCATION_FIRE_Y = 398,	//ȭ�� ���� �ִ� Y���� ��
	LOCATION_SCORE_X = 150,	//���� ǥ�� X��ġ
	LOCATION_SCORE_Y = 475,	//���� ǥ�� Y��ġ
	LOCATION_RING1_START = 700,	//ù��° �� ���� ��ġ
	LOCATION_RING2_START = 2000,	//�ι�° �� ���� ��ġ
	LOCATION_LITTLERING_START = 3500,	//���� �� ���� ��ġ
	LOCATION_GOAL_X = 20000	//���� ���� ��ġ

	//��ũ�η� �����ص� ��ġ ��ǥ�� ���� ����ٰ� �ھƵ� ����
};