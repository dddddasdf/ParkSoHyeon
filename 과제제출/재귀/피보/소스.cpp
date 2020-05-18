#include <iostream>


int Fibo(int n)
{ 
	if (n == 1) 
		return 0; 
	else if (n == 2) 
		return 1; 
	else 
		return Fibo(n - 1) + Fibo(n - 2); 
}


int main()
{
	int i;
	std::cout << "숫자 입력: ";
	std::cin >> i;
	
	std::cout << Fibo(i);


	return 0;
}