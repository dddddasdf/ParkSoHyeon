#include "Employee.h"

void SetStaffInformation(Staff *StaffTmp, char *NameTmp, int NumberTmp)
{
	strcpy(StaffTmp->sName, NameTmp);
	StaffTmp->iNumber = NumberTmp;
}

void ShowStaffInformation(Staff *StaffTmp, char *NameTmp, int NumberTmp)
{
	printf("�����: %s \t ��� ��ȣ: %d", NameTmp, NumberTmp);
}