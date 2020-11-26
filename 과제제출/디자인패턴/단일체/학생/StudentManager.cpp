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
		std::cout << "학생 이름: " << (*iter)->ReturnName() << "\n";
		std::cout << "학생 학년: " << (*iter)->ReturnValue(INFO_GRADE) << "\n";
		std::cout << "학생 번호: " << (*iter)->ReturnValue(INFO_NUMBER) << "\n";
		std::cout << "국어 성적: " << (*iter)->ReturnValue(INFO_KOREANSCORE) << "\n";
		std::cout << "수학 성적: " << (*iter)->ReturnValue(INFO_MATHSCORE) << "\n";
		std::cout << "영어 성적: " << (*iter)->ReturnValue(INFO_ENGLISHSCORE) << "\n";
		std::cout << "=========================================================================\n";
	}
}

StudentManager::~StudentManager()
{
	for (auto iter = StudentList.begin(); iter != StudentList.end(); iter++)
		delete (*iter);
}