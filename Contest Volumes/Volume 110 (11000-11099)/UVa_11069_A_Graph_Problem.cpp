
/*
	UVa 11069 - A Graph Problem

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11069_A_Graph_Problem.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	const int n_max = 76;
	int nr_subsets[n_max + 1];
	nr_subsets[1] = 1; nr_subsets[2] = nr_subsets[3] = 2;
	for (int i = 4; i <= n_max; i++)
		nr_subsets[i] = nr_subsets[i - 2] + nr_subsets[i - 3];
	int n;
	while (cin >> n)
		cout << nr_subsets[n] << endl;
	return 0;
}

