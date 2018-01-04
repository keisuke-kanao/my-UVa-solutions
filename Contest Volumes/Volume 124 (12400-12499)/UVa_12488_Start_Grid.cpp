
/*
	UVa 12488 - Start Grid

	To build using Visucal Studio 2012:
		cl -EHsc -O2 UVa_12488_Start_Grid.cpp

	This problem is similar to UVa 10810 - Ultra-QuickSort, 11495 - Bubbles and Buckets, 11858 - Frosh Week.
*/

#include <cstdio>

const int n_max = 24;
int array[n_max], temporary_array[n_max];

int merge(int low, int middle, int high)
{
	int nr_inversions = 0;
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
	nr_inversions += static_cast<int>(j - middle - 1) * (middle - i + 1);
	while (i <= middle)
		array[k++] = temporary_array[i++];
	while (j <= high)
		array[k++] = temporary_array[j++];
	return nr_inversions;
}

int merge_sort(int low, int high)
{
	int nr_inversions = 0;
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
	int n, start[n_max];
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; i++)
			scanf("%d", &start[i]);
		for (int i = 0; i < n; i++) {
			int m;
			scanf("%d", &m);
			for (int j = 0; j < n; j++)
				if (start[j] == m) {
					array[j] = i; break;
				}
		}
		printf("%d\n", merge_sort(0, n - 1));
	}
	return 0;
}

