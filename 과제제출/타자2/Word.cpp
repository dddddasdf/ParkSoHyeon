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
	bool bTmp = false;	//���� ù��° ��尡 ���� ��´ٸ� true�� ��ȯ�ؼ� �Ǹ� �� �� �ֵ��� �Ѵ�

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
				bTmp = true;	//false�̴� bTmp�� true�� ��ȯ
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
		return NO_ACCORDING_STRING;	//ù��° ��尡 ��������� �ƹ� �ܾ ������ �ٷ� ��ȯ

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
	
	WordStatus *TmpPrevious = TmpCurrent;	//���� ���� ���� ���� ���� �ܹ����̱� ������ ���� ����� �ּҸ� ������ ������ �ӽ� ����ü �ʿ�

	while (1)
	{
		if (TmpCurrent->sWord == GetWord)
		{
			TmpPrevious->Next = TmpCurrent->Next;	//������ �� ����� ���� ����� ���� ��带 ������ �� ����� ���� ���� ����
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