
/*
	UVa 10361 - Automatic Poetry

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10361_Automatic_Poetry.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void remove_bracket_chars(const char* p, char* q,
	const char*& qs2, const char*& qs3, const char*& qs4, const char*& qs5)
{
	qs2 = qs3 = qs4 = qs5 = NULL;
	for ( ; *p; p++) {
		if (*p == '<') {
			if (qs2)
				qs4 = q;
			else
				qs2 = q;
		}
		else if (*p == '>') {
			if (qs3)
				qs5 = q;
			else
				qs3 = q;
		}
		else
			*q++ = *p;
	}
	*q = '\0';
}

const char* find_dots(const char* p, int length)
{
	p += length - 1;
	for (int count = 0; length; length--, p--) // find 3 sequential dots from tha tail of the string
		if (*p == '.') {
			if (++count == 3)
				break;
		}
		else
			count = 0;
	return p;
}

int main(int /* argc */, char** /* argv */)
{
	const int nr_chars_max = 255;
	char removed_l1[nr_chars_max + 1];
	string line;
	getline(cin, line);
	istringstream iss(line);
	int n; // number of pairs of lines
	iss >> n;
	while (n--) {
		string l1, l2;
		getline(cin, l1); getline(cin, l2);
		// revmove '<' and '>' from l1
		const char *ps2, *ps3, *ps4, *ps5;
		remove_bracket_chars(l1.c_str(), removed_l1, ps2, ps3, ps4, ps5);
			// ps2, ps3, ps4, ps5 are pointed to s2, s3, s4, s5 respectively, after '<' and '>' have been removed
		// find "..." in l2
		const char* q = l2.c_str();
		const char* qs = find_dots(q, l2.length());
			// qs points to the first '.'
		cout << removed_l1 << endl;
		// print l2 before "..."
		while (q < qs)
			cout << *q++;
		// print s4s3s2s5
		const char* p;
		for (p = ps4; p < ps5; p++)
			cout << *p;
		for (p = ps3; p < ps4; p++)
			cout << *p;
		for (p = ps2; p < ps3; p++)
			cout << *p;
		for (p = ps5; *p; p++)
			cout << *p;
		for (p = qs + 3; *p; p++)
			cout << *p;
		cout << endl;
	}
	return 0;
}

