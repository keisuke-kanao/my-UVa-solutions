
/*
	UVa 10440 - Ferry Loading II

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10440_Ferry_Loading_II.cpp

	from 25 January, 2003 - Waterloo local contest, Problem B
		(http://acm.student.cs.uwaterloo.ca/~acm00/030125/data/)
*/

#include <iostream>
using namespace std;

const int m_max = 1440;
int ats[m_max]; // arrival times

int main()
{
	int c;
	cin >> c;
	while (c--) {
		int i, j, n, t, m;
		cin >> n >> t >> m;
		for (int i = 0; i < m; i++)
			cin >> ats[i];
		int tt = 0 /* trip time */, nt = 0 /* number of trips */;
		int mx = m % n;
		if (!mx)
			mx = n;
		for (i = 0; i < mx; ) {
			for (j = 0; j < n && i < mx; i++, j++)
				if (tt < ats[i])
					tt = ats[i];
			tt += (i < m) ? t * 2 : t;
			nt++;
#ifdef DEBUG
			cout << tt << ' ' << nt << ", next m: " << i << endl;
#endif
		}
		for ( ; i < m; ) {
			for (j = 0; j < n && i < m; i++, j++)
				if (tt < ats[i])
					tt = ats[i];
			tt += (i < m) ? t * 2 : t;
			nt++;
#ifdef DEBUG
			cout << tt << ' ' << nt << ", next m: " << i << endl;
#endif
		}
		cout << tt << ' ' << nt << endl;
	}
	return 0;
}

