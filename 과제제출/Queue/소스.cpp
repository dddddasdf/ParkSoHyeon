#include <iostream>

template <typename dkanrjsk>
class Queue
{
private:
	dkanrjsk *Front;
	int size;
public:
	Queue() { int size = 5; Init(); }
	Queue(int s) { size = s; Front = new dkanrjsk[size]; Init();  }
	void Init();
	void Menu();
	void Push(dkanrjsk Value);
	void Pop();
	bool IsEmpty();
};

template <typename dkanrjsk>
void Queue<dkanrjsk>::Init()
{
	for (int i = 0; i < size; i++)
		*(Front + i) = NULL;
}

template <typename dkanrjsk>
void Queue<dkanrjsk>::Menu()
{
	int Tmp;
	int iSelect;

	while (1)
	{
		std::cout << "1. ���� ����ֱ�\t2. ���� ����\t3. ����\n�Է�: ";
		std::cin >> iSelect;

		switch (iSelect)
		{
		case 1:
			std::cout << "�� �Է�: ";
			std::cin >> Tmp;
			Push(Tmp);
			break;
		case 2:
			Pop();
			break;
		case 3:
			return;
		}
		std::cout << "\n";
	}
}

template <typename dkanrjsk>
void Queue<dkanrjsk>::Push(dkanrjsk Value)
{
	if (*Front == NULL)
		*Front = Value;
	else if (IsEmpty() == false)
	{
		for (int i = 1; i < size; i++)
		{
			if (*(Front + i) == NULL)
			{
				*(Front + i) = Value;
				break;
			}
		}
	}
}

template <typename dkanrjsk>
void Queue<dkanrjsk>::Pop()
{
	if (*Front == NULL)
		std::cout << "ť �������\n";
	else
	{
		std::cout << "���: " << *Front << "\n";
		for (int i = 0; i < size; i++)
		{
			if (i != size - 1)
				*(Front + i) = *(Front + (i + 1));
			else
			{
				*(Front + i) = NULL;
				break;
			}

			if (*(Front + (i + 1)) == NULL)
				break;
		}
	}
}

template <typename dkanrjsk>
bool Queue<dkanrjsk>::IsEmpty()
{
	if (*(Front + (size -1)) != NULL)
	{
		std::cout << "ť �� ��\n";
		return true;
	}
	else
		return false;
}


void main()
{
	int Tmp;
	std::cout << "ť�� ũ�⸦ ����: ";
	std::cin >> Tmp;

	Queue <int> Q(Tmp);
	Q.Menu();
}