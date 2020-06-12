#pragma once
#include "Headers.h"

struct Monster
{
	string MonsterName;	//�� �̸�
	int MonsterCurrentLife;	//�� ���� �����
	int MonsterMaxLife;	//�� �ִ� �����
	int MonsterAttack;	//�� ���ݷ�
	int MonsterDropGold;	//���� �ִ� ���
	int MonsterLevel;	//�� ���� ����
	int MonsterCurrentExp;	//�� ���� ����ġ
	int MonsterMaxExp;	//���� ���� ���� ���� �䱸 ����ġ
	int MonsterDropExp;	//���� �ִ� ����ġ
};

struct MonsterNode
{
	Monster MonsterInformaiton;
	int iMonsterNumber;
	MonsterNode *Next;
};

struct MonsterList
{
	MonsterNode *Head;
	MonsterNode *Current;
	int iMonsterPopulation;
};

class Monsters
{
private:
	int m_iMonsterPopulation;
	MonsterList *NewMonsterList;
public:
	bool InitMonsterData();	//�� ���� �ʱ�ȭ. InitUserInfo()�� �Ȱ��� ��Ŀ����
	string ReturnMonsterName(int MonsterNumber);
	int ReturnMonsterStatus(int MonsterNumber, int StatusType);
	void DeleteMonsterList();
};

