#pragma once
#include <vector>
#include "Block.h"
#include "Headers (2).h"

//블락매니저랑 얘랑 하는 일 차이가??
//둘을 어케 분리하지

//factory는 만들고 manage는 출력만?? 맞나 이게
//출력이면 팩토리 메서드가 해야하는 거 아님?


//매니저에서 하던 거 어케 옮겨옴
//원래 매니저에서 setblock으로 새 블록 만들고 햇ㅇㅁ.... 이걸 이제 팩토리에서?

/*
1. new factory
2. Block* 만들블락 = 만들블락팩토리->크리에이트뉴블락???? 매니저에서 이걸 호출하나?
3. 

생각해보니까 블록 클래스에서 각 종류별 자식 클래스 만드는 작업부터 해야 함
포지션세팅은 어캄 팩토리에서 해주나 블록 클래스에서 하나
블록에서 하는 게 맞는 거 같다
매니저에 팩토리 넣는 게 맞는 거 갓아요

각 팩토리에서 블락별로 모양 세팅해주면 되나?
*/

class BlockFactory
{
private:
	std::vector <Block*> Blocks;	//이 벡터에 무슨 의미가 있지

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
