
/*
	UVa 10810 - Ultra-QuickSort

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10810_Ultra-QuickSort.cpp

	For the implementation, see:
	"Algorithms: How can I efficiently compute the number of swaps required by slow sorting methods like insertion sort and bubble sort to sort a given array?"
		(http://www.quora.com/Algorithms/How-can-I-efficiently-compute-the-number-of-swaps-required-by-slow-sorting-methods-like-insertion-sort-and-bubble-sort-to-sort-a-given-array)
*/

#include <iostream>
using namespace std;

const int n_max = 500000;
int array_[n_max], temporary_array_[n_max];

unsigned long long merge(int low, int middle, int high)
{
	unsigned long long nr_inversions = 0;
	for (int i = low; i <= high; i++)
		temporary_array_[i] = array_[i];
	int i = low, j = middle + 1;
    int k = low;
    // copy the smallest values from either the left or the right side back to the original array
	while (i <= middle && j <= high) {
		if (temporary_array_[i] <= temporary_array_[j]) {
			nr_inversions += j - middle - 1;
			array_[k++] = temporary_array_[i++];
		}
		else
			array_[k++] = temporary_array_[j++];
	}
	// copy the rest of the left side of the array into the target array
	nr_inversions += static_cast<unsigned long long>(j - middle - 1) * (middle - i + 1);
	while (i <= middle)
		array_[k++] = temporary_array_[i++];
	while (j <= high)
		array_[k++] = temporary_array_[j++];
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
			cin >> array_[i];
		unsigned long long nr_inversions = merge_sort(0, n - 1);
#ifdef DEBUG
		for (int i = 0; i < n; i++) {
			if (i)
				cout << ' ';
			cout << array_[i];
		}
		cout << endl;
#endif
		cout << nr_inversions << endl;
	}
	return 0;
}

