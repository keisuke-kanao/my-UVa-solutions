
/*
	UVa 130 - Roman Roulette

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_130_Roman_Roulette.cpp
*/

#include <cstdio>
#include <cstring>

bool roman_roulette(int n, int k, int s)
{
	const int nr_persons_max = 100;
	int persons[nr_persons_max];
	for (int i = 0; i < n; i++)
		persons[i] = i + 1;
	while (n > 1) {
#ifdef DEBUG
		for (int i = 0; i < n; i++)
			printf("%d%c", persons[i], ((i == n - 1) ? ',' : ' '));
		printf(" %d\n", s);
#endif
		int vi = (s + k - 1) % n; // index to the victim
		if (persons[vi] == 1) {
#ifdef DEBUG
			putchar('\n');
#endif
			return false;
		}
		int bi = vi; // index to the person who does the job of burying the victim
		for (int i = k; i; ) {
			bi = (bi + 1) % n;
			if (bi != vi)
				i--;
		}
		persons[vi] = persons[bi];
		memmove(&persons[bi], &persons[bi + 1], sizeof(int) * (n - bi - 1));
		if (bi < vi)
			vi--;
		n--;
		s = (vi + 1) % n;
	}
#ifdef DEBUG
	putchar('\n');
#endif
	return persons[0] == 1;
}

int main()
{
	while (true) {
		int n, k;
		scanf("%d %d", &n, &k);
		if (!n && !k)
			break;
		int s;
		for (s = 0; s < n; s++)
			if (roman_roulette(n, k, s))
				break;
		printf("%d\n", s + 1);
	}
	return 0;
}

