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
	system("cls");
	cout << "��ǰ��: " << m_sComputerName << endl;
	cout << "���� ����: ";
	if (m_bPower = true)
		cout << "On\n";
	else
		cout << "Off\n";
	cout << "�׷��� ī��: " << m_sGPU << endl;
	cout << "CPU: " << m_sCPU << endl;
	cout << "�޸�: " << m_iMemory << "G\n";
	system("pause>null");
}

void Computer::Functions()
{
	int Select;
	while (1)
	{
		system("cls");
		cout << "1. ����\n";
		cout << "2. �޸���\n";
		cout << "3. �׸���\n";
		cout << "4. ����ȭ��\n";
		cout << "���� >>>> ";
		cin >> Select;

		switch (Select)
		{
		case 1:
			system("calc");
			break;
		case 2:
			system("notepad");
			break;
		case 3:
			system("mspaint");
			break;
		case 4:
			return;
		default:
			cout << "Error: ���õ� �޴� ��ȣ���� �Է��Ͽ� �ֽʽÿ�...\n";
			break;
		}
	}
}

Computer::~Computer()
{
}
