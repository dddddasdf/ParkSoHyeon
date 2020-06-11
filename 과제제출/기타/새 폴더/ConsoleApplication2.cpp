#include <iostream>

class Test
{
private:
	int x;

	Test *Next;
public:
	Test() { }
	void Create(int i) { std::cout << i << "호기 생성\n"; x = i; Next = NULL; }
	bool IsNull() {
		if (Next == NULL) return true;
		else return false;
	}
	Test GoNext() {
		return *Next;
	}
	int ReturnNum() { return x; }
	void Connect(Test *tmp2) { 
		this->Next = tmp2; 
		std::cout << x << "호기에 연결 성공\n"; }
	void Call() { std::cout << "다음 호기 호출\n"; }
};


void main()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	Test *Head = new Test;
	Head = NULL;

	std::cout << "대가리 생성\n";

	for (int i = 0; i <= 10; i++)
	{
		Test *T;
		T = new Test;
		T->Create(i);

		if (Head == 0)
			Head = (T + i);
		else
		{
			Test *Tmp;
			Tmp = Head;
			
			while (1)
			{
				if (Tmp->IsNull() == true)
					break;
				Tmp = &Tmp->GoNext();
			}
			
			Tmp->Connect(T);
		}
	}

	std::cout << "정상적으로 수행 완료시 출력되는 문장";

	std::cout << "\n탐색 시작\n";

	Test *Tmp;
	Tmp = Head;

	while (1)
	{
		std::cout << "현재 " << Tmp->ReturnNum() << "호기\n";
		if (Tmp->IsNull() == NULL)
			break;

		Tmp = &Tmp->GoNext();
	}
}