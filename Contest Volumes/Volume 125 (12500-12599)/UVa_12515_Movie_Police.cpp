
/*
	UVa 12515 - Movie Police

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12515_Movie_Police.cpp
*/

#include <cstdio>
#include <cstring>

const int M_max = 1000, l_max = 127;

struct signature {
	int l_;
	char s_[l_max + 1];
} signatures[M_max];

int main()
{
	int M, Q;
	scanf("%d %d", &M, &Q);
	for (int i = 0; i < M; i++) {
		scanf("%s", signatures[i].s_);
		signatures[i].l_ = strlen(signatures[i].s_);
	}
	while (Q--) {
		char clip[l_max + 1];
		scanf("%s", clip);
		int l = strlen(clip);
		int min_i = 0, min_hd = l + 1;
		for (int i = 0; i < M && min_hd; i++) {
			const signature& s = signatures[i];
			if (s.l_ >= l) {
				int hd = l + 1;
				for (int j = 0; j <= s.l_ - l; j++) {
					int d = 0;
					for (int k = 0; k < l && d < hd && d < min_hd; k++)
						if (s.s_[j + k] != clip[k])
							d++;
					if (d < hd)
						hd = d;
				}
				if (hd < min_hd) {
					min_i = i; min_hd = hd;
				}
			}
		}
		printf("%d\n", min_i + 1);
	}
	return 0;
}

