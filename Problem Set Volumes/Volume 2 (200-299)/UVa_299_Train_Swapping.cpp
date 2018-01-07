
/*
	UVa 299 - Train Swapping

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_299_Train_Swapping.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int bubble_sort(int l, vector<int>& trains)
{
	int nr_swaps = 0;
	// do a bubble sort and count the number of swaps
	for (int i = l - 1; i > 0; i--)
		for (int j = 0; j < i; j++)
			if (trains[j] > trains[j + 1]) {
				nr_swaps++;
				swap(trains[j], trains[j + 1]);
			}
	return nr_swaps;
}

int main()
{
	int n;
	cin >> n;
	while (n--) {
		int l;
		cin >> l;
		vector<int> trains(l);
		for (int i = 0; i < l; i++)
			cin >> trains[i];
		int nr_swaps = bubble_sort(l, trains);
		cout <<"Optimal train swapping takes " << nr_swaps << " swaps.\n";
	}
	return 0;
}

