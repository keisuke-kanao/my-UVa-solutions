
/*
	8.6.3 Queue
	PC/UVa IDs: 110803/10128, Popularity: B, Success rate: high Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10128_Queue.cpp
*/

#include <iostream>
#include <vector>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

/*
	People are arranged in descending order of thier heights.

	The first person to be arranged (who is the highest of all) belongs to both P and R.

	The second person to be arranged belongs to either P if he/she is arranged to the left the first person or 
	R if he/she is arranged to the right of the first person.

	The third person to be arranged belongs to P if he/she is arranged to the left most position.
	He/She belongs to R if he/she is arranged to the rigth most position.
	He/She belongs to neither P nor R if he/she is arranged between the first two persons.

	And so on ...
*/

void arrange_people(int n /* number of people to be arranged */, int arranged /* number of people arranged so far */,
	int p /* number of people who have unblocked vision to their left */,
	int r /* number of people who have unblocked vision to their right */,
	int& arrangements /* number of arrangemnts */, vector< vector< vector<int> > >& cache)
{
	if (arranged == n) {
		if (!p && !r)
			arrangements++;
	}
	else if (!arranged)
		arrange_people(n, arranged + 1, p - 1, r - 1, arrangements, cache);
	else {
		if (p) {
			if (cache[arranged + 1][p - 1][r] == -1) {
				int arr = 0;
				arrange_people(n, arranged + 1, p - 1, r, arr, cache);
				cache[arranged + 1][p - 1][r] = arr;
			}
			arrangements += cache[arranged + 1][p - 1][r];
		}
		for (int i = 0; i < arranged - 1; i++) {
			if (cache[arranged + 1][p][r] == -1) {
				int arr = 0;
				arrange_people(n, arranged + 1, p, r, arr, cache);
				cache[arranged + 1][p][r] = arr;
			}
			arrangements += cache[arranged + 1][p][r];
		}
		if (r) {
			if (cache[arranged + 1][p][r - 1] == -1) {
				int arr = 0;
				arrange_people(n, arranged + 1, p, r - 1, arr, cache);
				cache[arranged + 1][p][r - 1] = arr;
			}
			arrangements += cache[arranged + 1][p][r - 1];
		}
	}
}

int main(int /* argc */, char ** /* argv */)
{
#ifdef DEBUG
	long long max_arrangements = 0;
#endif
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	int cases;
	cin >> cases;
	while (cases--) {
		int n, p, r;
		cin >> n >> p >> r;
		int arrangements = 0;
		if (n && p > 0 && p <= n && r >0 && r <= n) {
			vector< vector< vector<int> > > cache(n + 1, vector< vector<int> >(n + 1, vector<int>(n + 1, -1)));
			arrange_people(n, 0, p, r, arrangements, cache);
		}
		cout << arrangements << endl;
#ifdef DEBUG
		if (max_arrangements < arrangements)
			max_arrangements = arrangements;
#endif
	}
#ifdef DEBUG
	cerr << "max. arrangements = " << max_arrangements << endl;
#endif
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

