
/*
	UVa 10324 - Zeros and Ones

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10324_Zeros_and_Ones.cpp
*/

#include <algorithm>
#include <iterator>
#include <cstdio>
using namespace std;

const int length_max = 1000000;
int positions[length_max];
char zero_ones[length_max];

int main()
{
	int case_nr = 1;
	char c;
	while ((c = getchar()) != EOF && c != '\n') {
		int i = 0, j, n = 0;
		positions[n] = i; zero_ones[n] = c;
		i++; n++;
		while ((c = getchar()) != '\n') {
			if (c != zero_ones[n - 1]) {
				positions[n] = i; zero_ones[n] = c;
				n++;
			}
			i++;
		}
		printf("Case %d:\n", case_nr);
		int nr_queries;
		scanf("%d", &nr_queries);
		for (int q = 0; q < nr_queries; q++) {
			scanf("%d %d", &i, &j);
			if (i > j)
				swap(i, j);
			int pi = distance(positions, lower_bound(positions, positions + n, i));
			if (pi == n || pi < n && positions[pi] > i)
				pi--;
			int pj = distance(positions, lower_bound(positions, positions + n, j));
			if (pj == n || pj < n && positions[pj] > j)
				pj--;
			printf("%s\n", ((pi == pj) ? "Yes" : "No"));
		}
		getchar();
		case_nr++;
	}
	return 0;
}

