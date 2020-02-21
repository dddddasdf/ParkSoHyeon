#include "Computer.h"



Computer::Computer()
{
	m_sComputerName = "창원시청01";
	m_sGPU = "좋은 글카";
	m_sCPU = "좋은 씨피유";
	m_bPower = true;
	m_iMemory = 16;
}

void Computer::PrintSpec()
{
	cout << "제품명: " << m_sComputerName << endl;
	cout << "현재 상태: ";
	if (m_bPower = true)
		cout << "On\n";
	else
		cout << "Off\n";
	cout << "그래픽 카드: " << m_sGPU << endl;
	cout << "CPU: " << m_sCPU << endl;
	cout << "메모리: " << m_iMemory << "G\n";
}

Computer::~Computer()
{
}
