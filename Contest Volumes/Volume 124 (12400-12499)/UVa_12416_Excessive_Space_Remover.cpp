
/*
	UVa 12416 - Excessive Space Remover

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12416_Excessive_Space_Remover.cpp
*/

#include <cstdio>
#include <cmath>
#include <cctype>

const int nr_chars_max = 1048576;
char line[nr_chars_max + 1];

int main()
{
	const double log2 = log10(2.0);
	while (gets(line)) {
		int nr_spaces = 0, max_nr_spaces = 0;
		for (const char* p = line; *p; p++) {
			if (isspace(*p))
				nr_spaces++;
			else {
				if (nr_spaces > max_nr_spaces)
					max_nr_spaces = nr_spaces;
				nr_spaces = 0;
			}
		}
		if (max_nr_spaces > 1)
			printf("%.0lf\n", ceil(log10(static_cast<double>(max_nr_spaces)) / log2));
		else
			puts("0");
	}
	return 0;
}

