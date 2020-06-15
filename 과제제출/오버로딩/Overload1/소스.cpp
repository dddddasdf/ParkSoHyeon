#include <iostream>

class Point
{
private:
	int m_ix;
	int m_iy;
public:
	Point() { GetXY(); }
	Point(int x, int y)
	{
		m_ix = x;
		m_iy = y;
	}
	void GetXY();
	void operator / (Point tmp);
	~Point() { }
};

void Point::GetXY()
{
	std::cout << "x�� �Է�: ";
	std::cin >> m_ix;
	std::cout << "y�� �Է�: ";
	std::cin >> m_iy;
}

void Point::operator / (Point tmp)
{
	std::cout << "ù��° x = " << this->m_ix << "\tù��° y = " << this->m_iy << "\n";
	std::cout << "�ι�° x = " << tmp.m_ix << "\t�ι�° y = " << tmp.m_iy << "\n";
	
	std::cout << "��ü / ��ü��\n";

	if (this->m_ix >= tmp.m_ix)
		std::cout << "x���� ���� ��: " << (this->m_ix / tmp.m_ix);
	else if (this->m_ix < tmp.m_ix)
		std::cout << "x���� ���� ��: " << (tmp.m_ix / this->m_ix);

	std::cout << "\n";

	if (this->m_iy >= tmp.m_iy)
		std::cout << "y���� ���� ��: " << (this->m_iy / tmp.m_iy);
	else if (this->m_iy < tmp.m_iy)
		std::cout << "y���� ���� ��: " << (tmp.m_iy / this->m_iy);

	std::cout << "\n";
}

void main()
{
	Point p1(10, 20), p2(5, 40);
	p1 / p2;
	p1.~Point();
	p2.~Point();

	std::cout << "\n\n";

	Point p3, p4;
	p3 / p4;
}