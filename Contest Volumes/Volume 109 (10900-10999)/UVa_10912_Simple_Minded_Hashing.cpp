
/*
	UVa 10912 - Simple Minded Hashing

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10912_Simple_Minded_Hashing.cpp
*/

#include <cstdio>

const int L_max = 26, S_max = 351;
int nsc[L_max + 1][S_max + 1][L_max + 1];
	// nsc[l][s][c] is the number of strings of length l, that maps to s and has a max value of c
int ns[L_max + 1][S_max + 1];
	// ns[l][s] is the number of strings of length l, that maps to s

int main()
{
	for (int s = 1; s <= L_max; s++)
		nsc[1][s][s] = 1;
	for (int l = 2; l <= L_max; l++)
		for (int s = 1; s <= S_max; s++)
			for (int c = 1; c <= L_max; c++)
				for (int i = 1; i < c; i++)
					nsc[l][s][c] += nsc[l - 1][s - c][i];
	for (int l = 1; l <= L_max; l++)
		for (int s = 1; s <= S_max; s++)
			for (int c = 1; c <= L_max; c++)
				ns[l][s] += nsc[l][s][c];

	for (int c = 1; ; c++) {
		int L, S;
		scanf("%d %d", &L, &S);
		if (!L && !S)
			break;
		printf("Case %d: %d\n", c, ((L > 0 && L <= L_max && S > 0 && S <= S_max) ? ns[L][S] : 0));
	}
	return 0;
}

