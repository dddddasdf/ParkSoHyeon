#define _CRT_SECURE_NO_WARNINGS
#include "ArrayList.h"

int main()
{
	List *ListTmp = (List*)malloc(sizeof(List));
	ListInit(ListTmp);

	int iSize = 0;
	printf("���ϴ� ���� �Է�: ");
	scanf("%d", &iSize);

	for (int i = 1; i <= iSize; i++)
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

	printf("������ %d\n", sum);

	int iTmp = 0;
	printf("�����ϱ� ���ϴ� ��� �Է�: ");
	scanf("%d", &iTmp);

	int j = ListTmp->numOfData;
	for (int i = 0; i < j; i++)
	{
		tmp = 0;
		if (i == 0)
			LFirst(ListTmp, &tmp);
		else
			LNext(ListTmp, &tmp);

		if (0 != tmp && 0 == tmp % iTmp)
		{
			tmp = LRemove(ListTmp);
			printf("%d ����\n", tmp);
		}
	}
	iTmp = 0;
	printf("�����ϱ� ���ϴ� ��� �Է�: ");
	scanf("%d", &iTmp);
	j = ListTmp->numOfData;
	for (int i = 0; i < j; i++)
	{
		if (i == 0)
			LFirst(ListTmp, &tmp);
		else
			LNext(ListTmp, &tmp);

		if (0 != tmp && 0 == tmp % iTmp)
		{
			tmp = LRemove(ListTmp);
			printf("%d ����\n", tmp);
		}
	}

	printf("���� �迭 ���� �ִ� ����: ");
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