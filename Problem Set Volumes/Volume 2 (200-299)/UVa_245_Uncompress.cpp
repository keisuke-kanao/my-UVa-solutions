
/*
	UVa 245 - Uncompress

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_245_Uncompress.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>
using namespace std;

int main()
{
	int n = 0; // number of words
	vector<char*> words; // word list
	while (true) {
		string s;
		getline(cin, s);
		if (s[0] == '0')
			break;
		for (const char *p = s.c_str(), *q = s.c_str(); ; ) {
			if (isdigit(*p)) {
				int i = *p - '0';
				for (p++; isdigit(*p); p++) {
					i *= 10;
					i += *p - '0';
				}
				q = p;
				i--;
				char* r = words[n - 1 - i];
				cout << r;
				// move the word to the back of the list
				memmove(&words[n - 1 - i], &words[n - i], sizeof(char*) * i);
				words[n - 1] = r;
			}
			else {
				if (*p)
					cout << *p;
				if (isalpha(*p))
					p++;
				else {
					if (p - q) {
						// add a word at the back of the list
						char* t = new char[p - q + 1];
						memcpy(t, q, p - q);
						*(t + (p - q)) = '\0';
						words.push_back(strdup(t));
						n++;
						q = p;
					}
					if (*p) {
						p++; q++;
					}
					else // end of line
						break;
				}
			}
		}
		cout << endl;
	}
	return 0;
}

