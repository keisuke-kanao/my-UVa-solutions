
/*
	UVa 492 - Pig-Latin

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_492_Pig-Latin.cpp
*/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
	string line;
	while (getline(cin, line)) {
		const char* p = line.c_str();
		while (true) {
			for ( ; *p && !isalpha(*p); p++)
				cout << *p;
			if (!*p)
				break;
			const char* q = p;
			for ( ; isalpha(*q); q++)
				;
			char c = tolower(*p);
			if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
				for ( ; p < q; p++)
					cout << *p;
			}
			else {
				c = *p++;
				for ( ; p < q; p++)
					cout << *p;
				cout << c;
			}
			cout << "ay";
			p = q;
			if (*p)
				cout << *p++;
			else
				break;
		}
		cout << endl;
	}
	return 0;
}

