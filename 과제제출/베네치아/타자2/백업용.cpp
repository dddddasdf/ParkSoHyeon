//{
//for (int i = 0; i < iLines; i++)
//	getline(SynopsisText, SynopsisArr[i]);
//
//int iPrintLine = 0;	//��� ���� ���� 10�ٿ� �����ϸ� ����� ���۵Ǵ� �迭�� ���� �ɷ� �Ѿ �� �ְ�
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
////������ ����ؾ� �ϴ� ���� 10�� ����
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

//���� �� �迭 ���� �ó�ý� ���
//�Ʒ��� ����ť ���� ���·� �ó�ý� ���
//����ť ��� �Ẽ�� �ߴµ� ������ �ʹ� ���ؼ� �׳� ������ϱ�� �� �޸𸮰� ���ڶ�� �͵� �ƴϰ�...

//{
//ChangeColor(COLOR_BLUE);
//
//gotoxy(60, 27);
//cout << "��ŵ�ϱ�: SŰ";
//
//int iTopY = 18;	//9	//���� 10
//
//int iLines;
//
//SynopsisText >> iLines;
//
////string *SynopsisArr = new string[iLines];	//string �迭 ���� ������ ���پ� �� �������
//
//string SynopsisQueue[QUEUESIZE];	//���� ť ���·� �ó�ý� ���� ���� �� ���
//int iFront = 0, iRear = 0;
////����ڰ� ���� �����͸� �ְ� ���� �� �ƴϹǷ� ��ť ��ť �Լ� ���� ������ �����Ѵ�
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
//			return;	//��ŵ Ű �Է½� �ó�ý� ��� �Լ� Ż��
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