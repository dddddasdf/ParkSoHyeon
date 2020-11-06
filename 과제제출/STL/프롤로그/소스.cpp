#include <iostream>

//not !

//class Point
//{
//private:
//	int x;
//public:
//	Point(int _x = 0) : x(_x)
//	{
//
//	}
//
//	void Print() const 
//	{
//		std::cout << x << "\n";
//	}
//
//	bool operator ! () const
//	{
//		return !(this->x);
//	}
//};
//
//void main()
//{
//	Point p1(3);
//	p1.Print();
//
//	Point tmp;
//	tmp = !p1;
//
//	p1.Print();
//	tmp.Print();
//
//	std::cout << "\n";
//
//	Point p2(0);
//	p2.Print();
//
//	tmp = !p2;
//
//	p2.Print();
//	tmp.Print();
//}


//conjunction &

class Point
{
private:
	int x;
	int y;
public:
	Point(int _x = 0, int _y = 0) : x(_x), y(_y)
	{

	}

	void Print() const 
	{
		std::cout << x << ", " << y << "\n";
	}

	bool operator & (const Point &Tmp) const
	{
		return ((this->x & Tmp.x) & (this->y & Tmp.y));
	}
};

void main()
{
	Point p1(4, 6);
	Point p2(3, 7);

	Point result;
	result = p1 & p2;

	result.Print();
}