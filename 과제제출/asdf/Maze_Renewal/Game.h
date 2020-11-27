#include "BlockManager.h"
#pragma once


class Game
{
private:
	BlockManager *Interface;

public:
	virtual void Initialized();
	virtual void Update();
	virtual void Finished();

protected:

};

