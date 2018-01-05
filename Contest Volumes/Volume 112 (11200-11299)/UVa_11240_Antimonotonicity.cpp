
/*
	UVa 11240 - Antimonotonicity

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11240_Antimonotonicity.cpp
*/

#include <cstdio>

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		bool less = true;
		int i, p, longest = 0;
		if (n--) {
			scanf("%d", &p);
			longest = 1;
		}
		while (n--) {
			scanf("%d", &i);
			if (longest & 1) { // i should be less than p
				if (i < p)
					longest++;
			}
			else { // i should be greater than p
				if (i > p)
					longest++;
			}
			p = i;
		}
		printf("%d\n", longest);
	}
	return 0;
}

