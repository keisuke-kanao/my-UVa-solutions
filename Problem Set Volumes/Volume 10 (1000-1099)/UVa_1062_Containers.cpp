
/*
	UVa 1062 - Containers

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1062_Containers.cpp
*/

#include <cstdio>

int main()
{
	const int nr_chars_max = 1000;
	char s[nr_chars_max + 1], stacks[nr_chars_max];
	for (int case_nr = 1; ; case_nr++) {
		scanf("%s", s);
		if (s[0] == 'e')
			break;
		int nr_stacks = 0;
		for (const char* p = s; *p; p++) {
			int i;
			for (i = 0; i < nr_stacks; i++)
				if (*p <= stacks[i]) {
					stacks[i] = *p;
					break;
				}
			if (i == nr_stacks)
				stacks[nr_stacks++] = *p;
		}
		printf("Case %d: %d\n", case_nr, nr_stacks);
	}
	return 0;
}

