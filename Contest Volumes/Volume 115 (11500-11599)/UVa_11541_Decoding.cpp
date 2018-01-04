
/*
	UVa 11541 - Decoding

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11541_Decoding.cpp
*/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
	int t;
	cin >> t;
	for (int c = 1; c <= t; c++) {
		string s;
		cin >> s;
		cout << "Case " << c << ": ";
		for (const char* p = s.c_str(); *p; ) {
			char c = *p++;
			int length = 0;
			do {
				length *= 10;
				length += *p++ - '0';
			} while (isdigit(*p));
			while (length--)
				cout << c;
		}
		cout << endl;
	}
	return 0;
}

