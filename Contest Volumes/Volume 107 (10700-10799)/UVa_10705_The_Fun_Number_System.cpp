
/*
	UVa 10705 - The Fun Number System

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10705_The_Fun_Number_System.cpp
*/

#include <limits>
#include <cstdio>
using namespace std;

int main()
{
	const int k_max = 64;
	int t;
	scanf("%d", &t);
	while (t--) {
		int k;
		scanf("%d", &k);
		char s[k_max + 1], repr[k_max + 1];
		scanf("%s", s);
		long long N;
		scanf("%lld", &N);
		for (int i = k - 1; i >= 0; i--, N >>= 1) {
			if (N & 1) {
				repr[i] = '1';
				if (s[i] == 'p')
					N--;
				else
					N++;
			}
			else
				repr[i] = '0';
		}
		if (N)
			puts("Impossible");
		else {
			repr[k] = '\0';
			printf("%s\n", repr);
		}
	}
	return 0;
}

