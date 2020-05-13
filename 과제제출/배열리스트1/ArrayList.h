#pragma once
#include <iostream>
#define LIST_SIZE 9

void CreateIntArray();

void InitIntArray(int *Array);

void SearchIntArray(int *Array, int NumberOfData);

void SumIntArray(int *Array, int NumberOfData);

void RemoveIntElement(int *Array, int Condition, int &NumberOfData);

void FreeIntArray(int *Array);