
/*
	UVa 10721 - Bar Codes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10721_Bar_Codes.cpp
*/

#include <iostream>
using namespace std;

const int nkm_max = 50;
long long bc[nkm_max + 1][nkm_max + 1][nkm_max + 1];

int main()
{
	int n, k, m;
	for (n = 1; n <= nkm_max; n++)
		for (m = 1; m <= nkm_max; m++)
			if (n <= m)
				bc[n][1][m] = 1;
	for (n = 1; n <= nkm_max; n++)
		bc[n][n][1] = 1;
	for (k = 2; k <= nkm_max; k++)
		for (n = 2; n <= nkm_max; n++)
			for (m = 2; m <= nkm_max; m++)
				if (n >= k && n <= k * m) {
					if (n - k + 1 >= m)
						for (int i = 1; i <= m; i++)
							bc[n][k][m] += bc[n - i][k - 1][m];
					else
						bc[n][k][m] = bc[n][k][m - 1];
				}

	while (cin >> n >> k >> m)
		cout << bc[n][k][m] << endl;
	return 0;
}

