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
		b3 = true;	//초기화

		cout << "아이디 입력([3글자↑] AND [한글X]): ";
		cin >> Id;
		for (int i = 0; i < Id.length(); i++)
		{	//한글이 있나 검사
			if (CharRangeCheck('a', 'z', Id[i]) == FALSE &&
				CharRangeCheck('A', 'Z', Id[i]) == FALSE &&
				CharRangeCheck('0', '9', Id[i]) == FALSE)
			{
				cout << "비밀번호에 영문자와 숫자 이외가 들어가선 안 됩니다.\n";
				b1 = false;
				break;
			}
		}

		if (Id.length() <= 3)
		{
			cout << "아이디가 세글자 이하입니다.\n";	//길이가 3글자 이하인가 검사
			b2 = false;
		}
		
		User *tmp;
		tmp = HeadUser;

		while (1)
		{
			if (tmp->Id == Id)
			{
				cout << "사용할 수 없는 아이디입니다.\n";
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

void Login::PwInput(User* Usertmp)	//비밀번호 입력
{
	string Pw, Pw_check;
	bool b1, b2, b3, b4;

	do
	{
		system("cls");
		b1 = true;
		b2 = true;
		b3 = false;
		b4 = true;	//초기화
		cout << "비밀번호 입력([8글자↑] AND [영문] AND [숫자포함]): ";
		cin >> Pw;
		cout << "비밀번호 확인: ";
		cin >> Pw_check;

		for (int i = 0; i < Pw.length(); i++)
		{	//한글이 있나 검사
			if (CharRangeCheck('a', 'z', Pw[i]) == FALSE &&
				CharRangeCheck('A', 'Z', Pw[i]) == FALSE &&
				CharRangeCheck('0', '9', Pw[i]) == FALSE)
			{
				cout << "비밀번호에 영문자와 숫자 이외가 들어가선 안 됩니다.\n";
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
			cout << "비밀번호가 여덟글자 미만입니다.\n";	//길이가 3글자 이하인가 검사
			b2 = false;
		}

		if (b3 == false)
			cout << "숫자가 포함되어 있지 않습니다.\n";

		if (Pw != Pw_check)
		{
			b4 = false;
			cout << "비밀번호가 일치하지 않습니다.\n";
		}

		system("pause");
	} while (b1 != true || b2 != true || b3 != true || b4 != true);
	Usertmp->Password = Pw;
}

void Login::InfoInput(User *Usertmp)
{
	system("cls");
	cout << "닉네임 입력: ";
	cin >> Usertmp->Name;
	cout << "나이 입력: ";
	cin >> Usertmp->Age;
	cout << "휴대폰 번호 입력: ";
	cin >> Usertmp->PhoneNumber;
	cout << "회원가입 성공! 마일리지 1,000원 적립\n";
	Usertmp->Mileage = 1000;
	system("pause>null");
}

void Login::DataCheck()
{
	string Id_insert;
	string Pw_insert;
	system("cls");
	cout << "아이디 입력: ";
	cin >> Id_insert;
	cout << "비밀번호 입력: ";
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

	cout << "아이디 또는 비밀번호를 다시 확인하십시오...\n";
	system("pause>null");
}

void Login::ShowInfo(User *Usertmp)
{
	system("cls");
	cout << "============회원 정보============\n";
	cout << "아이디: " << Usertmp->Id << "   닉네임: " << Usertmp->Name << "\n";
	cout << "나이: " << Usertmp->Age << "     휴대폰 번호: " << Usertmp->PhoneNumber << "\n";
	cout << "마일리지: " << Usertmp->Mileage << "\n";
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
		cout << "1. 닉네임 변경\n";
		cout << "2. 나이 변경\n";
		cout << "3. 휴대폰 번호 변경\n";
		cout << "4. 돌아가기\n";
		cout << "입력: ";
		cin >> Select;

		switch (Select)
		{
		case 1:
			cout << "\n현재 닉네임: " << Usertmp->Name << "\n";
			cout << "변경할 닉네임 입력: ";
			cin >> Name_change;
			cout << Usertmp->Name << " → " << Name_change;
			Usertmp->Name = Name_change;
			system("pause");
			break;
		case 2:
			cout << "\n현재 나이: " << Usertmp->Age << "\n";
			cout << "변경할 나이 입력: ";
			cin >> Age_change;
			cout << Usertmp->Age << " → " << Age_change;
			Usertmp->Age = Age_change;
			system("pause");
			break;
		case 3:
			cout << "\n현재 휴대폰 번호: " << Usertmp->PhoneNumber << "\n";
			cout << "변경할 휴대폰 번호 입력: ";
			cin >> CP_change;
			cout << Usertmp->PhoneNumber << " → " << CP_change;
			Usertmp->PhoneNumber = CP_change;
			system("pause");
			break;
		case 4:
			return;
		default:
			cout << "제시된 메뉴 번호만을 입력하여 주십시오...\n";
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
		cout << "===== 환영합니다 =====\n";
		cout << "1. 컴퓨터 상태\n";
		cout << "2. 기능\n";
		cout << "3. 회원 정보\n";
		cout << "4. 회원 정보 변경\n";
		cout << "5. off\n";
		cout << "입력 >> ";
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
				cout << "off " << i << "초전\n";
				Sleep(1000);
			}
			return;
		default:
			cout << "지정된 메뉴 번호만 입력\n";
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
