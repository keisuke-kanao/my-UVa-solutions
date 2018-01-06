
/*
	UVa 10022 - Delta-wave

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10022_Delta-wave.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;

void get_position(int n, int& r, int& c)
{
	r = static_cast<int>(sqrt(static_cast<double>(n)));
	int sr = r * r;
	if (sr < n) {
		c = n - sr;
		r++;
	}
	else {
		c = n - (r - 1) * (r - 1);
	}
}

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		int M, N;
		scanf("%d %d", &M, &N);
		if (M > N)
			swap(M, N);
		int mr, mc, nr, nc;
		get_position(M, mr, mc);
		get_position(N, nr, nc);
#ifdef DEBUG
		printf("M:(%d, %d) N:(%d, %d)\n", mr, mc, nr, nc);
#endif
		int sp = 0;
		for ( ; mr < nr; mr++) {
			if (mc & 1) // mc is odd
				mc++, sp++;
			else if (mc + 2 == nc)
				mc = nc, sp += 2;
			else if (mc + 2 < nc)
				mc += 2, sp += 2;
			else
				sp += 2;
#ifdef DEBUG
		printf("\tM:(%d, %d)\n", mr + 1, mc);
#endif
		}
		sp += abs(nc - mc);
		printf("%d\n", sp);
		if (nr_cases)
			putchar('\n');
	}
	return 0;
}

