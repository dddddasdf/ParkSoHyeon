#include <iostream>

void Recursion_Hanoi(int *ArrayLeft, int *ArrayMiddle, int *ArrayRight, int NumberofLeft, int Number)
{
	if (ArrayLeft[1] == 0 && ArrayRight[0] == 0)
	{
		ArrayRight[0] = ArrayLeft[0];
		ArrayLeft[0] = 0;

		//PrintElements(ArrayLeft, ArrayMiddle, ArrayRight, Number);
	}
	else
	{

	}
}

void PrintElements(int *ArrayLeft, int *ArrayMiddle, int *ArrayRight, int Number)
{
	std::cout << "좌측: ";
	for (int i = 0; i < Number; i++)
		std::cout << ArrayLeft[i] << " ";
	std::cout << "\n";

	std::cout << "중간: ";
	for (int i = 0; i < Number; i++)
		std::cout << ArrayMiddle[i] << " ";
	std::cout << "\n";

	std::cout << "우측: ";
	for (int i = 0; i < Number; i++)
		std::cout << ArrayRight[i] << " ";
	std::cout << "\n\n";
}

void CreateArray(int Number)
{
	int *Array_Left = new int[Number];
	int *Array_Middle = new int[Number];
	int *Array_Right = new int[Number];

	for (int i = 0; i < Number; i++)
	{
		Array_Left[i] = Number - i;
		Array_Middle[i] = 0;
		Array_Right[i] = 0;
	}
	
	PrintElements(Array_Left, Array_Middle, Array_Right, Number);
}

int main()
{
	std::cout << "배치시킬 원반의 개수를 입력: ";
	int iNumberofPlate = 0;
	std::cin >> iNumberofPlate;

	CreateArray(iNumberofPlate);

	return 0;
}