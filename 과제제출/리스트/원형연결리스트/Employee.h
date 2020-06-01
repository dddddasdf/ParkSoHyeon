#ifndef __EMPLOYEE_H__
#define __EMPLOYEE_H__
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct INFORMATION
{
	char sName[50];
	int iNumber;
}Staff;

void SetStaffInformation(Staff *StaffTmp, char *NameTmp, int NumberTmp);

void ShowStaffInformation(Staff *StaffTmp, char *NameTmp, int NumberTmp);

#endif