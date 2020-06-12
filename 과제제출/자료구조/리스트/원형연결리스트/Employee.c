#include "Employee.h"

void SetStaffInformation(Staff *StaffTmp, char *NameTmp, int NumberTmp)
{
	strcpy(StaffTmp->sName, NameTmp);
	StaffTmp->iNumber = NumberTmp;
}

void ShowStaffInformation(Staff *StaffTmp, char *NameTmp, int NumberTmp)
{
	printf("사원명: %s \t 사원 번호: %d", NameTmp, NumberTmp);
}