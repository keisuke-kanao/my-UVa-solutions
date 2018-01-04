
/*
	UVa 11462 - Age Sort

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11462_Age_Sort.cpp
*/

#include <cstdio>
#include <cstring>

int main()
{
	const int ages_max = 100;
	int nr_people[ages_max + 1]; // nr_people[i] is the number of people of age i
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		memset(nr_people, 0, sizeof(nr_people));
		for (int i = 0; i < n; i++) {
			int j;
			scanf("%d", &j);
			nr_people[j]++;
		}
		bool printed = false;
		for (int i = 1; i <= ages_max; i++) {
			for (int j = 0; j < nr_people[i]; j++) {
				if (printed)
					printf(" %d", i);
				else {
					printed = true;
					printf("%d", i);
				}
			}
		}
		putchar('\n');
	}
	return 0;
}

