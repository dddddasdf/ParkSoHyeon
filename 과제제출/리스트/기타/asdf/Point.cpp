#include "Point.h"

void SetPointCoordinate(Point *TmpPoint, int X, int Y)
{
	TmpPoint->XPosition = X;
	TmpPoint->YPosition = Y;

	std::cout << "좌표 저장 성공\n";
}

void ShowCoordinate(Point *TmpPoint)
{
	std::cout << "[" << TmpPoint->XPosition << ", " << TmpPoint->YPosition << "]\n";
}

int ComparePoints(Point *PointFirst, Point *PointSecond)
{
	if ((PointFirst->XPosition == PointSecond->XPosition) && (PointFirst->YPosition == PointSecond->YPosition))
		return 3;
	else if (PointFirst->XPosition == PointSecond->XPosition)
		return 1;
	else if (PointFirst->YPosition == PointSecond->YPosition)
		return 2;
	else
		return 0;
}