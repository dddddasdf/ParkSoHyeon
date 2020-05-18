#include <iostream>

void Hanoi(int number, char from, char tmp, char to)
{
	if (number == 1)
		std::cout << "원반1을 " << from << "에서 " << to << "로 이동\n";
	else
	{
		Hanoi(number - 1, from, to, tmp);
		std::cout << "원반" << number << "를 " << from << "에서 " << to << "로 이동\n";
		Hanoi(number - 1, tmp, from, to);
	}
}

int main()
{
	char from = 'A';
	char tmp = 'B';
	char to = 'C';

	Hanoi(4, from, tmp, to);



	return 0;
}