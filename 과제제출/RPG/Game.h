#pragma once
#include "Headers.h"
#include "MapDraw.h"

struct Monster
{
	string MonsterName;
	int MonsterLife;
	int MonsterAttck;
	int MonsterGold;
	int Delay;	//���Ͱ� ������ �ϱ���� �ɸ��� �ð�
	bool Stance;
};

enum STANCE
{
	STANCE_ATTACK = true,
	STANCE_DEFENCE = false
};

class Game
{
private:
	MapDraw GameMap;
	string m_sUserName;	//�̸�
	int m_iUserCurrentLife;	//��������
	int m_iUserMaxLife;	//�ִ�����
	int m_iUserAttack;	//���ݷ�
	int m_iUserCurrentExp;		//�������ġ
	int m_iUserMaxExp;	//���� ������ �Ѿ�� ���� �ִ� ����ġ
	int m_iUserGold;	//���� ���
	int m_iUserLevel;	//����
	int m_iUserGetExp;	//������ �ִ� ����ġ
	bool m_bUserStance;	//���� ����
	Monster *MonsterArr;
public:
	Game();
	void GetName(string name);
	bool InitUserInfo();	//���� ���� �ʱ�ȭ, �ؽ�Ʈ�� ���������� �о�鿴�� ��� true�� ��ȯ�ϰ� �̾������ �ƴҽ� false�� ��ȯ�ϰ� �������� ���۵��� ���ϰ� ����
	bool InitMonsterInfo();	//�� ���� �ʱ�ȭ. InitUserInfo()�� �Ȱ��� ��Ŀ����
	void TownMenu();
	void NowBattle();	//���� ȭ��
	void ShowUserBattle();	//���� �� ���� ���� ������
	void ShowMonsterBattle();	//���� �� �� ���� ������
	void ShowResult();	//�� ��� �� �������ͽ� ������
	void ShowUserInfo();
	void DeleteInfo();
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	~Game();
};

