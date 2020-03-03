#include "Login.h"



Login::Login()
{

}

void Login::Register(int iUserCount)
{
	system("cls");

	if (iUserCount == 0)
	{
		HeadUser = new User;
		HeadUser->Next = NULL;
		IdInput(HeadUser);
		PwInput(HeadUser);
		InfoInput(HeadUser);
	}
	else
	{
		NewUser = new User;
		IdInput(NewUser);
		PwInput(NewUser);
		InfoInput(NewUser);
		NewUser->Next = NULL;

		User *tmp = HeadUser;
		
		while (1)
		{
			if (tmp->Next == NULL)
			{
				tmp->Next = NewUser;
				break;
			}
			tmp = tmp->Next;
		}

	}
}

int Login::CharRangeCheck(char Start, char End, char Check)
{
	if (Check >= Start && Check <= End)
		return TRUE;
	return FALSE;
}

void Login::IdInput(User *Usertmp)
{
	string Id;
	bool b1, b2, b3;

	do
	{
		system("cls");
		b1 = true;
		b2 = true;
		b3 = true;	//�ʱ�ȭ

		cout << "���̵� �Է�([3���ڡ�] AND [�ѱ�X]): ";
		cin >> Id;
		for (int i = 0; i < Id.length(); i++)
		{	//�ѱ��� �ֳ� �˻�
			if (CharRangeCheck('a', 'z', Id[i]) == FALSE &&
				CharRangeCheck('A', 'Z', Id[i]) == FALSE &&
				CharRangeCheck('0', '9', Id[i]) == FALSE)
			{
				cout << "��й�ȣ�� �����ڿ� ���� �̿ܰ� ���� �� �˴ϴ�.\n";
				b1 = false;
				break;
			}
		}

		if (Id.length() <= 3)
		{
			cout << "���̵� ������ �����Դϴ�.\n";	//���̰� 3���� �����ΰ� �˻�
			b2 = false;
		}
		
		User *tmp;
		tmp = HeadUser;

		while (1)
		{
			if (tmp->Id == Id)
			{
				cout << "����� �� ���� ���̵��Դϴ�.\n";
				b3 = false;
				break;
			}
			if (tmp->Next == NULL)
				break;

			tmp = tmp->Next;
		}

		system("pause");
	} while (b1 != true || b2 != true || b3 != true);
	Usertmp->Id = Id;
}

void Login::PwInput(User* Usertmp)	//��й�ȣ �Է�
{
	string Pw, Pw_check;
	bool b1, b2, b3, b4;

	do
	{
		system("cls");
		b1 = true;
		b2 = true;
		b3 = false;
		b4 = true;	//�ʱ�ȭ
		cout << "��й�ȣ �Է�([8���ڡ�] AND [����] AND [��������]): ";
		cin >> Pw;
		cout << "��й�ȣ Ȯ��: ";
		cin >> Pw_check;

		for (int i = 0; i < Pw.length(); i++)
		{	//�ѱ��� �ֳ� �˻�
			if (CharRangeCheck('a', 'z', Pw[i]) == FALSE &&
				CharRangeCheck('A', 'Z', Pw[i]) == FALSE &&
				CharRangeCheck('0', '9', Pw[i]) == FALSE)
			{
				cout << "��й�ȣ�� �����ڿ� ���� �̿ܰ� ���� �� �˴ϴ�.\n";
				b1 = false;
				break;
			}
		}

		for (int i = 0; i < Pw.length(); i++)
		{
			if (CharRangeCheck('0', '9', Pw[i]) == TRUE)
				b3 = true;
		}

		if (Pw.length() < 8)
		{
			cout << "��й�ȣ�� �������� �̸��Դϴ�.\n";	//���̰� 3���� �����ΰ� �˻�
			b2 = false;
		}

		if (b3 == false)
			cout << "���ڰ� ���ԵǾ� ���� �ʽ��ϴ�.\n";

		if (Pw != Pw_check)
		{
			b4 = false;
			cout << "��й�ȣ�� ��ġ���� �ʽ��ϴ�.\n";
		}

		system("pause");
	} while (b1 != true || b2 != true || b3 != true || b4 != true);
	Usertmp->Password = Pw;
}

void Login::InfoInput(User *Usertmp)
{
	system("cls");
	cout << "�г��� �Է�: ";
	cin >> Usertmp->Name;
	cout << "���� �Է�: ";
	cin >> Usertmp->Age;
	cout << "�޴��� ��ȣ �Է�: ";
	cin >> Usertmp->PhoneNumber;
	cout << "ȸ������ ����! ���ϸ��� 1,000�� ����\n";
	Usertmp->Mileage = 1000;
	system("pause>null");
}

