#include "ArrayList.h"

int main()
{
	List *ListTmp = (List*)malloc(sizeof(List));
	ListInit(ListTmp);

	for (int i = 1; i <= 9; i++)
		LInsert(ListTmp, i);
		
	int sum = 0;
	int tmp;

	for (int i = 0; i < ListTmp->numOfData; i++)
	{
		tmp = 0;
		if (i == 0)
		{
			LFirst(ListTmp, &tmp);
			sum += tmp;
		}
		else
		{
			LNext(ListTmp, &tmp);
			sum += tmp;
		}
	}

	printf("총합은 %d\n", sum);

	int j = ListTmp->numOfData;
	for (int i = 0; i < j; i++)
	{
		tmp = 0;
		if (i == 0)
			LFirst(ListTmp, &tmp);
		else
			LNext(ListTmp, &tmp);

		if (0 != tmp && 0 == tmp % 2)
		{
			tmp = LRemove(ListTmp);
			printf("%d 삭제\n", tmp);
		}
	}
	j = ListTmp->numOfData;
	for (int i = 0; i < j; i++)
	{
		if (i == 0)
			LFirst(ListTmp, &tmp);
		else
			LNext(ListTmp, &tmp);

		if (0 != tmp && 0 == tmp % 3)
		{
			tmp = LRemove(ListTmp);
			printf("%d 삭제\n", tmp);
		}
	}

	printf("현재 배열 내에 있는 원소: ");
	for (int i = 0; i < ListTmp->numOfData; i++)
	{
		if (i == 0)
			LFirst(ListTmp, &tmp);
		else
			LNext(ListTmp, &tmp);

		printf("%d ", tmp);
	}

	free(ListTmp);

	return 0;
}