
/*
	UVa 10036 - Divisibility

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10036_Divisibility.cpp
*/

#include <iostream>
#include <cstdlib>
using namespace std;

const int n_max = 10000, k_max = 100;
int integers[n_max];
bool remainders[2][k_max]; // remainders[][i] is true if (sum of the integers) % k == i

bool calculate_remainders(int n, int k)
{
	for (int i = 0; i < k; i++)
		remainders[0][i] = false;
	remainders[0][integers[0] % k] = true;
	for (int i = 1; i < n; i++) {
		int pri = (i - 1) % 2, cri = i % 2;
		for (int j = 0; j < k; j++) {
			int r = integers[i] % k;
			remainders[cri][j] = remainders[pri][(j - r + k) % k] || remainders[pri][(j + r) % k];
		}
	}
	return remainders[(n - 1) % 2][0];
}

int main()
{
	int m;
	cin >> m;
	while (m--) {
		int n, k;
		cin >> n >> k;
		for (int i = 0; i < n; i++) {
			int j;
			cin >> j;
			integers[i] = abs(j);
		}
		cout << ((calculate_remainders(n, k)) ? "Divisible\n" : "Not divisible\n");
	}
	return 0;
}

