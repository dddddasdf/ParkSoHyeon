#include <iostream>

template <typename GOHOME>
void Plus(GOHOME dkanrjsk, GOHOME dkanrjsk2)
{
	if (dkanrjsk > dkanrjsk2)
		std::cout << "더 큰 수: " << dkanrjsk << "\n";
	else if (dkanrjsk < dkanrjsk2)
		std::cout << "더 큰 수: " << dkanrjsk2 << "\n";
	else if (dkanrjsk == dkanrjsk2)
		std::cout << "두 수의 크기는 같다.\n";
}


int main()
{
	int Input1, Input2;
	std::cout << "아무거나 입력1: ";
	std::cin >> Input1;
	std::cout << "아무거나 입력2: ";
	std::cin >> Input2;

	Plus(Input1, Input2);

	return 0;
}