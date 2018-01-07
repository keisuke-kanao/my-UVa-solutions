
/*
	UVa 10025 - The ? 1 ? 2 ? ... ? n = k problem

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10025_n_k_problem.cpp
*/

/*
	For k = 0, n = 3
		- 1 - 2 + 3 = 0
	For k >= 1, if n satisfies the formula:
		? 1 ? 2 ? ... ? n = k ('?' is either '+' or '-')
	Then:
		sum_of_n - 2 * partial_sum_of_n = k
		partial_sum_of_n = (k - sum_of_n) / 2
	And also:
		partial_sum_of_n = sum_of_m - l, 0 <= l <= m <= n
*/

#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

int get_min_candidate_n(int k)
{
	return static_cast<int>(ceil((-1.0 + sqrt(1.0 + 8.0 * static_cast<double>(k))) / 2.0));
}

int sum_of_n(int n)
{
	return (n * (n + 1)) / 2;
}

bool is_partial_sum(int s, int n_max)
{
	int n = get_min_candidate_n(s);
	for (; n <= n_max; n++)
		if (sum_of_n(n) - s <= n)
			return true;
	return false;
}

int main()
{
	int nr_cases;
	cin >> nr_cases;
	for (int c = 0; c < nr_cases; c++) {
		int k;
		cin >> k;
		k = abs(k);
		if (k) {
			int n = get_min_candidate_n(k);
			for ( ; ; n++) {
				int partial_s = sum_of_n(n) - k;
				if (!partial_s)
					break;
				if (partial_s & 1)
					continue;
				partial_s >>= 1; // partial_s /= 2
				if (is_partial_sum(partial_s, n))
					break;
			}
			cout << n << endl;
		}
		else
			cout << 3 << endl;
		if (c < nr_cases - 1)
			cout << endl; // print a blank line between the outputs for two consecutive test cases
	}
	return 0;
}

