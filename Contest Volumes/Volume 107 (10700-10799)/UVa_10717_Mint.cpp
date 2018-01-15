
/*
	UVa 10717 - Mint

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10717_Mint.cpp
*/

#include <iostream>
#include <vector>
#include <set>
#include <limits>
#include <algorithm>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

/*
	lcm(a, b) = (a * b) / gcd(a, b)
	lcm(a, b, c) = lcm(a, lcm(b, c))
	lcm(a, b, c, d) = lcm(a, lcm(b, c, d))
*/

long long calculate_gcd(long long a, long long b)
{
	if (a < b)
		return calculate_gcd(b, a);
	if (!b)
		return a;
	else
		return calculate_gcd(b, a % b);
}

long long calculate_lcm(long long a, long long b)
{
		return (a * b) / calculate_gcd(a, b);
}

void calculate_lcms(int n, const vector<int>& coins, set<long long>& lcms)
{
	// C(50, 4) = 50! / {(50 - 4)!4!} = (50 * 49 * 48 * 47) / (4 * 3 * 2 * 1) = 50 * 49 * 2 * 47 = 230,300
	for (int i = 0; i < n - 3; i++)
		for (int j = i + 1; j < n - 2; j++) {
			long long lcm_i_j = calculate_lcm(coins[i], coins[j]);
			for (int k = j + 1; k < n - 1; k++) {
				long long lcm_i_j_k = calculate_lcm(lcm_i_j, coins[k]);
				for (int l = k + 1; l < n; l++)
					lcms.insert(calculate_lcm(lcm_i_j_k, coins[l]));
			}
		}
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (true) {
		int n, t;
		cin >> n >> t;
		if (!n && !t)
			break;
		vector<int> coins(n), tables(t);
		for (int i = 0; i < n; i++)
			cin >> coins[i];
		for (int i = 0; i < t; i++)
			cin >> tables[i];
		set<long long> lcms;
		calculate_lcms(n, coins, lcms);
		for (int i = 0; i < t; i++) {
			int table = tables[i];
			long long not_exceeding = numeric_limits<long long>::min(),
				not_less_than = numeric_limits<long long>::max();
			for (set<long long>::const_iterator j = lcms.begin(), e = lcms.end(); j != e; ++j) {
				long long lcm = *j;
				long long ne = (table / lcm) * lcm;
				if (ne == table) {
					not_exceeding = not_less_than = table;
					break;
				}
				else {
					not_exceeding = max(not_exceeding, ne);
					not_less_than = min(not_less_than, ne + lcm);
				}
			}
			cout << not_exceeding << ' ' << not_less_than << endl;
		}
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

