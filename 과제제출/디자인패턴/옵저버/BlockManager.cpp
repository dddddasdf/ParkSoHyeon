#include "BlockManager.h"

BlockManager::BlockManager()
{
	SetBlocks();
	PrintBlocks();
}

void BlockManager::SetBlocks()
{
	m_vBlockVector.resize(HEIGHT, std::vector<int>(WIDTH));
		
	std::vector <int> vTemporaryVector;

	for (int j = 0; j < HEIGHT; j++)
	{
		vTemporaryVector.resize(WIDTH);

		if (j == 0 || j == (HEIGHT - 1))	//첫줄과 마지막 줄
		{
			for (int i = 0; i < WIDTH; i++)
			{
				vTemporaryVector.at(i) = BLOCK_ATTRIBUTE_WALL;
			}

			if (j == 0)
				vTemporaryVector.at(10) = BLOCK_ATTRIBUTE_BREAKABLE;
		}
		else
		{
			vTemporaryVector.at(0) = BLOCK_ATTRIBUTE_WALL;

			for (int i = 1; i < WIDTH - 1; i++)
				vTemporaryVector.at(i) = BLOCK_ATTRIBUTE_NULL;

			vTemporaryVector.at(WIDTH - 1) = BLOCK_ATTRIBUTE_WALL;

			if (j == 1)
			{
				vTemporaryVector.at(8) = BLOCK_ATTRIBUTE_DOOR;
				vTemporaryVector.at(WIDTH - 2) = BLOCK_ATTRIBUTE_SWITCH;
			}
			else if (j == 2)
			{
				for (int m = 1; m < 9; m++)
					vTemporaryVector.at(m) = BLOCK_ATTRIBUTE_WALL;
			}
			else if (j >= 9 && j <= 13)
			{
				for (int i = 1; i < WIDTH - 1; i++)
					vTemporaryVector.at(i) = BLOCK_ATTRIBUTE_LAVA;
			}
			else if (j == HEIGHT - 3)
			{
				for (int i = WIDTH - 7; i < WIDTH - 1; i++)
					vTemporaryVector.at(i) = BLOCK_ATTRIBUTE_WALL;
			}
			else if (j == HEIGHT - 2)
			{
				vTemporaryVector.at(WIDTH - 1) = BLOCK_ATTRIBUTE_NULL;
			}
		}

		m_vBlockVector.at(j).swap(vTemporaryVector);	//이중 벡터에 집어넣음

		vTemporaryVector.clear();
	}
}

void BlockManager::PrintBlocks()
{
	std::string sTemporaryShape;	//Block에 모양 잡아놓고 왜 이런식으로 햇지??? 개정필요

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			gotoxy(j * 2, i);
			
			switch (m_vBlockVector.at(i).at(j))
			{
			case BLOCK_ATTRIBUTE_WALL:
				std::cout << "▩";
				break;
			case BLOCK_ATTRIBUTE_BREAKABLE:
				std::cout << "▨";
				break;
			case BLOCK_ATTRIBUTE_BROKEN:
				std::cout << "□";
				break;
			case BLOCK_ATTRIBUTE_LAVA:
				ChangeColor(COLOR_RED);
				std::cout << "■";
				ChangeColor(COLOR_BLUE);
				break;
			case BLOCK_ATTRIBUTE_BRIDGE:
				std::cout << "■";
				break;
			case BLOCK_ATTRIBUTE_DOOR:
				ChangeColor(COLOR_GOLD);
				std::cout << "■";
				ChangeColor(COLOR_BLUE);
				break;
			case BLOCK_ATTRIBUTE_SWITCH:
				ChangeColor(COLOR_YELLOW);
				std::cout << "◈";
				ChangeColor(COLOR_BLUE);
				break;
			case BLOCK_ATTRIBUTE_START:
				std::cout << "◎";
				break;
			case BLOCK_ATTRIBUTE_END:
				std::cout << "●";
				break;
			case BLOCK_ATTRIBUTE_USER:
				std::cout << "♣";
				break;
			case BLOCK_ATTRIBUTE_USER_DEAD:
				std::cout << "♧";
				break;
			}
		}
	}
}


BlockManager::~BlockManager()
{

}