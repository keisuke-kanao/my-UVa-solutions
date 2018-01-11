
/*
	UVa 10487 - Closest Sums

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10487_Closest_Sums.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
using namespace std;

const int nr_max = 1000;

int closest_sum(int n, const vector<int>& numbers, int s)
{
	int pcs, pd = -1;
	for (int i = 0, j = n - 1; i < j; ) {
		int cs = numbers[i] + numbers[j];
		if (cs == s)
			return cs;
		int d = abs(s - cs);
		if (cs > s)
			j--;
		else
			i++;
		if (pd == -1 || pd > d) {
			pcs = cs; pd = d;
		}
	}
	return pcs;
}

int main()
{
	vector<int> numbers(nr_max);
	for (int c = 1; ; c++) {
		int n;
		cin >> n;
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			cin >> numbers[i];
		sort(numbers.begin(), numbers.begin() + n);
		cout << "Case " << c << ":\n";
		int m;
		cin >> m;
		for (int i = 0; i < m; i++) {
			int s;
			cin >> s;
			cout << "Closest sum to " << s << " is " << closest_sum(n, numbers, s) << ".\n";
		}
	}
	return 0;
}

