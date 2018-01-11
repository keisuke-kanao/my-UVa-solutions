
/*
	UVa 10404 - Bachet's Game

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10404_Bachets_Game.cpp
*/

#include <iostream>
#include <vector>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

/*
	Let w[i] be true if Stan wins for the game of i stones, then:
		w[i] = !w[i - numbers[0]] || !w[i - numbers[1]] || ... !w[i - numbers[m - 1]], for 1 <= i <= n
		w[0] = false;
*/

int main()
{
#ifdef __ELAPSED_TIME__
	time_t start = clock();
#endif
	int n;
	while (cin >> n) {
		int m;
		cin >> m;
		vector<int> numbers(m);
		for (int i = 0; i < m; i++)
			cin >> numbers[i];
		vector<bool> w(n + 1, false);
		for (int i = 1; i <= n; i++) {
			for (int j = 0; j < m; j++)
				if (i >= numbers[j] && !w[i - numbers[j]]) {
					w[i] = true; break;
				}
		}
		cout << ((w[n]) ? "Stan" : "Ollie") << " wins\n";
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

