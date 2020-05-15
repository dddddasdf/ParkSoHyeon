#include <iostream>

void Search(int *Array, int StartIndex, int EndIndex, int target)
{
	int Middle = (StartIndex + EndIndex) / 2;

	if (Array[Middle] == target)
	{
		std::cout << "찾는 숫자의 인덱스 번호는 " << Middle;
	}
	else
	{
		if (StartIndex <= EndIndex)
		{
			if (Array[Middle] > target)
			{
				Search(Array, StartIndex, Middle - 1, target);
			}
			else if (Array[Middle] < target)
			{
				Search(Array, Middle + 1, EndIndex, target);
			}
		}
		else
			std::cout << "찾는 숫자 없음";
	}
}

int main()
{
	int i = 0;
	std::cout << "숫자 입력: ";
	std::cin >> i;

	int *Array = new int[i];
	for (int x = 0; x < i; x++)
		Array[x] = x * x;
	
	std::cout << "배열 생성\n";
	int j;

	std::cout << "찾고 싶은 숫자를 입력: ";
	std::cin >> j;
	
	Search(Array, 0, i - 1, j);

	delete[] Array;

	return 0;
}