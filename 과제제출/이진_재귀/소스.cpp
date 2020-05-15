#include <iostream>

void Search(int *Array, int StartIndex, int EndIndex, int target)
{
	int Middle = (StartIndex + EndIndex) / 2;

	if (Array[Middle] == target)
	{
		std::cout << "ã�� ������ �ε��� ��ȣ�� " << Middle;
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
			std::cout << "ã�� ���� ����";
	}
}

int main()
{
	int i = 0;
	std::cout << "���� �Է�: ";
	std::cin >> i;

	int *Array = new int[i];
	for (int x = 0; x < i; x++)
		Array[x] = x * x;
	
	std::cout << "�迭 ����\n";
	int j;

	std::cout << "ã�� ���� ���ڸ� �Է�: ";
	std::cin >> j;
	
	Search(Array, 0, i - 1, j);

	delete[] Array;

	return 0;
}