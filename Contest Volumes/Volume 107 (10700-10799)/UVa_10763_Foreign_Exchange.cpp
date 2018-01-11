
/*
	UVa 10763 - Foreign Exchange

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10763_Foreign_Exchange.cpp

	from 2004 ACPC Alberta Collegiate Programming Contest October 2, 2004, 11:00-16:00 Problem E
	(http://ugweb.cs.ualberta.ca/~acpc/2004/)
*/

#include <iostream>
#include <map>
using namespace std;

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		map< pair<int, int>, int > locations;
		for (int i = 0; i < n; i++) {
			pair<int, int> loc;
			cin >> loc.second >> loc.first;
			map< pair<int, int>, int >::iterator j = locations.find(loc);
			if (j != locations.end())
				j->second--;
			else {
				pair<map< pair<int, int>, int>::iterator, bool> result =
					locations.insert(make_pair(make_pair(loc.second, loc.first), 0));
				result.first->second++;
			}
		}
		bool successful = true;
		for (map< pair<int, int>, int >::const_iterator i = locations.begin(), e = locations.end(); i != e; ++i)
			if (i->second) {
				successful = false; break;
			}
		cout << ((successful) ? "YES\n" : "NO\n");
	}
	return 0;
}

