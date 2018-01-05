
/*
	UVa 11349 - Symmetric Matrix

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11349_Symmetric_Matrix.cpp
*/

#include <iostream>
using namespace std;

const int n_max = 100;
long long m[n_max][n_max];

int main()
{
	int t;
	cin >> t;
	for (int tn = 1; tn <= t; tn++) {
		char c, d;
		int n;
		cin >> c >> d >> n;
		bool symmetric = true;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++) {
				cin >> m[i][j];
				if (m[i][j] < 0)
					symmetric = false;
			}
		if (symmetric) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (m[i][j] != m[n - 1 - i][n - 1 - j]) {
						symmetric = false;
						break;
					}
		}
		cout << "Test #" << tn << ((symmetric) ? ": Symmetric.\n" : ": Non-symmetric.\n");
	}
	return 0;
}

