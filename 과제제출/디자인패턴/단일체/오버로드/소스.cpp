#include <iostream>
#include <Windows.h>
#include "Singleton.h"

class TimeManager : public Singleton<TimeManager>
{
private:
	int m_iHour;
	int m_iMin;
public:
	TimeManager() { m_iHour = 0; m_iMin = 0; }
	TimeManager(int Hour, int Min);
	void ShowTime();
	void PlusTime(int Hour, int Minute);
	void operator + (TimeManager TimeAdd);
	~TimeManager() { m_iHour = NULL; m_iMin = NULL; }
};

TimeManager::TimeManager(int Hour, int Min)
{
	if (Min >= 60)
	{
		Hour += (Min / 60);
		Min = (Min % 60);
	}
	m_iHour = Hour;
	m_iMin = Min;
}

void TimeManager::ShowTime()
{
	std::cout << " �� ���� �ð���" << m_iHour << "�ð� " << m_iMin << "��\n";
}

void TimeManager::PlusTime(int Hour, int Minute)
{
	this->m_iHour += Hour;
	this->m_iMin += Minute;

	if (this->m_iMin >= 60)
	{
		this->m_iHour += (this->m_iMin);
		this->m_iMin = (this->m_iMin % 60);
	}
}

//������ �����ε��� ������ �� �Ծ,,, ���� �÷��� Ÿ�� ������ ����
void TimeManager::operator + (TimeManager TimeAdd)
{
	this->m_iHour += TimeAdd.m_iHour;
	this->m_iMin += TimeAdd.m_iMin;

	if (this->m_iMin >= 60)
	{
		this->m_iHour += (this->m_iMin);
		this->m_iMin = (this->m_iMin % 60);
	}
}
//�ٵ� ������� ����ü ����ϰԲ� �� �ǵ� ���� �ҿ��ΰ� �ʹ�

void main()
{
	int iDays = 1;
	TimeManager *TimeBase = new TimeManager;
	TimeBase = TimeManager::GetInstance();
	TimeManager *TimeTemporary = new TimeManager;	//����ü ������ ���� ������ Ŭ���� ��ü �ϳ� �� ����
	TimeTemporary = TimeManager::GetInstance();

	int iSelect;
	bool iClose = false;

	while (!iClose)
	{
		system("cls");
		
		TimeBase->ShowTime();

		std::cout << "=====���� �ð� ���� ���α׷�(" << iDays << "Day)=====\n";
		std::cout << "\t\t1. �ð� ���\n";
		std::cout << "\t\t2. ����\n";
		std::cout << "\t\t�Է�: ";
		std::cin >> iSelect;

		switch (iSelect)
		{
		default:
			std::cout << "������ �޴� ��ȣ���� �Է��Ͽ� �ֽʽÿ�...\n";
			system("pause>null");
			break;
		case 1:
		{
			int iAddHour, iAddMin;
			std::cout << "�ð�: ";
			std::cin >> iAddHour;
			std::cout << "��: ";
			std::cin >> iAddMin;
			
			//TimeManager TimeAdd(iAddHour, iAddMin);
			//TimeTemporary + TimeAdd;
			//TimeAdd.~TimeManager();
			TimeTemporary->PlusTime(iAddHour, iAddMin);
			//delete TimeTemporary;
			iDays++;
		}
			break;
		case 2:
			iClose = true;
			break;
		}
	}
}