#include <iostream>

template <typename GOHOME>
void Plus(GOHOME dkanrjsk, GOHOME dkanrjsk2)
{
	if (dkanrjsk > dkanrjsk2)
		std::cout << "�� ū ��: " << dkanrjsk << "\n";
	else if (dkanrjsk < dkanrjsk2)
		std::cout << "�� ū ��: " << dkanrjsk2 << "\n";
	else if (dkanrjsk == dkanrjsk2)
		std::cout << "�� ���� ũ��� ����.\n";
}


int main()
{
	int Input1, Input2;
	std::cout << "�ƹ��ų� �Է�1: ";
	std::cin >> Input1;
	std::cout << "�ƹ��ų� �Է�2: ";
	std::cin >> Input2;

	Plus(Input1, Input2);

	return 0;
}