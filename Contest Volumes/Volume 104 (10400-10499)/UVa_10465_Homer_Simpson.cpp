
/*
	UVa 10465 - Homer Simpson

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10465_Homer_Simpson.cpp

	An accepted solution.
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

pair<int, int> how_many_burgers_to_eat(int m, int n, int t)
{
	vector< pair<bool, int> > burgers(t + 1, make_pair(false, 0));
		// burgers[i].first is true if time of i is realized
		// burgers[i].second is the number of bergers Homer can eat in time of i
	burgers[0].first = true;
	int i;
	for (i = min(m, n); i <= t; i++) {
		if (i >= m && i >= n) {
			if (burgers[i - m].first && burgers[i - n].first)
				burgers[i] = make_pair(true, max(burgers[i - m].second + 1, burgers[i - n].second + 1));
			else if (burgers[i - m].first)
				burgers[i] = make_pair(true, burgers[i - m].second + 1);
			else if (burgers[i - n].first)
				burgers[i] = make_pair(true, burgers[i - n].second + 1);
		}
		else if (i >= m) {
			if (burgers[i - m].first)
				burgers[i] = make_pair(true, burgers[i - m].second + 1);
		}
		else {
			if (burgers[i - n].first)
				burgers[i] = make_pair(true, burgers[i - n].second + 1);
		}
	}
	for (i = t; i; i--)
		if (burgers[i].first)
			break;
	return make_pair(burgers[i].second, t - i);
}

int main()
{
#ifdef __ELAPSED_TIME__
	time_t start = clock();
#endif
	int m, n, t;
	while (cin >> m >> n >> t) {
		pair<int, int> result = how_many_burgers_to_eat(m, n, t);
		cout << result.first;
		if (result.second)
			cout << ' ' << result.second;
		cout << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

