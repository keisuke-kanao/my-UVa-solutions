
/*
	UVa 11321 - Sort! Sort!! and Sort!!!

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11321_Sort_Sort_and_Sort.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int n_max = 10000;
int numbers[n_max];

struct number_comparator {
	int m_;

	number_comparator(int m) : m_(m) {}
	bool operator() (int i, int j) const;
};

bool number_comparator::operator() (int i, int j) const
{
	int r = i % m_, s = j % m_;
	if (r < s)
		return true;
	else if (r > s)
		return false;
	else {
		bool odd_i = i & 1, odd_j = j & 1;
		if (odd_i && odd_j)
			return i > j;
		else if (!odd_i && !odd_j)
			return i < j;
		else
			return (odd_i) ? true : false;
	}
}

int main()
{
	while (true) {
		int n, m;
		cin >> n >> m;
		cout << n << ' ' << m << endl;
		if (!n && !m)
			break;
		for (int i = 0; i < n; i++)
			cin >> numbers[i];
		sort(numbers, numbers + n, number_comparator(m));
		for (int i = 0; i < n; i++)
			cout << numbers[i] << endl;
	}
	return 0;
}

