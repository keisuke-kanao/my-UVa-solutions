
/*
	UVa 10626 - Buying Coke

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10626_Buying_Coke.cpp

	This is an accepted solution.
*/

#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

const int C_max =150, n1_max = 500, n5_max = 100, n10_max = 50;
int nr_coins[C_max + 1][n5_max + n10_max + 1][n10_max + 1];

int main()
{
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		int C, n1, n5, n10;
		cin >> C >> n1 >> n5 >> n10;
		int amount = n1 + n5 * 5 + n10 * 10;
		for (int i = 0; i <= C; i++)
			for (int j = 0; j <= n5 + n10; j++)
				for (int k = 0; k <= n10; k++)
					nr_coins[i][j][k] = numeric_limits<int>::max();
		nr_coins[0][n5][n10] = 0;
		for (int i = 1; i <= C; i++)
			for (int j = 0; j <= n5 + n10; j++)
				for (int k = 0; k <= n10; k++)
					if (nr_coins[i - 1][j][k] != numeric_limits<int>::max()) {
						n1 = amount - j * 5 - k * 10;
						if (n1 >= 8)
							nr_coins[i][j][k] = min(nr_coins[i][j][k], nr_coins[i - 1][j][k] + 8);
						if (n1 >= 3 && j >= 1)
							nr_coins[i][j - 1][k] = min(nr_coins[i][j - 1][k], nr_coins[i - 1][j][k] + 4);
						if (j >= 2)
							nr_coins[i][j - 2][k] = min(nr_coins[i][j - 2][k], nr_coins[i - 1][j][k] + 2);
						if (k >= 1)
							nr_coins[i][j][k - 1] = min(nr_coins[i][j][k - 1], nr_coins[i - 1][j][k] + 1);
						if (n1 >= 3 && j < n5 + n10 && k >= 1)
							nr_coins[i][j + 1][k - 1] = min(nr_coins[i][j + 1][k - 1], nr_coins[i - 1][j][k] + 4);
					}
		int min_nr_coins = numeric_limits<int>::max();
		for (int j = 0; j <= n5 + n10; j++)
			for (int k = 0; k <= n10; k++)
				min_nr_coins = min(min_nr_coins, nr_coins[C][j][k]);
		cout << min_nr_coins << endl;
	}
	return 0;
}

