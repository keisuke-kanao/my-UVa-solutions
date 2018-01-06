
/*
	UVa 10019 - Funny Encryption Method

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10019_Funny_Encryption_Method.cpp
*/

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main()
{
	int N;
	cin >> N;
	while (N--) {
		string M;
		cin >> M;
		long decimal = strtol(M.c_str(), NULL, 10);
		int b1 = 0;
		for ( ; decimal; decimal >>= 1)
			if (decimal & 1)
				b1++;
		long hexadecimal = strtol(M.c_str(), NULL, 16);
		int b2 = 0;
		for ( ; hexadecimal; hexadecimal >>= 1)
			if (hexadecimal & 1)
				b2++;
		cout << b1 << ' ' << b2 << endl;
	}
	return 0;
}

