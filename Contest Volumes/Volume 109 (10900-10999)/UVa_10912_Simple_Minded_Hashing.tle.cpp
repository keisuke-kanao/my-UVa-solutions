
/*
	UVa 10912 - Simple Minded Hashing

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10912_Simple_Minded_Hashing.cpp
*/

#include <cstdio>

const int L_max = 26;
int sums[L_max + 1]; // sums[i] is the sum of integers up to i
#ifdef DEBUG
char letters[L_max + 2]; // letters[i] is the i-th letter of string
#endif

int get_sum(int i, int j)
{
	return sums[i + j] - sums[i - 1];
}

void simple_minded_hashing(int i, int l, int s, int L, int S, int& nr)
{
	if (l == L) {
		if (S - s <= L_max) {
#ifdef DEBUG
			letters[l] = 'a' + S - s - 1;
			letters[l + 1] = '\0';
			puts(&letters[1]);
#endif
			nr++;
		}
	}
	else {
		for (int j = i + 1; j + L - l <= L_max && get_sum(j, L - l) <= S - s; j++) {
#ifdef DEBUG
			letters[l] = 'a' + j - 1;
#endif
			simple_minded_hashing(j, l + 1, s + j, L, S, nr);
		}
	}
}

int main()
{
	for (int i = 1; i <= L_max; i++)
		sums[i] = sums[i - 1] + i;
	for (int c = 1; ; c++) {
		int L, S;
		scanf("%d %d", &L, &S);
		if (!L && !S)
			break;
		int nr = 0;
		if (L > 0 && L <= L_max && S > 0 && S <= sums[L_max])
			simple_minded_hashing(0, 1, 0, L, S, nr);
		printf("Case %d: %d\n", c, nr);
	}
	return 0;
}

