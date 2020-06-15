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
	system("cls");
	cout << "제품명: " << m_sComputerName << endl;
	cout << "현재 상태: ";
	if (m_bPower = true)
		cout << "On\n";
	else
		cout << "Off\n";
	cout << "그래픽 카드: " << m_sGPU << endl;
	cout << "CPU: " << m_sCPU << endl;
	cout << "메모리: " << m_iMemory << "G\n";
	system("pause>null");
}

void Computer::Functions()
{
	int Select;
	while (1)
	{
		system("cls");
		cout << "1. 계산기\n";
		cout << "2. 메모장\n";
		cout << "3. 그림판\n";
		cout << "4. 메인화면\n";
		cout << "선택 >>>> ";
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
			cout << "Error: 제시된 메뉴 번호만을 입력하여 주십시오...\n";
			break;
		}
	}
}

Computer::~Computer()
{
}
