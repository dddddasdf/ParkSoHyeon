#include "StudentManager.h"

StudentManager* StudentManager::m_hThis = NULL;

StudentManager::StudentManager()
{

}

int StudentManager::GetSize()
{
	return StudentList.size();
}

void StudentManager::NewData()
{
	std::cout << "=========================================================================\n";
	StudentList.push_back(new Student);
}

void StudentManager::ShowList()
{
	for (auto iter = StudentList.begin(); iter != StudentList.end(); iter++)
	{
		std::cout << "=========================================================================\n";
		std::cout << "�л� �̸�: " << (*iter)->ReturnName() << "\n";
		std::cout << "�л� �г�: " << (*iter)->ReturnValue(INFO_GRADE) << "\n";
		std::cout << "�л� ��ȣ: " << (*iter)->ReturnValue(INFO_NUMBER) << "\n";
		std::cout << "���� ����: " << (*iter)->ReturnValue(INFO_KOREANSCORE) << "\n";
		std::cout << "���� ����: " << (*iter)->ReturnValue(INFO_MATHSCORE) << "\n";
		std::cout << "���� ����: " << (*iter)->ReturnValue(INFO_ENGLISHSCORE) << "\n";
		std::cout << "=========================================================================\n";
	}
}

StudentManager::~StudentManager()
{
	for (auto iter = StudentList.begin(); iter != StudentList.end(); iter++)
		delete (*iter);
}