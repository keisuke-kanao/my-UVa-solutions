
/*
	UVa 12700 - Banglawash

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12700_Banglawash.cpp
*/

#include <cstdio>

int main()
{
	const int N_max = 10;
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N;
		scanf("%d", &N);
		char s[N_max + 1];
		scanf("%s", s);
		int bangladesh = 0, www = 0, tie = 0, abandoned = 0;
		for (int i = 0; i < N; i++) {
			switch (s[i]) {
			case 'B':
				bangladesh++; break;
			case 'W':
				www++; break;
			case 'T':
				tie++; break;
			case 'A':
				abandoned++; break;
			}
		}
		printf("Case %d: ", t);
		if (abandoned == N)
			puts("ABANDONED");
		else {
			N -= abandoned;
			if (bangladesh == N)
				puts("BANGLAWASH");
			else if (www == N)
				puts("WHITEWASH");
			else if (bangladesh > www)
				printf("BANGLADESH %d - %d\n", bangladesh, www);
			else if (www > bangladesh)
				printf("WWW %d - %d\n", www, bangladesh);
			else
				printf("DRAW %d %d\n", bangladesh, tie);
		}
	}
	return 0;
}

