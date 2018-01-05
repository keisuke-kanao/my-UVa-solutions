
/*
	UVa 10858 - Unique Factorization

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10858_Unique_Factorization.cpp
*/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void unique_factorization(int m, int n, vector<int>& factors, vector< vector<int> >& factorizations)
{
	for (int i = m, j = static_cast<int>(sqrt(static_cast<double>(n))); i <= j; i++)
		if (!(n % i)) {
			factors.push_back(i);
			unique_factorization(i, n / i, factors, factorizations);
			factors.pop_back();
		}
	if (!factors.empty()) {
		factorizations.push_back(factors);
		factorizations.back().push_back(n);
	}
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		vector<int> factors;
		vector< vector<int> > factorizations;
		unique_factorization(2, n, factors, factorizations);
		cout << factorizations.size() << endl;
		for (size_t i = 0; i < factorizations.size(); i++) {
			const vector<int>& f = factorizations[i];
			for (size_t j = 0; j < f.size(); j++) {
				if (j)
					cout << ' ';
				cout << f[j];
			}
			cout << endl;
		}
	}
	return 0;
}

