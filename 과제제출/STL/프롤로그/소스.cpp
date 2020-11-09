#include <iostream>

//단항 연산자//////////////////////////////////////////////////////////////////////////////////////////

//logic value not !/////

//class Point
//{
//private:
//	int x;
//	int y;
//public:
//	Point(int _x = 0, int _y = 0) : x(_x), y(_y)
//	{
//
//	}
//
//	void Print() const
//	{
//		std::cout << x << ", " << y << "\n";
//	}
//
//	const Point operator ! () const
//	{
//		return Point(!(this->x), !(this->y));
//	}
//};
//
//void main()
//{
//	Point p1(3, 0);
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
//	Point p2(0, 2);
//	p2.Print();
//
//	tmp = !p2;
//
//	p2.Print();
//	tmp.Print();
//}


//conjunction &/////

//class Point
//{
//private:
//	int x;
//	int y;
//public:
//	Point(int _x = 0, int _y = 0) : x(_x), y(_y)
//	{
//
//	}
//
//	void Print() const 
//	{
//		std::cout << x << ", " << y << "\n";
//	}
//
//	const Point operator & (const Point &Tmp)
//	{
//		return Point((this->x & Tmp.x) , (this->y & Tmp.y));
//	}
//};
//
//void main()
//{
//	Point p1(4, 6);
//	Point p2(3, 7);
//
//	Point result;
//	result = p1 & p2;
//
//	result.Print();
//}

//bit value not ~/////

//class Point
//{
//private:
//	int x;
//	int y;
//public:
//	Point(int _x = 0, int _y = 0) : x(_x), y(_y)
//	{
//
//	}
//
//	void Print() const 
//	{
//		std::cout << x << ", " << y << "\n";
//	}
//
//	const Point operator ~ () const
//	{
//		return Point(~(this->x), ~(this->y));
//	}
//};
//
//void main()
//{
//	Point p1(3, 0);
//	p1.Print();
//
//	Point tmp;
//	tmp = ~p1;
//
//	p1.Print();
//	tmp.Print();
//
//	std::cout << "\n";
//
//	Point p2(0, 2);
//	p2.Print();
//
//	tmp = ~p2;
//
//	p2.Print();
//	tmp.Print();
//}

//+ /////

//class Point
//{
//private:
//	int x;
//	int y;
//public:
//	Point(int _x = 0, int _y = 0) : x(_x), y(_y)
//	{
//
//	}
//
//	void Print() const
//	{
//		std::cout << x << ", " << y << "\n";
//	}
//
//	const Point operator + () const
//	{
//		return Point(+(this->x), +(this->y));
//	}
//};
//
//void main()
//{
//	Point p1(3, -5);
//
//	Point tmp;
//	tmp = +p1;
//
//	p1.Print();
//	tmp.Print();
//}

// - /////

//class Point
//{
//private:
//	int x;
//	int y;
//public:
//	Point(int _x = 0, int _y = 0) : x(_x), y(_y)
//	{
//
//	}
//
//	void Print() const
//	{
//		std::cout << x << ", " << y << "\n";
//	}
//
//	const Point operator - () const
//	{
//		return Point(-(this->x), -(this->y));
//	}
//};
//
//void main()
//{
//	Point p1(3, -5);
//
//	Point tmp;
//	tmp = -p1;
//
//	p1.Print();
//	tmp.Print();
//}


//-- /////

//class Point
//{
//private:
//	int x;
//	int y;
//public:
//	Point(int _x = 0, int _y = 0) : x(_x), y(_y)
//	{
//
//	}
//
//	void Print() const 
//	{
//		std::cout << x << ", " << y << "\n";
//	}
//
//	const Point operator -- ()
//	{
//		--x;
//		--y;
//		return *this;
//	}
//
//	const Point operator -- (int)
//	{
//		x--;
//		y--;
//		return *this;
//	}
//};
//
//void main()
//{
//	Point p1(4, 6);
//	Point p2(3, 7);
//
//	Point result;
//	result = p1--;
//	p1.Print();
//	result.Print();
//
//	result = --p2;
//	p2.Print();
//	result.Print();
//}


//이항연산자//////////////////////////////////////////////////////////////////////////////////////////


//+ /////

