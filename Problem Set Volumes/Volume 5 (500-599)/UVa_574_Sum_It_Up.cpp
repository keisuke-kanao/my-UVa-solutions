
/*
	UVa 574 - Sum It Up

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_574_Sum_It_Up.cpp

	from ACM Mid Central Regionals 1997
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_MidCen/1997/index.html)
*/

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

void sum_it_up(int t, int n, int i, const vector< pair<int, int> >& numbers, const vector<int>& sums,
	vector<int>& added, int& nr_cases)
{
	if (!t) {
		bool printed = false;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < added[i]; j++) {
				if (printed)
					cout << '+';
				else
					printed = true;
				cout << numbers[i].first;
			}
		cout << endl;
		nr_cases++;
	}
	else {
		if (i == n || t > sums[i])
			return;
		else {
			for (int j = numbers[i].second; j >= 0; j--) {
				int s = numbers[i].first * j;
				if (t - s >= 0) {
					added[i] = j;
					sum_it_up(t - s, n, i + 1, numbers, sums, added, nr_cases);
				}
			}
		}
	}
}

int main()
{
	while (true) {
		int t, n;
		cin >> t >> n;
		if (!n)
			break;
		vector< pair<int, int> > numbers;
		pair<int, int> i(make_pair(0, 1));
		cin >> i.first;
		for (int j = 1; j < n; j++) {
			int k;
			cin >> k;
			if (i.first == k)
				i.second++;
			else {
				numbers.push_back(i);
				i = make_pair(k, 1);
			}
		}
		numbers.push_back(i);
		n = numbers.size();
		vector<int> sums(n); // sums[i] is the sum of numbers between numbers[i] and numbers[n - 1]
		for (int i = n - 1, s = 0; i >= 0; i--) {
			s += numbers[i].first * numbers[i].second;
			sums[i] = s;
		}
		vector<int> added(n, 0); // added[i] is the number of occurrences that numbers[i] is added
		cout << "Sums of " << t << ":\n";
		int nr_cases = 0;
		sum_it_up(t, n, 0, numbers, sums, added, nr_cases);
		if (!nr_cases)
			cout << "NONE\n";
	}
	return 0;
}

