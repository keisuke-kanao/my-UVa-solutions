
/*
	UVa 242 - Stamps and Envelope Size

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_242_Stamps_and_Envelope_Size.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int S_max = 10, max_denomination = 100, N_max = 10;

int nr_denominations[N_max + 1], denominations[N_max + 1][S_max + 1], max_coverages[N_max + 1];
bool values[S_max + 1][S_max + 1][max_denomination * S_max + 1];
	// values[i][j][k] is true if value of k can be represented using j stamps out of i stamps

int get_max_coverage(int nr_stamps, int nr_denoms, const int* denoms)
{
	memset(values, 0, sizeof(values));
	int max_v = 0;
	for (int j = 1, k = denoms[1]; j <= nr_stamps; j++, k += denoms[1])
		values[1][j][k] = true, max_v = k;
#ifdef DEBUG
	for (int j = 1; j <= nr_stamps; j++)
		for (int k = 1; k <= max_v; k++)
		if (values[1][j][k])
			printf("[%d][%d][%d] ", 1, j, k);
	putchar('\n');
#endif
	for (int i = 2; i <= nr_denoms; i++) {
		int max_k = max_v;
		max_v = 0;
		for (int j = 1; j <= nr_stamps; j++)
			for (int k = 1; k <= max_k; k++)
				if (values[i - 1][j][k]) {
					values[i][j][k] = true;
					for (int l = 1, s = denoms[i]; l <= nr_stamps - j; l++, s += denoms[i])
						values[i][j + l][k + s] = true, max_v = max(max_v, k + s);
				}
		for (int j = 1, k = denoms[i]; j <= nr_stamps; j++, k += denoms[i])
			values[i][j][k] = true, max_v = max(max_v, k);
#ifdef DEBUG
		for (int j = 1; j <= nr_stamps; j++)
			for (int k = 1; k <= max_v; k++)
			if (values[i][j][k])
				printf("[%d][%d][%d] ", i, j, k);
		putchar('\n');
#endif
	}
	int k;
	for (k = 0; k < max_v; k++) {
		int j;
		for (j = 1; j <= nr_stamps; j++)
			if (values[nr_denoms][j][k + 1])
				break;
		if (j > nr_stamps)
			break;
	}
	return k;
}

int compare_denomination(int di, int dj)
{
	if (nr_denominations[di] != nr_denominations[dj])
		return (nr_denominations[di] < nr_denominations[dj]) ? di : dj;
	for (int i = nr_denominations[di]; i; i--)
		if (denominations[di][i] != denominations[dj][i])
			return (denominations[di][i] < denominations[dj][i]) ? di : dj;
	return di;
}

int main()
{
	while (true) {
		int S;
		scanf("%d", &S);
		if (!S)
			break;
		int N;
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			scanf("%d", &nr_denominations[i]);
			for (int j = 1; j <= nr_denominations[i]; j++)
				scanf("%d", &denominations[i][j]);
			max_coverages[i] = get_max_coverage(S, nr_denominations[i], &denominations[i][0]);
#ifdef DEBUG
			printf("max coverage: %d\n", max_coverages[i]);
#endif
		}
		int max_coverage = max_coverages[1], max_coverage_denomination = 1;
		for (int i = 2; i <= N; i++) {
			if (max_coverage < max_coverages[i])
				max_coverage = max_coverages[i], max_coverage_denomination = i;
			else if (max_coverage == max_coverages[i])
				max_coverage_denomination = compare_denomination(max_coverage_denomination, i);
		}
		printf("max coverage = %3d :", max_coverage);
		for (int i = 1; i <= nr_denominations[max_coverage_denomination]; i++)
			printf("%3d", denominations[max_coverage_denomination][i]);
		putchar('\n');
	}
	return 0;
}

