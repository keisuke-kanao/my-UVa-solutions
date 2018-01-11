
/*
	UVa 674 - Coin Change

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_674_Coin_Change.cpp
*/

/*
	Let C(n, d(k)) be the number of ways to make change of n units with highest denomination of d(k), then:
		C(n) = Σ C(n, d(i)) (i = 1 to k)
	The recurrence relations is:
		C(n, d(k)) = Σ {Σ C(n - i * d(k), d(j)) (j = 1 to k - 1)} (i = 1 to n / d(k)) (for n ≧ d(k), d(k) > 1).
	And the base cases are:
		C(n, d(k)) = 0 (for n ＜ d(k)) and
		C(n, d(k)) = 1 (for n ≧ d(k), d(k) == 1).
*/

#include <iostream>
#include <cstring>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int nr_denominations = 5;
const int denominations[nr_denominations] = {1, 5, 10, 25, 50}; // a set of denominations
const int cents_max = 7489;
int changes[cents_max + 1][nr_denominations];
	// changes[i][j] is the number of ways to make change of i units with highest denomination of denominations[j]

void generate_changes()
{
	memset(changes, 0, sizeof(changes));
	for (int n = 0; n < cents_max + 1; n++)
		changes[n][0] = 1;
	for (int n = 1; n < cents_max + 1; n++)
		for (int k = 1; k < nr_denominations; k++) {
			int c = 0;
			for (int i = 1; i <= n / denominations[k]; i++)
				for (int j = 0; j < k; j++)
					c += changes[n - i * denominations[k]][j];
			changes[n][k] = c;
		}
}

int get_number_of_changes(int n)
{
	int c = 0;
	for (int i = 0; i < nr_denominations; i++)
		c += changes[n][i];
	return c;
}

int main()
{
#ifdef __ELAPSED_TIME__
	time_t start = clock();
#endif
	generate_changes();
	int n;
	while (cin >> n)
		cout << get_number_of_changes(n) << endl;
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

