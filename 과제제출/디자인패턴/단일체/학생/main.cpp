#include "School.h"
#include "Student.h"

int main()
{
	int iSelect = 0;

	while (iSelect != 3)
	{
		std::cout << "등록된 자료 개수: " << Student::Get << std::endl;
		std::cout << "-----메뉴\n";
		std::cout << "1. 학생 데이터 입력\n";
		std::cout << "2. 등록된 학생 정보 일괄 조회\n";
		std::cout << "3. 종료\n";

		std::cin >> iSelect;

		switch (iSelect)
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			return;
		}
	}

	return 0;
}