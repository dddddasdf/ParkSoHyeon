#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

typedef struct Test
{
	string sItemName;
	int iItemNumber;

	Test(string Name = "", int itemnumber = 0)
		: sItemName(Name), iItemNumber(itemnumber)
	{
	}
}TestStruct;

bool CompareNumber(TestStruct Tmp1, TestStruct Tmp2)
{
	if (Tmp1.iItemNumber <= Tmp2.iItemNumber)
		return Tmp1.iItemNumber;
	else
		return Tmp2.iItemNumber;
}

int main()
{
	//vector<double> v;

	//v.push_back(10.5);
	//v.push_back(22.7);
	//v.push_back(14.85);
	//v.push_back(5.53798);
	//v.push_back(30);
	//v.push_back(0.55);

	//vector<double>::iterator iter;

	//sort(v.begin(), v.end(), less<double>());
	//for (iter = v.begin(); iter != v.end(); ++iter)
	//	cout << *iter << " ";
	//cout << "\n";

	//sort(v.begin(), v.end(), greater<double>());
	//for (iter = v.begin(); iter != v.end(); ++iter)
	//	cout << *iter << " ";
	//cout << "\n";

	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);

	vector<TestStruct> ItemList;

	ItemList.push_back(TestStruct("목검", 5));
	ItemList.push_back(Test("청동검", 2));
	ItemList.push_back(Test("체력포션", 100));
	ItemList.push_back(Test("해골물", 102));
	ItemList.push_back(Test("마나포션", 101));

	sort(ItemList.begin(), ItemList.end(), CompareNumber);	//크래시 남

	for (int i = 0; i < ItemList.size(); i++)
		cout << "아이템명: " << ItemList[i].sItemName << "\n";


	


	/*vector<string> v;

	v.push_back("I");
	v.push_back("want ");
	v.push_back("go ");
	v.push_back("home");
	v.push_back("orz");
	v.push_back("test");

	vector<string>::iterator iter;

	iter = find(v.begin(), v.end(), "home");
	cout << *iter << "\n";

	iter = find(v.begin(), v.end(), "house");

	if (iter == v.end())
		cout << "그런 단어 없음\n";*/

	/*for (iter = v.begin(); iter != v.end(); ++iter)
		cout << *iter << "\n";*/



	return 0;
}