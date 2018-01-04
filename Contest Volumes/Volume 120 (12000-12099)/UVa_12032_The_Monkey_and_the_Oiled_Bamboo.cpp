
/*
	UVa 12032 - The Monkey and the Oiled Bamboo

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12032_The_Monkey_and_the_Oiled_Bamboo.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 100000;
int rungs[n_max];

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &rungs[i]);
		int k = rungs[0];
		for (int i = 1; i < n; i++)
			k = max(k, rungs[i] - rungs[i - 1]);
		int j = k;
		if (rungs[0] == j)
			j--;
		for (int i = 1; i < n; i++) {
			int d = rungs[i] - rungs[i - 1];
			if (d == j)
				j--;
			else if (d > j) {
				k++; break;
			}
		}
		printf("Case %d: %d\n", t, k);
	}
	return 0;
}

