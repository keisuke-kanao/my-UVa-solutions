
/*
	UVa 11849 - CD

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11849_CD.cpp
*/

#include <cstdio>
#include <cstdlib>

const int n_max = 1000000;
int numbers[n_max];

int compare_number(const void* i, const void* j)
{
	return *reinterpret_cast<const int*>(i) - *reinterpret_cast<const int*>(j);
}

int main()
{
	while (true) {
		int n, m;
		scanf("%d %d", &n, &m);
		if (!n && !m)
			break;
		for (int i = 0; i < n; i++)
			scanf("%d", &numbers[i]);
/*
		qsort(numbers, n, sizeof(int), compare_number);
*/
		int nr = 0;
		for (int i = 0; i < m; i++) {
			int number;
			scanf("%d", &number);
			if (bsearch(&number, numbers, n, sizeof(int), compare_number))
				nr++;
		}
		printf("%d\n", nr);
	}
	return 0;
}


