#include "Employee.h"

void SetStaffInformation(Staff *StaffTmp, char *NameTmp, int NumberTmp)
{
	strcpy(StaffTmp->sName, NameTmp);
	StaffTmp->iNumber = NumberTmp;
}

void ShowStaffInformation(Staff *StaffTmp)
{
	printf("�����: %s \t ��� ��ȣ: %d\n", StaffTmp->sName, StaffTmp->iNumber);
}