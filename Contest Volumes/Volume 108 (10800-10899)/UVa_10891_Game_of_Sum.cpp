
/*
	UVa 10891 - Game of Sum

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10891_Game_of_Sum.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int n_max = 100;
int numbers[n_max];
long long sums[n_max]; // sums[i] is the sum of up to i-th numbers
long long max_diffs[n_max][n_max];

long long sum(int i, int j)
{
	long long s = sums[j];
	if (i)
		s -= sums[i - 1];
	return s;
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		for (int i = 0; i < n; i++) {
			cin >> numbers[i];
			sums[i] = numbers[i];
			if (i)
				sums[i] += sums[i - 1];
		}
		for (int i = 0; i < n; i++)
			max_diffs[i][i] = numbers[i];
		for (int d = 1; d < n; d++)
			for (int i = 0, j = d; j < n; i++, j++) {
				long long s = sum(i, j);
				max_diffs[i][j] = s;
				for (int k = i; k < j; k++)
					max_diffs[i][j] = max(max_diffs[i][j], s - min(max_diffs[i][k], max_diffs[k + 1][j]));
#ifdef DEBUG
				cout << "max_diffs[" << i << "][" << j << "] = " << max_diffs[i][j] << endl;
#endif
			}
		cout << 2 * max_diffs[0][n - 1] - sum(0, n - 1) << endl;
	}
	return 0;
}

