
/*
	UVa 11495 - Bubbles and Buckets

	To build using Visucal Studio 2010:
		cl -EHsc -O2 UVa_11495_Bubbles_and_Buckets.cpp

	This problem is similar to UVa 10810 - Ultra-QuickSort.
*/

#ifdef ONLINE_JUDGE

// An accepted solution.

#include <iostream>
using namespace std;

const int n_max = 100000;
int array[n_max], temporary_array[n_max];

unsigned long long merge(int low, int middle, int high)
{
	unsigned long long nr_inversions = 0;
	for (int i = low; i <= high; i++)
		temporary_array[i] = array[i];
	int i = low, j = middle + 1;
    int k = low;
    // copy the smallest values from either the left or the right side back to the original array
	while (i <= middle && j <= high) {
		if (temporary_array[i] <= temporary_array[j]) {
			nr_inversions += j - middle - 1;
			array[k++] = temporary_array[i++];
		}
		else
			array[k++] = temporary_array[j++];
	}
	// copy the rest of the left side of the array into the target array
	nr_inversions += static_cast<unsigned long long>(j - middle - 1) * (middle - i + 1);
	while (i <= middle)
		array[k++] = temporary_array[i++];
	while (j <= high)
		array[k++] = temporary_array[j++];
	return nr_inversions;
}

unsigned long long merge_sort(int low, int high)
{
	unsigned long long nr_inversions = 0;
	if (low < high) {
		int middle = (low + high) / 2;
		nr_inversions = merge_sort(low, middle); // sort the left side of the array
		nr_inversions += merge_sort(middle + 1, high); // sort the right side of the array
		nr_inversions += merge(low, middle, high); // combine them both
	}
	return nr_inversions;
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			cin >> array[i];
		unsigned long long nr_inversions = merge_sort(0, n - 1);
#ifdef DEBUG
		cout << nr_inversions << endl;
#endif
		cout << ((nr_inversions & 1) ? "Marcelo\n" : "Carlos\n");
	}
	return 0;
}

#else // !ONLINE_JUDGE

// Time Limit Exceeded.

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		long long nr_swaps = 0;
		vector<int> integers;
		while (n--) {
			int i;
			cin >> i;
			vector<int>::iterator ii = lower_bound(integers.begin(), integers.end(), i);
			ii = integers.insert(ii, i);
			int j = static_cast<int>(distance(integers.begin(), ii)) + 1;
			nr_swaps += i - j;
		}
#ifdef DEBUG
		cout << nr_swaps << endl;
#endif
		cout << ((nr_swaps & 1) ? "Marcelo\n" : "Carlos\n");
	}
	return 0;
}

#endif // ONLINE_JUDGE

