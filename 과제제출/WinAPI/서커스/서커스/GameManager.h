#pragma once
#include "ResourceManager.h"
#include "TemplateSingleton.h"
#include "DrawManager.h"

class GameManager : public Singleton <GameManager>
{
private:

public:
	void WholeInit();	//��ü �ʱ�ȭ �Ѱ�
	void MovingCharacter();	//
};



/*
�����غ��ϱ� ������ ���¿����� ����� ������ �̵����� �� �ϴ���
���۰��� ������ ���ΰ� ������ ���ΰ�
�����ϴ� �� �� ����� �� ������


ĳ���� X ��ǥ�� ����
Y��ǥ�� �����ÿ� �ٲ�

ĳ���� �̵� ��Ŀ����
����Ű �� �� ������ �����̰� �ٽ� ���ĵ����� ���ƿ��� �� 2�������� ����


������...
�����ϸ� ���� ���� ���� ���� �����
�����̽��� ������ ���� �ð����� ������ �ð� ���� Ű�Է� �� �޵��� ó����
�ؾ��� �� ����
*/