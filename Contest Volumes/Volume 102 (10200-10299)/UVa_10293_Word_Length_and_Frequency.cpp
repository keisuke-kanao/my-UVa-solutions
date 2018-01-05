
/*
	UVa 10293 - Word Length and Frequency

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10293_Word_Length_and_Frequency.cpp
*/

#include <iostream>
#include <string>
#include <map>
#include <cctype>
using namespace std;

int main()
{
	bool terminated = false;
	while (true) {
		string s;
		map<int, int> words;
		while (true) {
			if (!getline(cin, s)) {
				terminated = true;
				break;
			}
			else if (s.length())
				break;
		}
		if (terminated)
			break;
		int length = 0;
		while (true) {
			if (s.length() == 1 && s[0] == '#')
				break;
			char pc = -1;
			for (const char *p = s.c_str(); ; p++) {
				char c = *p;
				if (!c || isspace(c) || c == '?' || c == '!' || c == ',' || c == '.') {
					if (length && pc != '-') {
						pair<map<int, int>::iterator, bool> result = words.insert(make_pair(length, 1));
						if (!result.second)
							result.first->second++;
						length = 0;
					}
					if (!c)
						break;
				}
				else if (c != '-' && c != '\'')
					length++;
				pc = c;
			}
			if (!getline(cin, s))
				break;
		}
		for (map<int, int>::const_iterator wi = words.begin(), we = words.end(); wi != we; ++wi)
			cout << wi->first << ' ' << wi->second << endl;
		cout << endl;
	}
	return 0;
}

