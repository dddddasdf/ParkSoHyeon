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
	FirstNode->Previous = NULL;

	LastNode->iXPos = DUMMYPOSITION;
	LastNode->iYPos = DUMMYPOSITION;
	LastNode->sWord = "";
	LastNode->Next = NULL;
	LastNode->Previous = NULL;

	LastNode = FirstNode;
}

void Word::MakeNewWordStruct(string NewWord)
{
	if (FirstNode->sWord == "")
	{
		FirstNode->sWord = NewWord;
		FirstNode->iXPos = rand() % ((WIDTH * 2) - 1);
		if ((FirstNode->sWord.length() + FirstNode->iXPos) > (WIDTH * 2))
		{
			FirstNode->iXPos -= (FirstNode->sWord.length() + FirstNode->iXPos) - (WIDTH * 2);
		}
			
		FirstNode->iYPos = 0;
		int iTmp = rand() % 10;
		if (iTmp == 0 || iTmp > 5)
			FirstNode->iIsHaveItem = ITEM_NULL;
		else
			FirstNode->iIsHaveItem = iTmp;
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
		int iTmp = rand() % 10;
		if (iTmp == 0 || iTmp > 5)
			FirstNode->iIsHaveItem = ITEM_NULL;
		else
			FirstNode->iIsHaveItem = iTmp;
		NewWordTmp->Next = NULL;
		LastNode->Next = NewWordTmp;
		NewWordTmp->Previous = LastNode;
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
			CleanEachWord(Tmp->iXPos, Tmp->iYPos, Tmp->sWord.length());
			Tmp->iYPos++;

			if (FirstNode->iYPos == HORIZON)
			{
				WordStatus *TmpH = FirstNode;
				FirstNode = FirstNode->Next;
				Tmp = FirstNode;
				TmpH->iIsHaveItem = 0;
				TmpH->iXPos = DUMMYPOSITION;
				TmpH->iYPos = DUMMYPOSITION;
				bTmp = true;	//false�̴� bTmp�� true�� ��ȯ
				delete TmpH;

				if (Tmp->Next == NULL)
					break;

				continue;
			}

			if (Tmp->Next == NULL)
				break;
			
			Tmp = Tmp->Next;
		}
	}
	
	return bTmp;
}

void Word::Print(bool IsHiding)
{
	WordStatus *Tmp = FirstNode;

	if (IsHiding == false)
	{
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
	else if (IsHiding == true)
	{
		ChangeColor(COLOR_BLUE);

		while (1)
		{
			gotoxy(Tmp->iXPos, Tmp->iYPos);
			cout << "(^^)      ";	//�ܾ� ������ �ߵ���
			
			if (Tmp->Next == NULL)
				break;

			Tmp = Tmp->Next;
		}
		ORIGINAL
	}
}

int Word::CheckCorrect(string GetWord)
{
	if (FirstNode->sWord == "")
		return NO_ACCORDING_STRING;	//ù��° ��尡 ��������� �ƹ� �ܾ ������ �ٷ� ��ȯ

	WordStatus *TmpCurrent = FirstNode;

	while (1)
	{
		if (TmpCurrent->sWord == GetWord)
		{
			if (TmpCurrent == FirstNode)
			{
				if (FirstNode->Next != NULL)
				{
					FirstNode = FirstNode->Next;
					FirstNode->Previous = NULL;	//ù��° ��带 ���� ���� ������ ���� ���� ����� ���� �ܰ�� ���� ���� ���´�
				}
				else
				{
					int iTmpItemNumber = FirstNode->iIsHaveItem;
					CleanEachWord(FirstNode->iXPos, FirstNode->iYPos, (FirstNode->sWord).length());
					FirstNode->iIsHaveItem = 0;
					FirstNode->iXPos = DUMMYPOSITION;
					FirstNode->iYPos = DUMMYPOSITION;
					FirstNode->sWord = "";
					return iTmpItemNumber;	//ù��° ��常 �����ϰ� �ְ� �ش� ��带 ���� ���̸� ��� ���븸 û���Ѵ�
				}
			}
			else if (TmpCurrent == LastNode)
			{
				LastNode = TmpCurrent->Previous;
				LastNode->Next = NULL;	//������ ��带 ���� ���� ������ ���� ���� ����� ���� �ܰ�� ���� ���� ���´�
			}
			else
			{
				(TmpCurrent->Previous)->Next = TmpCurrent->Next;
				(TmpCurrent->Next)->Previous = TmpCurrent->Previous;	//���� ����� ���� ���� ���� ��带 �̾��ش�
			}
			int iTmpItemNumber = TmpCurrent->iIsHaveItem;
			CleanEachWord(TmpCurrent->iXPos, TmpCurrent->iYPos, (TmpCurrent->sWord).length());
			TmpCurrent->iIsHaveItem = 0;
			TmpCurrent->iXPos = DUMMYPOSITION;
			TmpCurrent->iYPos = DUMMYPOSITION;
			delete TmpCurrent;
			return iTmpItemNumber;
		}
		if (TmpCurrent->Next == NULL)
			break;

		TmpCurrent = TmpCurrent->Next;
	}

	return NO_ACCORDING_STRING;
}

void Word::CleanEachWord(int iXPos, int iYPos, int WordLength)
{
	gotoxy(iXPos, iYPos);
	for (int i = 0; i <= WordLength; i++)
		cout << "��";
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