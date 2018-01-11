
/*
	UVa 10340 - All in All

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10340_All_in_All.cpp

	An accepted solution.
*/

#include <iostream>
#include <string>
using namespace std;

bool is_subsequence(const string& s, const string& t) // see if s is a subsequence of t
{
	for (int i = 0, j = 0, k = 0, ie = s.length(), je = t.length(); i < ie && j < je; ) {
		if (s[i] == t[j]) {
			if (++k == ie)
				return true;
			i++; j++;
		}
		else
			j++;
	}
	return false;
}

int main()
{
	string s, t;
	while (cin >> s >> t)
		cout << ((is_subsequence(s, t)) ? "Yes\n" : "No\n");
	return 0;
}

