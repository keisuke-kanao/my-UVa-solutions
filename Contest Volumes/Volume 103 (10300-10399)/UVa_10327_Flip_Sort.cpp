
/*
	UVa 10327 - Flip Sort

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10327_Flip_Sort.cpp

	This problem is exactly same as 299 - Train Swapping.
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int nr_max = 1000;
int numbers[nr_max];

int bubble_sort(int n)
{
	int nr_swaps = 0;
	// do a bubble sort and count the number of swaps
	for (int i = n - 1; i > 0; i--)
		for (int j = 0; j < i; j++)
			if (numbers[j] > numbers[j + 1]) {
				nr_swaps++;
				swap(numbers[j], numbers[j + 1]);
			}
	return nr_swaps;
}

int main()
{
	int n;
	while (cin >> n) {
		for (int i = 0; i < n; i++)
			cin >> numbers[i];
		int nr_swaps = bubble_sort(n);
		cout << "Minimum exchange operations : " << nr_swaps << endl;
	}
	return 0;
}

