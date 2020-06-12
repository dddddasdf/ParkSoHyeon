#pragma once
#include <iostream>

struct Point
{
	int XPosition;
	int YPosition;
};

void SetPointCoordinate(Point *TmpPoint, int X, int Y);

void ShowCoordinate(Point *TmpPoint);

int ComparePoints(Point *PointFirst, Point *PointSecond);