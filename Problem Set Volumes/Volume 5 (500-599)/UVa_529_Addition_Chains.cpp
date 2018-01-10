
/*
	UVa 529 - Addition Chains

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_529_Addition_Chains.cpp

	from International Collegiate Programming Contest 1997 University of Ulm Local Contest Problem A
		(http://www.informatik.uni-ulm.de/acm/Locals/1997/)
*/

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

/*
For a set of intergers s = {a(0), a(1), ..., a(k)}, a(0) = 1, a(0) < a(1) < ... < a(k):
If (n - a(k)) is in the set, done.
Else
	For j = k, k - 1, k - 2, ..., 0:
		if (a(j) + a(k) < n)
			Append a(j) + a(k) to the set, and recurse the process.

Initially, s = {a(0)}.
If n > 1, addition_chains();
*/

const int n_max = 10000;
int chains[n_max] = {1};
int min_chains[n_max];

bool addition_chains(int n, int candidate, int nr_chains, int& min_nr_chains, int chains[])
{
	int i;
	if (binary_search(chains, chains + nr_chains, n - candidate)) {
#ifdef DEBUG
		for (i = 0; i < nr_chains; i++)
			cout << chains[i] << ' ';
		cout << n << endl;
#endif
		if (nr_chains < min_nr_chains) {
			min_nr_chains = nr_chains;
			memcpy(min_chains, chains, sizeof(int) * min_nr_chains);
		}
		return true;
	}
	else if (nr_chains + 1 < min_nr_chains) {
#ifdef DEBUG
		for (i = 0; i < nr_chains; i++)
			cout << chains[i] << ' ';
		cout << endl;
#endif
		i = nr_chains - 1;
		for ( ; i >= 0; i--) {
			int s = candidate + chains[i];
			if (s < n) {
				chains[nr_chains] = s;
				if (!addition_chains(n, s, nr_chains + 1, min_nr_chains, chains))
					break;
			}
		}
		return (i == nr_chains - 1) ? false : true;
	}
	else {
#ifdef DEBUG
		for (i = 0; i < nr_chains; i++)
			cout << chains[i] << ' ';
		cout << endl;
#endif
		return false;
	}
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		int min_nr_chains = n;
		if (n > 1) {
			addition_chains(n, chains[0], 1, min_nr_chains, chains);
			for (int i = 0; i < min_nr_chains; i++)
				cout << min_chains[i] << ' ';
		}
		cout << n << endl;
	}
	return 0;
}