//class Point
//{
//private:
//	int x;
//	int y;
//public:
//	Point(int _x = 0, int _y = 0) : x(_x), y(_y)
//	{
//
//	}
//
//	void Print() const 
//	{
//		std::cout << x << ", " << y << "\n";
//	}
//
//	const Point operator + (const Point &Tmp)
//	{
//		return Point((this->x + Tmp.x) , (this->y + Tmp.y));
//	}
//};
//
//void main()
//{
//	Point p1(4, 6);
//	Point p2(3, 7);
//
//	Point result;
//	result = p1 + p2;
//
//	result.Print();
//}

//- /////

//class Point
//{
//private:
//	int x;
//	int y;
//public:
//	Point(int _x = 0, int _y = 0) : x(_x), y(_y)
//	{
//
//	}
//
//	void Print() const 
//	{
//		std::cout << x << ", " << y << "\n";
//	}
//
//	const Point operator - (const Point &Tmp)
//	{
//		return Point((this->x - Tmp.x) , (this->y - Tmp.y));
//	}
//};
//
//void main()
//{
//	Point p1(4, 6);
//	Point p2(3, 7);
//
//	Point result;
//	result = p1 - p2;
//
//	result.Print();
//}

//* /////

//class Point
//{
//private:
//	int x;
//	int y;
//public:
//	Point(int _x = 0, int _y = 0) : x(_x), y(_y)
//	{
//
//	}
//
//	void Print() const 
//	{
//		std::cout << x << ", " << y << "\n";
//	}
//
//	const Point operator * (const Point &Tmp)
//	{
//		return Point((this->x * Tmp.x) , (this->y * Tmp.y));
//	}
//};
//
//void main()
//{
//	Point p1(4, 6);
//	Point p2(3, 7);
//
//	Point result;
//	result = p1 * p2;
//
//	result.Print();
//}

//devide / /////

//class point
//{
//private:
//	double x;
//	double y;
//public:
//	point(double _x = 0, double _y = 0) : x(_x), y(_y)
//	{
//
//	}
//
//	void print() const 
//	{
//		std::cout << x << ", " << y << "\n";
//	}
//
//	const point operator / (const point &tmp)
//	{
//		return point((this->x / tmp.x) , (this->y / tmp.y));
//	}
//};
//
//void main()
//{
//	point p1(4, 6);
//	point p2(3, 7);
//
//	point result;
//	result = p1 / p2;
//
//	result.print();
//}


// < /////

//class point
//{
//private:
//	double x;
//	double y;
//public:
//	point(double _x = 0, double _y = 0) : x(_x), y(_y)
//	{
//
//	}
//
//	void print() const 
//	{
//		std::cout << x << ", " << y << "\n";
//	}
//
//	bool operator < (const point &tmp) const
//	{
//		return ((this->x < tmp.x) && (this->y < tmp.y)) ? true : false;
//	}
//};
//
//void main()
//{
//	point p1(4, 6);
//	point p2(3, 7);
//
//	p1.print();
//	p2.print();
//
//	if (p1 < p2)
//		std::cout << "p1 < p2\n";
//	else
//		std::cout << "안 일치\n\n";
//
//	point p3(1, 5);
//	point p4(8, 9);
//
//	p3.print();
//	p4.print();
//
//	if (p3 < p4)
//		std::cout << "p3 < p4";
//	else
//		std::cout << "안 일치";
//}

// <= /////

class point
{
private:
	double x;
	double y;
public:
	point(double _x = 0, double _y = 0) : x(_x), y(_y)
	{

	}

	void print() const
	{
		std::cout << x << ", " << y << "\n";
	}

	bool operator <= (const point &tmp) const
	{
		return ((this->x <= tmp.x) && (this->y <= tmp.y)) ? true : false;
	}
};

void main()
{
	point p1(4, 6);
	point p2(3, 7);

	p1.print();
	p2.print();

	if (p1 <= p2)
		std::cout << "p1 <= p2\n";
	else
		std::cout << "안 일치\n\n";

	point p3(8, 7);
	point p4(8, 9);

	p3.print();
	p4.print();

	if (p3 <= p4)
		std::cout << "p3 <= p4";
	else
		std::cout << "안 일치";
}