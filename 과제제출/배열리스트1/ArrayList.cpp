#include "ArrayList.h"


void CreateIntArray()
{
	int *ArrayTmp= new int[LIST_SIZE];
	int NumberOfData = LIST_SIZE;	//������ ����

	InitIntArray(ArrayTmp);
	SumIntArray(ArrayTmp, NumberOfData);
	RemoveIntElement(ArrayTmp, 2, NumberOfData);
	RemoveIntElement(ArrayTmp, 3, NumberOfData);
	SearchIntArray(ArrayTmp, NumberOfData);
	FreeIntArray(ArrayTmp);
}

void InitIntArray(int *Array)
{
	for (int i = 0; i < LIST_SIZE; i++)
		Array[i] = (i + 1);
}

void SearchIntArray(int *Array, int NumberOfData)
{
	for (int i = 0; i < NumberOfData; i++)
		std::cout << Array[i] << " ";
	std::cout << "\n";
}

void SumIntArray(int *Array, int NumberOfData)
{
	int iTmp = 0;
	for (int i = 0; i < NumberOfData; i++)
		iTmp += Array[i];

	std::cout << "�迭 ������ �� ���� " << iTmp << "\n";
}

void RemoveIntElement(int *Array, int Condition, int &NumberOfData)
{
	for (int i = 0; i < LIST_SIZE; i++)
	{
		if (0 == (Array[i] % Condition))
		{
			for (int j = i; j < LIST_SIZE - 1; j++)
			{
				if (j + 1 == (NumberOfData - 1))
				{
					Array[j] = Array[j + 1];
					Array[j + 1] = 0;
					break;
				}
				else
					Array[j] = Array[j + 1];
			}
			NumberOfData--;
		}
	}

	std::cout << Condition << "�� ����� �ش��ϴ� ���� ���� �Ϸ�\n";
}

void FreeIntArray(int *Array)
{
	delete[] Array;
}