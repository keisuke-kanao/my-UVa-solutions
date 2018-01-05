
/*
	UVa 10520 - Determine it

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10520_Determine_it.cpp
*/

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int n_max = 20;

long long a[n_max + 1][n_max + 1];

long long aij(int n, int i, int j)
{
	long long result = a[i][j];
	if (result != -1)
		return result;
	if (i < j) {
		for (int k = i; k < j; k++)
			result = max(result, aij(n, i, k) + aij(n, k + 1, j));
	}
	else {
		long long r0 = 0, r1 = 0;
		if (i < n)
			for (int k = i + 1; k <= n; k++) 
				r0 = max(r0, aij(n, k, 1) + aij(n, k, j));
		if (j > 0)
			for (int k = 1; k < j; k++)
				r1 = max(r1, aij(n, i, k) + aij(n, n, k));
		result = r0 + r1;
	}
	return a[i][j] = result;
}

int main()
{
	int n, an1;
	while (cin >> n >> an1) {
		memset(a, -1, sizeof(a));
		a[n][1] = an1;
		cout << aij(n, 1, n) << endl;
	}
	return 0;
}

