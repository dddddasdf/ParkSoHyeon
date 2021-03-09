#pragma once
#include <vector>
#include "Block.h"
#include "Headers (2).h"

//����Ŵ����� ��� �ϴ� �� ���̰�??
//���� ���� �и�����

//factory�� ����� manage�� ��¸�?? �³� �̰�
//����̸� ���丮 �޼��尡 �ؾ��ϴ� �� �ƴ�?


//�Ŵ������� �ϴ� �� ���� �Űܿ�
//���� �Ŵ������� setblock���� �� ��� ����� �ޤ���.... �̰� ���� ���丮����?

/*
1. new factory
2. Block* ������ = ���������丮->ũ������Ʈ�����???? �Ŵ������� �̰� ȣ���ϳ�?
3. 

�����غ��ϱ� ��� Ŭ�������� �� ������ �ڽ� Ŭ���� ����� �۾����� �ؾ� ��
�����Ǽ����� ��į ���丮���� ���ֳ� ��� Ŭ�������� �ϳ�
��Ͽ��� �ϴ� �� �´� �� ����
�Ŵ����� ���丮 �ִ� �� �´� �� ���ƿ�

�� ���丮���� ������� ��� �������ָ� �ǳ�?
*/

class BlockFactory
{
private:
	std::vector <Block*> Blocks;	//�� ���Ϳ� ���� �ǹ̰� ����

protected:
	void AddBlock(Block* NewBlock);

public:
	~BlockFactory();

	virtual Block* CreateNewBlockClass() = 0;

};

class WallBlockFactory : public BlockFactory
{
private:
	
public:
	virtual Block* CreateNewBlockClass();
};

class FeedBlockFactory : public BlockFactory
{
private:

public:
	
	virtual Block* CreateNewBlockClass();
};

class ObstacletBlockFactory : public BlockFactory
{
private:

public:

	virtual Block* CreateNewBlockClass();
};
