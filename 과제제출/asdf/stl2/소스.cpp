#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

template<typename T>
struct Plus : public binary_function<T, T, T> //어댑터 적용이 가능하도록.
{
	T operator( )(const T& left, const T& right) const
	{
		return left + right;
	}
};
void main()
{
	Plus<int> sPlus;
	cout << sPlus(10, 20) << endl;
	cout << sPlus.operator()(10, 20) << endl;

	cout << Plus<int>()(10, 20) << endl;
	cout << Plus<int>().operator()(10, 20) << endl;
}