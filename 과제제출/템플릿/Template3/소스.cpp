#include <iostream>

template <typename GOHOME>
void Plus(GOHOME dkanrjsk, GOHOME dkanrjsk2, GOHOME dkanrjsk3)
{
	if (dkanrjsk > dkanrjsk2)
	{
		if (dkanrjsk > dkanrjsk3)
			std::cout << "���� ū ��: " << dkanrjsk << "\n";
		else
			std::cout << "���� ū ��: " << dkanrjsk3 << "\n";
	}
	else if (dkanrjsk < dkanrjsk2)
	{
		if (dkanrjsk2 > dkanrjsk3)
			std::cout << "���� ū ��: " << dkanrjsk2 << "\n";
		else
			std::cout << "���� ū ��: " << dkanrjsk3 << "\n";
	}
	else if (dkanrjsk == dkanrjsk2 && dkanrjsk2 == dkanrjsk3)
		std::cout << "�� ���� ũ��� ����.\n";
}


int main()
{
	int Input1, Input2, Input3;
	std::cout << "�ƹ��ų� �Է�1: ";
	std::cin >> Input1;
	std::cout << "�ƹ��ų� �Է�2: ";
	std::cin >> Input2;
	std::cout << "�ƹ��ų� �Է�3: ";
	std::cin >> Input3;

	Plus(Input1, Input2, Input3);

	return 0;
}