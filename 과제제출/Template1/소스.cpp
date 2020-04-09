#include <iostream>

template <typename GOHOME>
void Plus(GOHOME dkanrjsk)
{
	GOHOME Result;

	Result = dkanrjsk + 1;
	std::cout << "결과: " << dkanrjsk << " + 1 = " << Result << "\n";
}


int main()
{
	int Input;
	std::cout << "아무거나 입력: ";
	std::cin >> Input;

	Plus(Input);

	return 0;
}