#pragma once
#include "Headers.h"

class Rank
{
private:
public:
	void LoadRankingFile();	//��ŷ �ؽ�Ʈ ���� �ҷ��´�
	void GetNameAndScore(string Name, int Score, int Stage);	//�÷��̰� �Ϸ�Ǹ� �̸��� ������ �޾ƿͼ� ������ ���Ͽ� �����Ѵ�
	
	Rank();
	~Rank();
};

