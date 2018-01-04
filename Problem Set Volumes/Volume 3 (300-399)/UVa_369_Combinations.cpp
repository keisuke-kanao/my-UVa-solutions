
/*
	UVa 369 - Combinations

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_369_Combinations.cpp
*/

#include <iostream>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

/*
int combination(int n, int k)
{
	return (!k || n == k) ? 1 : combination(n - 1, k - 1) + combination(n - 1, k);
}
*/

const int n_max = 100;
int combinations[n_max + 1][n_max + 1];

int combination(int n, int m)
{
	for (int i = 0; i <= n; i++)
		combinations[i][0] = 1;
	for (int i = 0; i <= n; i++)
		combinations[i][i] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j < i; j++)
			combinations[i][j] = combinations[i - 1][j -1 ] + combinations[i - 1][j];
	return combinations[n][m];
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (true) {
		int m, n;
		cin >> n >> m;
		if (!n && !m)
			break;
#ifdef __ELAPSED_TIME__
		if (start == -1)
			start = clock();
#endif
		cout << n << " things taken " << m << " at a time is " << combination(n, m) << " exactly.\n";
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

