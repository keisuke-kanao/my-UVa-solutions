
/*
	UVa 10306 - e-Coins

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10306_e_Coins.cpp
*/

#include <iostream>
#include <limits>
#include <algorithm>
using namespace std;

const int m_max = 40, s_max = 300;
const int not_possible = s_max * s_max + 1;
int nr_coins[m_max + 1][s_max + 1][s_max + 1];
	// nr_coins[i][j][k] is the minimum number of coins up to i (i >= 1) in which
	// the sum of conventinal values is j and the sum of InfoTechnological values is k

struct e_coin {
	int value_;
	int it_value_;
} e_coins[m_max + 1];

int main()
{
	int n;
	cin >> n;
	while (n--) {
		int m, s;
		cin >> m >> s;
		for (int i = 1; i <= m; i++)
			cin >> e_coins[i].value_ >> e_coins[i].it_value_;
		for (int j = 0; j <= s; j++)
			for (int k = 0; k <= s; k++)
				nr_coins[0][j][k] = not_possible;
		nr_coins[0][0][0] = 0;
		for (int i = 1; i <= m; i++) {
			const e_coin& ec = e_coins[i];
			for (int j = 0; j <= s; j++)
				for (int k = 0; k <= s; k++) {
					if (j >= ec.value_ && k >= ec.it_value_)
						nr_coins[i][j][k] = min(nr_coins[i - 1][j][k], nr_coins[i][j - ec.value_][k - ec.it_value_] + 1);
					else
						nr_coins[i][j][k] = nr_coins[i - 1][j][k];
				}
		}
		int ss = s * s, min_nr = not_possible;
		for (int j = 0; j <= s; j++)
			for (int k = 0; k <= s; k++)
				if (j * j + k * k == ss)
					min_nr = min(min_nr, nr_coins[m][j][k]);
		if (min_nr == not_possible)
			cout << "not possible\n";
		else
			cout << min_nr << endl;
	}
	return 0;
}

