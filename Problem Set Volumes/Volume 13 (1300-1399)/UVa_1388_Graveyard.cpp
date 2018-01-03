
/*
	UVa 1388 - Graveyard

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1388_Graveyard.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const double perimeter = 10000.0;
const int n_max = 1000, m_max = 1000;
double cds[n_max], nds[n_max + m_max]; // current / new distances

int main()
{
	int n, m;
	while (scanf("%d %d", &n, &m) != EOF) {
		m += n;
		for (int i = 0; i < n; i++)
			cds[i] = (perimeter * (i + 1)) / n;
		for (int i = 0; i < m; i++)
			nds[i] = (perimeter * (i + 1)) / m;
		double d = 0.0;
		for (int i = 0, j = 0; i < n - 1; ) {
			if (cds[i] < nds[j]) {
				d += min(cds[i] - nds[j - 1], nds[j] - cds[i]);
				i++;
			}
			else if (cds[i] > nds[j])
				j++;
			else {
				i++, j++;
			}
		}
		printf("%.4lf\n", d);
	}
	return 0;
}

