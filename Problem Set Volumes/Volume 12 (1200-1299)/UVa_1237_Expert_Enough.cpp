
/*
	UVa 1237 - Expert Enough?

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1237_Expert_Enough.cpp

	This is an accepted solution.
*/

#include <cstdio>

const int D_max = 10000, nr_chars_max = 31;
struct price {
	char maker_[nr_chars_max + 1];
	int l_, h_; // lowest price, highest price
} prices[D_max];

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int D;
		scanf("%d", &D);
		for (int i = 0; i < D; i++)
			scanf("%s %d %d", prices[i].maker_, &prices[i].l_, &prices[i].h_);
		int Q;
		scanf("%d", &Q);
		while (Q--) {
			int P;
			scanf("%d", &P);
			int mi = -1;
			for (int i = 0; i < D; i++)
				if (P >= prices[i].l_ && P <= prices[i].h_) {
					if (mi == -1)
						mi = i;
					else {
						mi = -1;
						break;
					}
				}
			if (mi != -1)
				printf("%s\n", prices[mi].maker_);
			else
				puts("UNDETERMINED");
		}
		if (T)
			putchar('\n');
	}
	return 0;
}

