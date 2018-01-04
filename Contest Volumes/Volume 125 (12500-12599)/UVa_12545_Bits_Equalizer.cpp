
/*
	UVa 12545 - Bits Equalizer

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12545_Bits_Equalizer.cpp
*/

#include <cstdio>
#include <cstring>

int main()
{
	const int nr_bits_max = 100;
	int C;
	scanf("%d", &C);
	for (int c = 1; c <= C; c++) {
		char S[nr_bits_max + 1], T[nr_bits_max + 1];
		scanf("%s", S);
		scanf("%s", T);
		int nr_bits = strlen(S);
		int S_0s = 0, S_1s = 0, T_0s = 0, T_1s = 0;
		for (int i = 0; i < nr_bits; i++) {
			if (S[i] == '0')
				S_0s++;
			else if (S[i] == '1')
				S_1s++;
			if (T[i] == '0')
				T_0s++;
			else
				T_1s++;
		}
		int nr_moves = 0;
		if (S_0s + S_1s < nr_bits) {
			for (int i = 0; i < nr_bits; i++)
				if (S[i] == '?') {
					if (T[i] == '0') {
						if (S_0s < T_0s) {
							S_0s++;
							S[i] = '0';
						}
						else {
							S_1s++;
							S[i] = '1';
						}
					}
					else {
						if (S_1s < T_1s) {
							S_1s++;
							S[i] = '1';
						}
						else {
							S_0s++;
							S[i] = '0';
						}
					}
					nr_moves++;
				}
		}
#ifdef DEBUG
		printf("%s %d\n", S, nr_moves);
#endif
		if (S_1s > T_1s)
			nr_moves = -1;
		else {
			if (S_1s < T_1s) {
				for (int i = 0; i < nr_bits; i++)
					if (S[i] == '0' && T[i] == '1' && S_1s < T_1s) {
						S[i] = '1';
						S_1s++;
						nr_moves++;
					}
			}
#ifdef DEBUG
			printf("%s %d\n", S, nr_moves);
#endif
			int nr = 0;
			for (int i = 0; i < nr_bits; i++)
				if (S[i] != T[i])
					nr++;
			nr_moves += nr / 2;
		}
		printf("Case %d: %d\n", c, nr_moves);
	}
	return 0;
}

