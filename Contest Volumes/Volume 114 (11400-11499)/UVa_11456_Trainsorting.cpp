
/*
	UVa 11456 - Trainsorting

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11456_Trainsorting.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 2000;
int values[n_max];
int lis[n_max];
	// lis[i] is the longest DECREASING subsequence starting at (n - i - 1), 0 <= i < n
int lds[n_max];
	// lds[i] is the longest INCREASING subsequence starting at (n - i - 1), 0 <= i < n

int LIS(int n)
{
	int length = 1;
	lis[0] = 1;
	for (int i = 1; i < n; i++) {
		lis[i] = 1;
		for (int j = 0; j < i; j++)
			if (values[j] < values[i]) {
				if (lis[i] < 1 + lis[j]) {
					lis[i] = 1 + lis[j];
				}
			}
		if (length < lis[i])
			length = lis[i];
	}
	return length;
}

int LDS(int n)
{
	int length = 1;
	lds[0] = 1;
	for (int i = 1; i < n; i++) {
		lds[i] = 1;
		for (int j = 0; j < i; j++)
			if (values[j] > values[i]) {
				if (lds[i] < 1 + lds[j]) {
					lds[i] = 1 + lds[j];
				}
			}
		if (length < lds[i])
			length = lds[i];
	}
	return length;
}

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &values[n - i - 1]);
		LIS(n);
		LDS(n);
		int longest = 0;
		for (int i = 0; i < n; i++) {
#ifdef DEBUG
			printf("%d: %d %d\n", i, lis[i], lds[i]);
#endif
			longest = max(longest, lis[i] + lds[i] - 1);
		}
		printf("%d\n", longest);
	}
	return 0;
}

