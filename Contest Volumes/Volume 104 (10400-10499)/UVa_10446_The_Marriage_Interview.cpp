
/*
	UVa 10446 - The Marriage Interview :-)

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10446_The_Marriage_Interview.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int n_max = 60, b_max = 60;
unsigned long long trib_calls[n_max + 1][b_max + 1];

int main()
{
	int n, b;
	for (b = 1; b <= b_max; b++)
		trib_calls[0][b] = trib_calls[1][b] = 1;
	for (n = 2; n <= n_max; n++)
		for (b = 1; b <= b_max; b++) {
			trib_calls[n][b] = 1;
			for (int i = 1; i <= min(n, b); i++)
				trib_calls[n][b] += trib_calls[n - i][b];
			if (b > n)
				trib_calls[n][b] += b - n;
		}
	for (int cn = 1; ; cn++) {
		cin >> n >> b;
		if (n > n_max)
			break;
		cout << "Case " << cn << ": " << ((n < 0 || b < 1) ? 1 : trib_calls[n][b]) << endl;
	}
	return 0;
}

