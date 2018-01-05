
/*
	UVa 10771 - Barbarian tribes

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10771_Barbarian_tribes.cpp

	This is a variation of Josephus problem.
		(http://en.wikipedia.org/wiki/Josephus_problem)
*/

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	while (true) {
		int n, m, k;
		cin >> n >> m >> k;
		if (!k)
			break;
		vector<char> maids(n + m);
		for (int i = 0; i < n; i++)
			maids[i] = 'G';
		for (int i = n; i < n + m; i++)
			maids[i] = 'K';
		n += m;
		char maid;
		for (int i = 0; ; ) {
#ifdef DEBUG
			cout << "n: " << n << " i: " << i << ' ';
			for (int j = 0; j < n; j++)
				cout << maids[j];
			cout << endl;
#endif
			i = (i + k - 1) % n;
			maid = maids[i];
			maids.erase(maids.begin() + i);
			if (!--n)
				break;
			i = (i + k - 1) % n;
			maids[i] = (maids[i] == maid) ? 'G' : 'K';
			i = (i + 1) % n;
		}
		cout << ((maid == 'K') ? "Keka\n" : "Gared\n");
	}
	return 0;
}

