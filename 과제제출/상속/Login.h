#pragma once
#include "Computer.h"

struct User
{
	string Id;
	string Password;
	string Name;
	int Age;
	string PhoneNumber;
	int Mileage;
	User *Next;
};

class Login: public Computer
{
private:
	User *HeadUser, *NewUser;	//���ڴ� ��� ���� ������
public:
	Login();
	void Register(int iUserCount);
	int CharRangeCheck(char Start, char End, char Check);	//���� Ȯ�ο�
	void IdInput(User *Usertmp);	//���̵� üũ
	void PwInput(User *Usertmp);	//��й�ȣ üũ
	void InfoInput(User *Usertmp);	//��Ÿ ���� üũ ������� ���� ���� �Լ�
	void DataCheck();	//�α��� �ϴ� �Լ�
	void ShowInfo(User *Usertmp);	//���� ������
	void ModifyInfo(User *Usertmp);	//���� ����
	void UserMenu(User *Usertmp);
	void DeleteUserData(User *Usertmp);
	~Login();
};