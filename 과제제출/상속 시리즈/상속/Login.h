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
	User *HeadUser, *NewUser;	//전자는 헤드 유저 데이터
public:
	Login();
	void Register(int iUserCount);
	int CharRangeCheck(char Start, char End, char Check);	//문자 확인용
	void IdInput(User *Usertmp);	//아이디 체크
	void PwInput(User *Usertmp);	//비밀번호 체크
	void InfoInput(User *Usertmp);	//기타 정보 체크 여기까지 가입 관련 함수
	void DataCheck();	//로그인 하는 함수
	void ShowInfo(User *Usertmp);	//정보 보여줌
	void ModifyInfo(User *Usertmp);	//정보 수정
	void UserMenu(User *Usertmp);
	void DeleteUserData(User *Usertmp);
	~Login();
};