
/*
	UVa 902 - Password Search

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_902_Password_Search.cpp

	An accepted solution.
*/

#include <iostream>
#include <string>
#include <map>
using namespace std;

int main()
{
	int n;
	while (cin >> n) {
		string s;
		cin >> s;
		map<string, int> substrings; // key is a substring, value is its number of occurrences
		for (int i = 0, j = s.length() - n; i <= j; i++)
			substrings[s.substr(i, n)]++;
		int max_occurrences = 0;
		map<string, int>::const_iterator max_i;
		for (map<string, int>::const_iterator i = substrings.begin(), e = substrings.end(); i != e; i++)
			if (i->second > max_occurrences) {
				max_i = i;
				max_occurrences = i->second;
			}
		cout << max_i->first << endl;
	}
	return 0;
}

