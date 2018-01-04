
/*
	UVa 11876 - N + NOD (N)

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11876_NOD.cpp
*/

#include <cstdio>
#include <cmath>

const int n_max = 1000010;
const int ni_max = 1000000;

int nr_nis[n_max + 1]; // nr_nis[i] is the number of Ni up to i

/*
	If the number is a^i * b^j * c^k * ..., then it has (i + 1) * (j+1) * (k+1)... divisors.
*/

int number_of_divisors(int n)
{
	if (n < 3)
		return n;
	int nr = 2; // 1 and n
	for (int i = 2, e = static_cast<int>(sqrt(static_cast<double>(n))); i <= e; i++)
		if (!(n % i)) {
			nr++;
			int j = n / i;
			if (j > i)
				nr++;
		}
	return nr;
}
int main()
{
	int i = 1, ni = 1, nr = 1;
	nr_nis[i++] = nr;
	do {
		int nni = ni + number_of_divisors(ni);
		for ( ; i < nni; i++)
			nr_nis[i] = nr;
		nr_nis[i++] = ++nr;
		ni = nni;
#ifdef DEBUG
		printf("%d %d\n", ni, nr);
#endif
	} while (ni <= ni_max);
#ifdef DEBUG
	printf("%d %d %d\n", i, ni, nr); // 1000011 1000010 64726
#endif
	int t;
	scanf("%d", &t);
	for (int cn = 1; cn <= t; cn++) {
		int a, b;
		scanf("%d %d", &a, &b);
		printf("Case %d: %d\n", cn, nr_nis[b] - nr_nis[a - 1]);
	}
	return 0;
}

