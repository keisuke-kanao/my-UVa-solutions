
/*
	UVa 10905 - Children's Game

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10905_Childrens_Game.cpp

	For the implementation, see UVa 10905 - Algorithmist (http://www.algorithmist.com/index.php/UVa_10905).
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool compare_number(const string& i, const string& j)
{
	string ij = i + j, ji = j + i;
	if (ij < ji)
		return true;
	else if (ij == ji)
		return i < j;
	else
		return false;
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		vector<string> numbers(n);
		for (int i = 0; i < n; i++)
			cin >> numbers[i];
		sort(numbers.begin(), numbers.end(), compare_number);
		for (int i = n - 1; i >= 0; i--)
			cout << numbers[i];
		cout << endl;
	}
	return 0;
}

