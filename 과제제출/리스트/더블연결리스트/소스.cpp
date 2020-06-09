#include "Functions.h"

int main()
{
	List NewList;
	Value *DataTmp;
	ListInit(&NewList);
	std::cout << "리스트 초기화\n\n";

	int iSelect = 0;
	int iTmp = 0;

	while (iSelect != 4)
	{
		std::cout << "현재 데이터 개수: " << LCount(&NewList) << "\n";
		std::cout << "메뉴 선택(1. 데이터 입력 / 2. 데이터 출력 / 3. 데이터 삭제 / 4.종료)\n입력: ";
		std::cin >> iSelect;

		switch (iSelect)
		{
		default:
			std::cout << "올바른 번호 입력 요망\n";
			break;
		case 1:
			std::cout << "숫자 입력: ";
			std::cin >> iTmp;
			DataTmp = new Value;
			SetData(DataTmp, iTmp);
			LInsert(&NewList, DataTmp);
			break;
		case 2:
			if (LCount(&NewList) == 0)
				std::cout << "등록된 데이터 없음\n";
			else
			{
				LFirst(&NewList, &DataTmp);
				std::cout << ReturnData(DataTmp) << "\n";

				for (int i = 1; i < LCount(&NewList); i++)
				{
					LNext(&NewList, &DataTmp);
					std::cout << ReturnData(DataTmp) << "\n";
				}
			}
			break;
		case 3:
			if (LCount(&NewList) == 0)
				std::cout << "등록된 데이터 없음\n";
			else
			{
				std::cout << "삭제하고 싶은 값 입력(먼저 입력된 데이터 삭제, 중복 삭제X): ";
				std::cin >> iTmp;

				LFirst(&NewList, &DataTmp);
				if (ReturnData(DataTmp) == iTmp)
				{
					DataTmp = LRemove(&NewList);
				}
				else
				{
					for (int i = 1; i < LCount(&NewList); i++)
					{
						LNext(&NewList, &DataTmp);
						if (ReturnData(DataTmp) == iTmp)
						{
							DataTmp = LRemove(&NewList);
						}
					}
				}
			}
			break;
		case 4:
			break;
		}
		std::cout << "\n";
	}
	return 0;
}