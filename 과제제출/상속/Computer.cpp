#include "Computer.h"



Computer::Computer()
{
	m_sComputerName = "â����û01";
	m_sGPU = "���� ��ī";
	m_sCPU = "���� ������";
	m_bPower = true;
	m_iMemory = 16;
}

void Computer::PrintSpec()
{
	cout << "��ǰ��: " << m_sComputerName << endl;
	cout << "���� ����: ";
	if (m_bPower = true)
		cout << "On\n";
	else
		cout << "Off\n";
	cout << "�׷��� ī��: " << m_sGPU << endl;
	cout << "CPU: " << m_sCPU << endl;
	cout << "�޸�: " << m_iMemory << "G\n";
}

Computer::~Computer()
{
}
