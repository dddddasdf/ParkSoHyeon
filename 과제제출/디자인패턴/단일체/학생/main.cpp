#include "StudentManager.h"

int main()
{
	int iSelect = 0;

	while (iSelect != 3)
	{
		system("cls");
		std::cout << "��ϵ� �ڷ� ����: " << StudentManager::GetInstance()->GetSize() << std::endl;
		std::cout << "-----�޴�\n";
		std::cout << "1. �л� ������ �Է�\n";
		std::cout << "2. ��ϵ� �л� ���� �ϰ� ��ȸ\n";
		std::cout << "3. ����\n";

		std::cin >> iSelect;

		switch (iSelect)
		{
		case 1:
			StudentManager::GetInstance()->NewData();
			break;
		case 2:
			StudentManager::GetInstance()->ShowList();
			system("pause");
			break;
		case 3:
			StudentManager::DestoryThis();
			break;
		}
	}

	return 0;
}