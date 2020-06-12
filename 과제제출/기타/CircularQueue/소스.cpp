#include <iostream>

template <typename dkanrjsk>
class Queue
{
private:
	dkanrjsk *Front, *Rear;
	int size;
public:
	Queue() { int size = 5; Init(); }
	Queue(int s) { size = s; Front = new dkanrjsk[size]; Rear = new dkanrjsk[size]; Init(); }
	void Init();
	void Menu();
	void Push(dkanrjsk Value);
	void Pop();
	bool IsEmpty();
};

template <typename dkanrjsk>
void Queue<dkanrjsk>::Init()
{
	for (int i; i < size; i++)
		dkanrjsk[i] = NULL;
}

template <typename dkanrjsk>
void Queue<dkanrjsk>::Push(dkanrjsk Value)
{
	if (Front == Rear)
	{
		*Front = Value;
		*Rear = Value;
		Rear++;
	}
	else if (IsEmpty() == false)
	{
		*Rear = Value;
		Rear++;
	}
}

template <typename dkanrjsk>
void Queue<dkanrjsk>::Pop()
{
	if (Front != Rear)
	{
		std::cout << *Front << "\n";

	}
	else
		std::cout << "큐 비어있음\n";
}

template <typename dkanrjsk>
bool Queue<dkanrjsk>::IsEmpty()
{
	if (Rear == dkanrjsk[size - 1])
	{
		std::cout << "큐 다 참\n";
		return true;
	}
	else
		return false;
}


void main()
{

}