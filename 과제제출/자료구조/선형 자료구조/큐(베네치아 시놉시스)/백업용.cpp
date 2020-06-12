//{
//for (int i = 0; i < iLines; i++)
//	getline(SynopsisText, SynopsisArr[i]);
//
//int iPrintLine = 0;	//출력 중인 줄이 10줄에 도달하면 출력이 시작되는 배열이 다음 걸로 넘어갈 수 있게
//
//for (int i = 0; i < iLines; i++)
//{
//	Sleep(800);
//	CleanParticularArea(30, 100, 8, 19);
//	if (_kbhit())
//	{
//		cIsSkip = _getch();
//		if (cIsSkip == 'S' || cIsSkip == 's')
//			return;
//	}
//	if (i < 10)
//	{
//		int YTmp = 0;
//		for (int j = iPrintLine; j <= i; j++)
//		{
//			gotoxy(WIDTH - (SynopsisArr[j].length() / 2), iTopY + YTmp);
//			cout << SynopsisArr[j];
//			YTmp++;
//		}
//		if (iTopY > 9)
//			iTopY--;
//	}
//	else
//	{
//		iPrintLine++;
//		int YTmp = 0;
//		for (int j = iPrintLine; j <= i; j++)
//		{
//			gotoxy(WIDTH - (SynopsisArr[j].length() / 2), iTopY + YTmp);
//			cout << SynopsisArr[j];
//			YTmp++;
//		}
//	}
//}
//
////앞으로 출력해야 하는 줄이 10줄 이하
//for (int i = 1; i < 10; i++)
//{
//	Sleep(800);
//	CleanParticularArea(30, 100, 8, 19);
//	int YTmp = 0;
//	for (int j = iLines - (10 - i); j < iLines; j++)
//	{
//		gotoxy(WIDTH - (SynopsisArr[j].length() / 2), iTopY + YTmp);
//		cout << SynopsisArr[j];
//		YTmp++;
//	}
//}
//
//Sleep(700);
//CleanParticularArea(15, 50, 8, 19);
//}

//위는 깡 배열 만들어서 시놉시스 출력
//아래는 원형큐 응용 형태로 시놉시스 출력
//원형큐 출력 써볼려 했는데 깜빡임 너무 심해서 그냥 깡출력하기로 함 메모리가 모자라는 것도 아니고...

//{
//ChangeColor(COLOR_BLUE);
//
//gotoxy(60, 27);
//cout << "스킵하기: S키";
//
//int iTopY = 18;	//9	//길이 10
//
//int iLines;
//
//SynopsisText >> iLines;
//
////string *SynopsisArr = new string[iLines];	//string 배열 만들어서 깡으로 한줄씩 다 집어넣음
//
//string SynopsisQueue[QUEUESIZE];	//원형 큐 형태로 시놉시스 문장 저장 및 출력
//int iFront = 0, iRear = 0;
////사용자가 직접 데이터를 넣고 빼는 게 아니므로 인큐 디큐 함수 별도 생성은 생략한다
//
//bool bIsEnd = false;
//
//getline(SynopsisText, SynopsisQueue[0]);
//iRear++;
//gotoxy(WIDTH - (SynopsisQueue[0].length() / 2), iTopY);
//cout << SynopsisQueue[0];
//iTopY--;
//
//while (!bIsEnd)
//{
//	if (_kbhit())
//	{
//		if (_getch() == 's' || _getch() == 'S')
//			return;	//스킵 키 입력시 시놉시스 출력 함수 탈출
//	}
//
//	Sleep(800);
//	CleanParticularArea(15, 100, 8, 19);
//
//	if (!SynopsisText.eof())
//	{
//		getline(SynopsisText, SynopsisQueue[iRear]);
//		iRear = (iRear + 1) % QUEUESIZE;
//
//		int YTmp = 0;
//
//		for (int i = iFront; (i % QUEUESIZE) != iRear; i++)
//		{
//			gotoxy(WIDTH - (SynopsisQueue[(i % QUEUESIZE)].length() / 2), iTopY + YTmp);
//			cout << SynopsisQueue[(i % QUEUESIZE)];
//			YTmp++;
//		}
//
//		if (iFront == (iRear + 1) % QUEUESIZE)
//			iFront = (iFront + 1) % QUEUESIZE;
//	}
//	else
//	{
//		int YTmp = 0;
//
//		for (int i = iFront; (i % QUEUESIZE) != iRear; i++)
//		{
//			gotoxy(WIDTH - (SynopsisQueue[(i % QUEUESIZE)].length() / 2), iTopY + YTmp);
//			cout << SynopsisQueue[(i % QUEUESIZE)];
//			YTmp++;
//		}
//
//		if (iFront != (iRear + 1) % QUEUESIZE)
//			iFront = (iFront + 1) % QUEUESIZE;
//		else
//			bIsEnd = true;
//	}
//
//	if (iTopY > 9)
//		iTopY--;
//}
//
//SynopsisText.close();
//CleanParticularArea(15, 50, 8, 19);
//ORIGINAL
//}



////////////////////////////////////////////////////////////////////////////////////////////////////