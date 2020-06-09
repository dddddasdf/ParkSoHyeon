#include "Functions.h"

int main()
{
	List NewList;
	Value *DataTmp;
	ListInit(&NewList);
	std::cout << "����Ʈ �ʱ�ȭ\n\n";

	int iSelect = 0;
	int iTmp = 0;

	while (iSelect != 4)
	{
		std::cout << "���� ������ ����: " << LCount(&NewList) << "\n";
		std::cout << "�޴� ����(1. ������ �Է� / 2. ������ ��� / 3. ������ ���� / 4.����)\n�Է�: ";
		std::cin >> iSelect;

		switch (iSelect)
		{
		default:
			std::cout << "�ùٸ� ��ȣ �Է� ���\n";
			break;
		case 1:
			std::cout << "���� �Է�: ";
			std::cin >> iTmp;
			DataTmp = new Value;
			SetData(DataTmp, iTmp);
			LInsert(&NewList, DataTmp);
			break;
		case 2:
			if (LCount(&NewList) == 0)
				std::cout << "��ϵ� ������ ����\n";
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
				std::cout << "��ϵ� ������ ����\n";
			else
			{
				std::cout << "�����ϰ� ���� �� �Է�(���� �Էµ� ������ ����, �ߺ� ����X): ";
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