void Login::DataCheck()
{
	string Id_insert;
	string Pw_insert;
	system("cls");
	cout << "���̵� �Է�: ";
	cin >> Id_insert;
	cout << "��й�ȣ �Է�: ";
	cin >> Pw_insert;

	User *tmp = HeadUser;

	while(1)
	{
		if (tmp->Id == Id_insert)
		{
			if (tmp->Password == Pw_insert)
			{
				UserMenu(tmp);
				return;
			}
			else
				break;
		}
		if (tmp->Next == NULL)
			break;
		tmp = tmp->Next;
	}

	cout << "���̵� �Ǵ� ��й�ȣ�� �ٽ� Ȯ���Ͻʽÿ�...\n";
	system("pause>null");
}

void Login::ShowInfo(User *Usertmp)
{
	system("cls");
	cout << "============ȸ�� ����============\n";
	cout << "���̵�: " << Usertmp->Id << "   �г���: " << Usertmp->Name << "\n";
	cout << "����: " << Usertmp->Age << "     �޴��� ��ȣ: " << Usertmp->PhoneNumber << "\n";
	cout << "���ϸ���: " << Usertmp->Mileage << "\n";
	system("pause");
}

void Login::ModifyInfo(User *Usertmp)
{
	int Select = 0;
	string Name_change;
	int Age_change;
	string CP_change;

	while (1)
	{
		ShowInfo(Usertmp);
		cout << "=======================\n";
		cout << "1. �г��� ����\n";
		cout << "2. ���� ����\n";
		cout << "3. �޴��� ��ȣ ����\n";
		cout << "4. ���ư���\n";
		cout << "�Է�: ";
		cin >> Select;

		switch (Select)
		{
		case 1:
			cout << "\n���� �г���: " << Usertmp->Name << "\n";
			cout << "������ �г��� �Է�: ";
			cin >> Name_change;
			cout << Usertmp->Name << " �� " << Name_change;
			Usertmp->Name = Name_change;
			system("pause");
			break;
		case 2:
			cout << "\n���� ����: " << Usertmp->Age << "\n";
			cout << "������ ���� �Է�: ";
			cin >> Age_change;
			cout << Usertmp->Age << " �� " << Age_change;
			Usertmp->Age = Age_change;
			system("pause");
			break;
		case 3:
			cout << "\n���� �޴��� ��ȣ: " << Usertmp->PhoneNumber << "\n";
			cout << "������ �޴��� ��ȣ �Է�: ";
			cin >> CP_change;
			cout << Usertmp->PhoneNumber << " �� " << CP_change;
			Usertmp->PhoneNumber = CP_change;
			system("pause");
			break;
		case 4:
			return;
		default:
			cout << "���õ� �޴� ��ȣ���� �Է��Ͽ� �ֽʽÿ�...\n";
			system("pause");
			break;
		}
	}
}

void Login::UserMenu(User *Usertmp)
{
	int iSelect;

	while (1)
	{
		system("cls");
		cout << "===== ȯ���մϴ� =====\n";
		cout << "1. ��ǻ�� ����\n";
		cout << "2. ���\n";
		cout << "3. ȸ�� ����\n";
		cout << "4. ȸ�� ���� ����\n";
		cout << "5. off\n";
		cout << "�Է� >> ";
		cin >> iSelect;

		switch (iSelect)
		{
		case 1:
			PrintSpec();
			break;
		case 2:
			Functions();
			break;
		case 3:
			ShowInfo(Usertmp);
			break;
		case 4:
			ModifyInfo(Usertmp);
			break;
		case 5:
			for (int i = 5; i > 0; i--)
			{
				cout << "off " << i << "����\n";
				Sleep(1000);
			}
			return;
		default:
			cout << "������ �޴� ��ȣ�� �Է�\n";
			system("pause>null");
			break;
		}
	}
}

void Login::DeleteUserData(User *Usertmp)
{
	if (Usertmp->Next != NULL)
	{
		DeleteUserData(Usertmp->Next);
		Usertmp->Age = NULL;
		Usertmp->Mileage = NULL;
		delete Usertmp;
	}
	else
	{
		Usertmp->Age = NULL;
		Usertmp->Mileage = NULL;
		delete Usertmp;
	}
}

Login::~Login()
{
	DeleteUserData(HeadUser);
}
