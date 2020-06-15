#include <iostream>

template <typename GOHOME>
void Plus(GOHOME dkanrjsk, GOHOME dkanrjsk2, GOHOME dkanrjsk3)
{
	if (dkanrjsk > dkanrjsk2)
	{
		if (dkanrjsk > dkanrjsk3)
			std::cout << "가장 큰 수: " << dkanrjsk << "\n";
		else
			std::cout << "가장 큰 수: " << dkanrjsk3 << "\n";
	}
	else if (dkanrjsk < dkanrjsk2)
	{
		if (dkanrjsk2 > dkanrjsk3)
			std::cout << "가장 큰 수: " << dkanrjsk2 << "\n";
		else
			std::cout << "가장 큰 수: " << dkanrjsk3 << "\n";
	}
	else if (dkanrjsk == dkanrjsk2 && dkanrjsk2 == dkanrjsk3)
		std::cout << "세 수의 크기는 같다.\n";
}


int main()
{
	int Input1, Input2, Input3;
	std::cout << "아무거나 입력1: ";
	std::cin >> Input1;
	std::cout << "아무거나 입력2: ";
	std::cin >> Input2;
	std::cout << "아무거나 입력3: ";
	std::cin >> Input3;

	Plus(Input1, Input2, Input3);

	return 0;
}