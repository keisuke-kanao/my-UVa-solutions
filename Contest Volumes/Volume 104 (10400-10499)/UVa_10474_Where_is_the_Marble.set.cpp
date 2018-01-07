
/*
	UVa 10474 - Where is the Marble?

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10474_Where_is_the_Marble.set.cpp

	running time on Uva Online Judge = 2.904 sec.
*/

#include <iostream>
#include <set>
using namespace std;

int main()
{
	for (int c = 1; ; c++) {
		int n, q;
		cin >> n >> q;
		if (!n && !q)
			break;
		multiset<int> marbles;
		for (int i = 0; i < n; i++) {
			int number;
			cin >> number;
			marbles.insert(number);
		}
		cout << "CASE# " << c << ":\n";
		for (int i = 0; i < q; i++) {
			int number;
			cin >> number;
			pair<multiset<int>::iterator, multiset<int>::iterator> result = marbles.equal_range(number);
			if (result.first == marbles.end() || *result.first != number)
				cout << number << " not found\n";
			else {
				cout << number << " found at " << distance(marbles.begin(), result.first) + 1 << endl;
			}
		}
	}
	return 0;
}

