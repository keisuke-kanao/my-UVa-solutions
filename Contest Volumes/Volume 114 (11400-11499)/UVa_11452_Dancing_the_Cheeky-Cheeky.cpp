
/*
	UVa 11452 - Dancing the Cheeky-Cheeky

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11452_Dancing_the_Cheeky-Cheeky.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_steps_max = 2000;
char steps[nr_steps_max + 1];

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		scanf("%s", steps);
		int nr_steps = strlen(steps);
		for (int n = nr_steps / 2, m = (nr_steps + 2) / 3; n >= m; n--) {
			int i = nr_steps - 1, j = nr_steps - 1 - n, k = nr_steps - n;
			for ( ; i >= k; i--, j--)
				if (steps[i] != steps[j])
					break;
			if (i < k) {
				if (n < 8) {
					for (i = 0; i < 8; i++)
						putchar(steps[k + i % n]);
					puts("...");
				}
				else {
					steps[k + 8] = '\0';
					printf("%s...\n", &steps[k]);
				}
				break;
			}
		}
	}
	return 0;
}

