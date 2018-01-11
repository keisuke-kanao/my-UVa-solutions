
/*
	UVa 10720 - Graph Construction

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10720_Graph_Construction.cpp
*/

/*
	The Erdos-Gallai theorem states that a non-increasing sequence of n numbers d(i) (for i = 1, ..., n) is 
	the degree sequence of a simple graph if and only if the sum of the sequence is even and 
		Σd(i) (i = 1 to k) <= k * (k - 1) + Σmin(d(i), k) (i = k + 1 to n) for k ∈ {1, ..., n}

	For the left hand side of the above equation:
	If k >= d(k):
		Σmin(d(i), k) (i = k + 1 to n) = Σd(i) (i = k + 1 to n)
										= Σd(i) (i = 1 to n) - Σd(i) (i = 1 to k)
	Else:
		Σmin(d(i), k) (i = k + 1 to n) = Σk (i = k + 1 to j) + Σd(i) (i = j + 1 to n)
										= k * (j - k) + Σd(i) (i = 1 to n) - Σd(i) (i = 1 to j)
*/

#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
using namespace std;

const int nr_degrees_max = 10000;
int nr_degrees, degrees[nr_degrees_max + 1] = {0};
long long partial_sum[nr_degrees_max + 1];

bool apply_erdos_gallai_theorem()
{
	for (int i = 1; i <= nr_degrees; i++)
		partial_sum[i] = partial_sum[i - 1] + degrees[i];
	for (int k = 1; k <= nr_degrees; k++) {
		int j = distance(degrees + 1, lower_bound(degrees + 1, degrees + nr_degrees + 1, k, greater<int>()));
		long long min_sum;
		if (j < k)
			min_sum = partial_sum[nr_degrees] - partial_sum[k];
		else
			min_sum = k * (j - k) + partial_sum[nr_degrees] - partial_sum[j];
		if (partial_sum[k] > k * (k - 1) + min_sum)
			return false;
	}
	return true;
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		nr_degrees = 0;
		long long sum = 0;
		bool possible = true;
		for (int i = 0; i < n; i++) {
			int v;
			cin >> v;
			if (v >= 0) {
				degrees[1 + nr_degrees++] = v;
				sum += v;
			}
			else if (v < 0)
				possible = false;
		}
		if (possible) {
			if (sum & 1)
				possible = false;
			else if (sum) {
				sort(degrees + 1, degrees + nr_degrees + 1, greater<int>());
				possible = apply_erdos_gallai_theorem();
			}
		}
		cout << ((possible) ? "Possible\n" : "Not possible\n");
	}
	return 0;
}

