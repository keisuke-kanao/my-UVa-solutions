
/*
	UVa 331 - Mapping the Swaps

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_331_Mapping_the_Swaps.cpp

	from ACM North Central Regional programming contest, 1994 Problem A

	The ACM ICPC Problem Set Archive
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive.html)
*/

#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

const int nr_values_max = 5;

int bubble_sort(int nr_values, int values[])
{
	int nr_swaps = 0;
	// do a bubble sort and count the number of swaps
	for (int i = nr_values - 1; i > 0; i--)
		for (int j = 0; j < i; j++)
			if (values[j] > values[j + 1]) {
				nr_swaps++;
				swap(values[j], values[j + 1]);
			}
	return nr_swaps;
}

bool are_values_sorted(int nr_values, const int values[])
{
	for (int i = 0; i < nr_values - 1; i++)
		if (values[i] > values[i + 1])
			return false;
	return true;
}

void bubble_sort(int nr_values, int values[], int nr_swaps, int& nr_swap_maps)
{
	if (!nr_swaps) {
		if (are_values_sorted(nr_values, values))
			nr_swap_maps++;
	}
	else {
		for (int i = 0; i < nr_values - 1; i++)
			if (values[i] > values[i + 1]) {
				swap(values[i], values[i + 1]);
				bubble_sort(nr_values, values, nr_swaps - 1, nr_swap_maps);
				swap(values[i], values[i + 1]);
			}
	}
}

int main()
{
	for (int s = 1; ; s++) {
		int nr_values;
		cin >> nr_values;
		if (!nr_values)
			break;
		int original_values[nr_values_max];
		for (int i = 0; i < nr_values; i++)
			cin >> original_values[i];
		int values[nr_values_max];
		memcpy(values, original_values, sizeof(int) * nr_values);
		int min_nr_swaps = bubble_sort(nr_values, values);
		int nr_swap_maps = 0;
		if (min_nr_swaps > 1) {
			memcpy(values, original_values, sizeof(int) * nr_values);
			bubble_sort(nr_values, values, min_nr_swaps, nr_swap_maps);
		}
		else
			nr_swap_maps = min_nr_swaps;
		cout << "There are " << nr_swap_maps << " swap maps for input data set " << s << ".\n";
	}
	return 0;
}

