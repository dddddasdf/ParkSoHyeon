#include "Monsters.h"

bool Monsters::InitMonsterData()
{
	//�� ���� ���ڴ� �����ϴ� ������ �� ��
	//����Ʈ �� ���� �ؽ�Ʈ ���� �о�� �� ���ڰ� �ǹ��ϴ� ����
	//���̸�, ���ݷ�, �����, ���� �ϱ� ���� ����ġ, �ִ� ����ġ, ����, �ִ� ���
	//�ڵ忡�� �߰��� ��������� �ϴ� ���� �������ġ ������ �ִ� ����ġ ��������

	ifstream MonsterInfoLoad;
	MonsterInfoLoad.open("DefaultMonsterInfo.txt");
	if (MonsterInfoLoad.is_open())
	{
		NewMonsterList = new MonsterList;
		MonsterInfoLoad >> NewMonsterList->iMonsterPopulation;

		NewMonsterList->Head = new MonsterNode;
		NewMonsterList->Head->Next = NULL;
		NewMonsterList->Current = NULL;

		int j = 0;

		while (!MonsterInfoLoad.eof())
		{
			MonsterNode *NewMonsterNode = new MonsterNode;

			MonsterInfoLoad >> MonsterArray[j].MonsterName;
			MonsterInfoLoad >> MonsterArray[j].MonsterAttack;
			MonsterInfoLoad >> MonsterArray[j].MonsterMaxLife;
			MonsterInfoLoad >> MonsterArray[j].MonsterMaxExp;
			MonsterInfoLoad >> MonsterArray[j].MonsterDropExp;
			MonsterInfoLoad >> MonsterArray[j].MonsterLevel;
			MonsterInfoLoad >> MonsterArray[j].MonsterDropGold;
			MonsterArray[j].MonsterCurrentExp = 0;
			MonsterArray[j].MonsterCurrentLife = MonsterArray[j].MonsterMaxLife;
			j++;
		}

		return true;
	}
	else
		return false;	//����Ʈ ���� ������ ���� ��� �������� ǥ���ϰ� ���� ȭ������ ���ư���
}