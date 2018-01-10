
/*
	UVa 729 - The Hamming Distance Problem

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_729_The_Hamming_Distance_Problem.cpp
*/

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int n_max = 16;

int main()
{
	char s[n_max + 1];
	int d;
	cin >> d;
	while (d--) {
		int n, h;
		cin >> n >> h;
		memset(s, '0', n - h);
		memset(s + (n - h), '1', h);
		s[n] = '\0';
		do
			cout << s << endl;
		while (next_permutation(s, s + n));
		if (d)
			cout << endl;
	}
	return 0;
}

