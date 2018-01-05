
/*
	UVa 10482 - The Candyman Can

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10482_The_Candyman_Can.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int n_max = 32, weight_max = 20;
const int sum_of_weights_max = n_max * weight_max;

int weights[n_max + 1];
int sum_of_weights[n_max + 1]; // sum of weghts up to i
bool subset_sums[sum_of_weights_max + 1][sum_of_weights_max + 1];
	// subset_sums[a][b] is true if there is a subset of weights whose sums are a, b

int badness(int s, int a, int b)
{
	int c = s - (a + b);
	return max(max(a, b), c) - min(min(a, b), c);
}

int main()
{
	int t;
	cin >> t;
	for (int c = 1; c <= t; c++) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++) {
			cin >> weights[i];
			sum_of_weights[i] = sum_of_weights[i - 1] + weights[i];
		}
		int s = sum_of_weights[n];
		for (int a = 0; a <= s; a++)
			for (int b = 0; b <= s; b++)
					subset_sums[a][b] = false;
		subset_sums[0][0] = true;
		for (int i = 1; i <= n; i++) {
			int si = sum_of_weights[i], wi = weights[i];
			for (int a = si; a >= 0; a--)
				for (int b = si; b >= 0; b--)
					if (a >= wi && subset_sums[a - wi][b] || b >= wi && subset_sums[a][b - wi])
						subset_sums[a][b] = true;
#ifdef DEBUG
			cout << i << ':';
			for (int a = 0; a <= si; a++)
				for (int b = 0; b <= si; b++)
					if (subset_sums[a][b]) 
						cout << " [" << a << ", " << b << ']';
			cout << endl;
#endif
		}
		int min_badness = s;
		for (int a = 0; a <= s; a++)
			for (int b = 0; b <= s; b++)
				if (subset_sums[a][b])
					min_badness = min(min_badness, badness(s, a, b));
		cout << "Case " << c << ": " << min_badness << endl;
	}
	return 0;
}

