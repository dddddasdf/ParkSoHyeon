#include <iostream>

class Test
{
private:
	int x;

	Test *Next;
public:
	Test() { std::cout << "내용물 초기화\t"; }
	void operator = (Test *tmp);
	void Create(int i) { std::cout << i << "호기 생성\n"; x = i; Next = NULL; }
	bool IsNull() { if (Next == NULL) return true; 
	else return false; }
	Test GoNext() { return *Next; }
	void Connect() {  std::cout << "연결 성공\n"; }
	void Call() { std::cout << "다음 호기 호출\n"; }
};

void Test::operator = (Test *tmp)
{
	this->Next = tmp;
}

void main()
{
	//_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	Test *T = new Test;
	Test *Head = new Test;

	std::cout << "대가리 생성\n";

	for (int i = 0; i <= 10; i++)
	{
		(T + i)->Create(i);

		if (i == 0)
			Head = (T + i);
		else
		{
			Test *Tmp;
			Tmp = Head;
			for (int j = 0; ; j++)
			{
				if (Tmp->IsNull() == true)
				{
					*(T + j) = (T + i);
					break;
				}
				else
				{
					Tmp = &Tmp->GoNext();
				}
			}
		}
	}
}