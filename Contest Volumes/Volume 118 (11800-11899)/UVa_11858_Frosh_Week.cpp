
/*
	UVa 11858 - Frosh Week

	To build using Visucal Studio 2012:
		cl -EHsc -O2 UVa_11858_Frosh_Week.cpp

	This problem is similar to UVa 10810 - Ultra-QuickSort, 11495 - Bubbles and Buckets.
*/

#include <cstdio>

const int n_max = 1000000;
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
	int n;
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; i++)
			scanf("%d", &array[i]);
		printf("%llu\n", merge_sort(0, n - 1));
	}
	return 0;
}

