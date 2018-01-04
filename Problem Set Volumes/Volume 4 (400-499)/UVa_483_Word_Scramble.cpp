
/*
	UVa 483 - Word Scramble

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_483_Word_Scramble.cpp
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

int main()
{
	string s;
	while (getline(cin, s)) {
		int i = 0, e = s.length();
		string::iterator si = s.begin();
		while (i < e) {
			int j = i;
			while (j < e && !isspace(s[j]))
				j++;
			reverse(si + i, si + j);
			i = ++j;
		}
		cout << s << endl;
	}
	return 0;
}

