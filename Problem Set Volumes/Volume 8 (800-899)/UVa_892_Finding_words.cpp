
/*
	UVa 892 - Finding words

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_892_Finding_words.cpp
*/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
	string s, w;
	bool hyphened = false;
	while (true) {
		getline(cin, s);
		if (s == "#")
			break;
		for (const char* p = s.c_str(); *p; p++) {
			if (isalpha(*p))
				w += *p;
			else {
				if (*p == '-') {
					if (*(p + 1) == '\0')
						hyphened = true;
				}
				else {
					cout << w;
					w.clear();
					if (hyphened) {
						hyphened = false;
						cout << endl;
					}
					if (isspace(*p))
						cout << *p;
				}
			}
		}
		if (!w.empty() && !hyphened) {
			cout << w;
			w.clear();
		}
		cout << endl;
	}
	return 0;
}

