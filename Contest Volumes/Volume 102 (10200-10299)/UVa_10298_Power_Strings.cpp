
/*
	UVa 10298 - Power Strings

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10298_Power_Strings.cpp
*/

#include <cstdio>
#include <cstring>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif

const int nr_chars_max = 1000000;
char s[nr_chars_max + 1];

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (true) {
		gets(s);
		if (!strcmp(s, "."))
			break;
		int i, j, k, l, length = strlen(s);
		for (k = 1; k < length; k++) {
			if (length % k)
				continue;
			for (i = 0; i < k; i++) {
				char c = s[i];
				for (j = i + k; j < length; j += k)
					if (s[j] != c)
						break;
				if (j < length)
					break;
			}
			if (i == k)
				break;
		}
		printf("%d\n", length / k);
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

