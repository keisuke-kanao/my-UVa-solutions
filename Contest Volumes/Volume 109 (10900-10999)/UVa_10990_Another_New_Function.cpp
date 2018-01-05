
/*
	UVa 10990 - Another New Function

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10990_Another_New_Function.cpp
*/

#include <iostream>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int n_max = 2000000;
int phis[n_max + 1]; // phis[i] is the phi function's value for i
int depthphis[n_max + 1]; // depthphis[i] is the depthphi function's value for i
int sodfs[n_max + 1]; // sodfs[i] = SODF(1, i)

int phi_function(int n)
{
	int result = n;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0)
			result -= result / i;
		while (n % i == 0)
			n /= i; 
	}
	if (n > 1)
		result -= result / n;
	return result;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	for (int i = 1; i <= n_max; i += 2) {
		phis[i] = phi_function(i);
		int d = depthphis[phis[i]] + 1;
		depthphis[i] = d;
		int j = i, k = i * 2;
		if (k <= n_max) {
			phis[k] = phis[i];
			depthphis[k] = d;
			for (j = k, k *= 2, d++; k <= n_max; j = k, k *= 2, d++) {
				phis[k] = 2 * phis[j];
				depthphis[k] = d;
			}
		}
	}
	for (int i = 1, sodf = 0; i <= n_max; i++) {
		sodf += depthphis[i];
		sodfs[i] = sodf;
	}
	int N;
	cin >> N;
	while (N--) {
		int m, n;
		cin >> m >> n;
		int sodf = 0;
		cout << sodfs[n] - sodfs[m - 1] << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

