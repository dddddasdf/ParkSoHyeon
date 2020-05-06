#include "Word.h"


Word::Word()
{

}

void Word::InitNodes()
{
	FirstNode = new WordStatus;
	LastNode = new WordStatus;

	FirstNode->iXPos = DUMMYPOSITION;
	FirstNode->iYPos = DUMMYPOSITION;
	FirstNode->sWord = "";
	FirstNode->Next = NULL;

	LastNode->iXPos = DUMMYPOSITION;
	LastNode->iYPos = DUMMYPOSITION;
	LastNode->sWord = "";
	LastNode->Next = NULL;

	LastNode = FirstNode;
}

void Word::MakeNewWordStruct(string NewWord)
{
	if (FirstNode->sWord == "")
	{
		FirstNode->sWord = NewWord;
		FirstNode->iXPos = rand() % (WIDTH * 2);
		if ((FirstNode->sWord.length() + FirstNode->iXPos) > (WIDTH * 2))
		{
			FirstNode->iXPos -= (FirstNode->sWord.length() + FirstNode->iXPos) - (WIDTH * 2);
		}
			
		FirstNode->iYPos = 0;
		FirstNode->iIsHaveItem = rand() % MAKE_ITEM;
	}
	else
	{
		WordStatus *NewWordTmp = new WordStatus;
		NewWordTmp->sWord = NewWord;
		NewWordTmp->iXPos = rand() % (WIDTH * 2);
		if ((NewWordTmp->sWord.length() + NewWordTmp->iXPos) > (WIDTH * 2))
		{
			NewWordTmp->iXPos -= NewWordTmp->sWord.length();
		}

		NewWordTmp->iYPos = 0;
		NewWordTmp->iIsHaveItem = rand() % MAKE_ITEM;
		NewWordTmp->Next = NULL;
		LastNode->Next = NewWordTmp;
		LastNode = NewWordTmp;
	}
}

bool Word::Dropping()
{
	bool bTmp = false;	//만약 첫번째 노드가 땅에 닿는다면 true를 반환해서 피를 깔 수 있도록 한다

	if (FirstNode->sWord != "")
	{
		WordStatus *Tmp = FirstNode;

		while (1)
		{
			Tmp->iYPos++;

			if (FirstNode->iYPos == HORIZON)
			{
				WordStatus *TmpH = FirstNode;
				FirstNode = FirstNode->Next;
				Tmp = FirstNode;
				Tmp->iYPos++;
				TmpH->iIsHaveItem = 0;
				TmpH->iXPos = DUMMYPOSITION;
				TmpH->iYPos = DUMMYPOSITION;
				bTmp = true;	//false이던 bTmp를 true로 변환
				delete TmpH;
			}

			if (Tmp->Next == NULL)
				break;

			Tmp = Tmp->Next;
		}
	}
	
	return bTmp;
}

void Word::Print()
{
	WordStatus *Tmp = FirstNode;
	ChangeColor(COLOR_BLUE);

	while (1)
	{
		gotoxy(Tmp->iXPos, Tmp->iYPos);
		cout << Tmp->sWord;

		if (Tmp->Next == NULL)
			break;

		Tmp = Tmp->Next;
	}
	ORIGINAL
}

int Word::CheckCorrect(string GetWord)
{
	if (FirstNode->sWord == "")
		return NO_ACCORDING_STRING;	//첫번째 노드가 비어있으면 아무 단어도 없으니 바로 반환

	WordStatus *TmpCurrent = FirstNode;

	if (FirstNode->sWord == GetWord)
	{
		FirstNode = FirstNode->Next;
		int iTmpItemNumber = TmpCurrent->iIsHaveItem;
		TmpCurrent->iIsHaveItem = 0;
		TmpCurrent->iXPos = DUMMYPOSITION;
		TmpCurrent->iYPos = DUMMYPOSITION;
		delete TmpCurrent;
		return iTmpItemNumber;
	}
	else
		TmpCurrent = TmpCurrent->Next;
	
	WordStatus *TmpPrevious = TmpCurrent;	//이전 노드로 가는 참조 없이 단방향이기 때문에 이전 노드의 주소를 저장할 별도의 임시 구조체 필요

	while (1)
	{
		if (TmpCurrent->sWord == GetWord)
		{
			TmpPrevious->Next = TmpCurrent->Next;	//지워야 할 노드의 이전 노드의 다음 노드를 지워야 할 노드의 다음 노드로 변경
			int iTmpItemNumber = TmpCurrent->iIsHaveItem;
			TmpCurrent->iIsHaveItem = 0;
			TmpCurrent->iXPos = DUMMYPOSITION;
			TmpCurrent->iYPos = DUMMYPOSITION;
			delete TmpCurrent;
			return iTmpItemNumber;
		}
		
		if (TmpCurrent->Next == NULL)
			break;
		
		TmpPrevious = TmpCurrent;
		TmpCurrent = TmpCurrent->Next;
	}

	return NO_ACCORDING_STRING;
}

void Word::DeleteAllWords()
{
	if (FirstNode->sWord != "")
	{
		while (1)
		{
			if (FirstNode == LastNode)
			{
				delete FirstNode;
				break;
			}
			WordStatus *Tmp = FirstNode;
			FirstNode = FirstNode->Next;
			Tmp->iXPos = DUMMYPOSITION;
			Tmp->iYPos = DUMMYPOSITION;
			Tmp->iIsHaveItem = 0;
			Tmp->sWord = "";
			delete Tmp;
		}
	}
	else
		delete FirstNode;

}

Word::~Word()
{

}