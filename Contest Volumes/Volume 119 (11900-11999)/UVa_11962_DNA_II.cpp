
/*
	UVa 11962 - DNA II

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11962_DNA_II.cpp
*/

#include <cstdio>

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		const int nr_dna_chars = 4, nr_chars_max = 30;
		const char dna_chars[] = {'A', 'C', 'G', 'T'};
		char s[nr_chars_max + 1];
		scanf("%s", s);
		int i, length = 0;
		long long index = 0;
		for (const char* p = s; *p; p++) {
			for (i = 0; /* i < nr_dna_chars */; i++)
				if (*p == dna_chars[i])
					break;
			if (length++)
				index *= 4;
			index += i;
		}
		printf("Case %d: (%d:%lld)\n", t, length, index);
	}
	return 0;
}

