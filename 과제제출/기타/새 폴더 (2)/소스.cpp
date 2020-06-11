#include <iostream>

struct Test
{
	int x;
	Test *Next;
};

void Recursion(Test *Tmpp)
{
	if (Tmpp->Next != NULL)
	{
		Recursion(Tmpp->Next);
		delete Tmpp;
	}
	else
		delete Tmpp;
}

void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
	
	Test *Head;
	Head = NULL;

	for (int i = 0; i <= 10; i++)
	{
		Test *NewTest;
		NewTest = new Test;
		NewTest->x = i;
		NewTest->Next = NULL;

		if (Head == NULL)
		{
			Head = NewTest;
		}
		else
		{
			Test *Tmp;
			Tmp = Head;

			while (1)
			{
				if (Tmp->Next == NULL)
					break;
				Tmp = Tmp->Next;
			}

			Tmp->Next = NewTest;
		}

		std::cout << i << "ȣ�� ���� ����\n";
	}

	std::cout << "\nŽ�� ����\n";
	
	Test *Tmp;
	Tmp = Head;
	while (1)
	{
		std::cout << "���� " << Tmp->x << "ȣ��\n";
		if (Tmp->Next == NULL)
			break;
		
		Tmp = Tmp->Next;
	}

	std::cout << "Ž�� �Ϸ�\n";

	
	Tmp = Head;

	Recursion(Tmp);

	std::cout << "\n���� �Ϸ�\n";
}