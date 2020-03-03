#pragma once
#include "Headers.h"


class Computer
{
private:
	string m_sComputerName;
	bool m_bPower = false;
	string m_sGPU;
	string m_sCPU;
	int m_iMemory;
public:
	Computer();
	void PrintSpec();
	void Functions();
	~Computer();
};

