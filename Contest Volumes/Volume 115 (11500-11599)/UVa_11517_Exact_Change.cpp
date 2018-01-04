
/*
	UVa 11517 - Exact Change

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11517_Exact_Change.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int n_max = 100, price_max = 10000 * 2;
int bcs[n_max + 1]; // bills and coins
int min_nr_bcs[2][price_max + 1];
  // min_nr_bcs[k % 2][i] is the minimum number of coins to pay the amount of i using the first k bills and coins

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int p, n, p_max = 0;
		cin >> p >> n;
		for (int i = 1; i <= n; i++) {
			cin >> bcs[i];
			p_max += bcs[i];
		}
		p_max = min(p_max, price_max);
		for (int k = 0; k < 2; k++)
			for (int i = 1; i <= p_max; i++)
				min_nr_bcs[k][i] = n + 1;
		min_nr_bcs[1][bcs[1]] = 1;
		for (int k = 2; k <= n; k++) {
			int cm = (k % 2), pm = (k - 1) % 2;
			for (int i = 1; i <= p_max; i++)
				min_nr_bcs[cm][i] = (i < bcs[k]) ?
					min_nr_bcs[pm][i] : min(min_nr_bcs[pm][i], min_nr_bcs[pm][i - bcs[k]] + 1);
		}
		for (int m = n % 2, i = p;  ; i++)
			if (min_nr_bcs[m][i] < n + 1) {
				cout << i << ' ' << min_nr_bcs[m][i] << endl;
				break;
			}
	}
	return 0;
}

