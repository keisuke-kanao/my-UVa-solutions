
/*
	UVa 10176 - Ocean Deep ! - Make it shallow !!

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10176_Ocean_Deep.cpp
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
	const int divisor = 131071;
	const int nr_digits_max = 10000;
	char number[nr_digits_max + 2];
	string s;
	while (getline(cin, s)) {
		int length = 0;
		while (true) {
			for (int i = 0, l = s.length(); i < l; i++)
				if (s[i] == '0' || s[i] == '1' || s[i] == '#')
					number[length++] = s[i];
			if (number[length - 1] == '#')
				break;
			getline(cin, s);
		}
#ifdef DEBUG
		number[length] = '\0';
		cout << length << ' ' << number << endl;
#endif
		int residue = 0;
		for (int i = 0; i < length - 1; i++) {
			residue <<= 1;
			residue += number[i] - '0';
			residue %= divisor;
		}
		cout << ((residue) ? "NO\n" : "YES\n");
	}
	return 0;
}

