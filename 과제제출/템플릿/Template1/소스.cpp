#include <iostream>

template <typename GOHOME>
void Plus(GOHOME dkanrjsk)
{
	GOHOME Result;

	Result = dkanrjsk + 1;
	std::cout << "���: " << dkanrjsk << " + 1 = " << Result << "\n";
}


int main()
{
	int Input;
	std::cout << "�ƹ��ų� �Է�: ";
	std::cin >> Input;

	Plus(Input);

	return 0;
}