/*
	2.8.3 Hartals
	PC/UVa IDs: 110203/10050, Popularity: B, Success rate: high Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10050_Hartals.cpp
*/

#include <iostream>
#include <set>
using namespace std;

int main(int /* argc */, char** /* argv */)
{
	int cases;
	cin >> cases;
	while (cases--) {
		int days, parties;
		cin >> days >> parties;
		set<int> hartals;
		while (parties--) {
			int hartal;
			cin >> hartal;
			for (int h = hartal; h <= days; h += hartal)
				if (h % 7 && h % 7 != 6) // there are no hartals on either Fridays or Saturdays
					hartals.insert(h);
		}
		cout << hartals.size() << endl;
	}
	return 0;
}

