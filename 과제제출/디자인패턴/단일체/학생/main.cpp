#include "School.h"
#include "Student.h"

int main()
{
	int iSelect = 0;

	while (iSelect != 3)
	{
		std::cout << "��ϵ� �ڷ� ����: " << Student::Get << std::endl;
		std::cout << "-----�޴�\n";
		std::cout << "1. �л� ������ �Է�\n";
		std::cout << "2. ��ϵ� �л� ���� �ϰ� ��ȸ\n";
		std::cout << "3. ����\n";

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