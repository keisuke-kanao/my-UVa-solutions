
/*
	UVa 12718 - Dromicpalin Substrings

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12718_Dromicpalin_Substrings.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_letters = 26, nr_chars_max = 1000;

bool is_dromicpalin(int length, const int* nr_freqs)
{
	bool odd_freq = (length & 1) ? false : true;
	for (int i = 0; i < nr_letters && length; length -= nr_freqs[i++]) {
		if (nr_freqs[i] & 1) {
			if (odd_freq)
				return false;
			else
				odd_freq = true;
		}
	}
	return true;
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		char s[nr_chars_max + 1];
		scanf("%s", s);
		int length = strlen(s), nr_dromicpalins = 0;
		for (int i = 0; i < length; i++) {
			int nr_freqs[nr_letters] = {};
			for (int j = i; j < length; j++) {
				nr_freqs[s[j] - 'a']++;
				if (is_dromicpalin(j - i + 1, nr_freqs))
					nr_dromicpalins++;
			}
		}
		printf("Case %d: %d\n", t, nr_dromicpalins);
	}
	return 0;
}

