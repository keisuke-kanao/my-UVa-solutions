
/*
	UVa 1225 - Digit Counting

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_1225_Digit_Counting.cpp
*/

#include <iostream>
using namespace std;

const int n_max = 10000, nr_digits = 10;
int digits_counts[n_max][nr_digits];
	// digits_counts[i][j] is the number of times that digit of j appears for i

int main()
{
	for (int i = 1; i < n_max; i++) {
		int j = i;
		do {
			digits_counts[i][j % 10]++;
			j /= 10;
		} while (j);
	}
	for (int i = 2; i < n_max; i++)
		for (int j = 0; j < nr_digits; j++)
			digits_counts[i][j] += digits_counts[i - 1][j];
	int s;
	cin >> s;
	while (s--) {
		int n;
		cin >> n;
		for (int i = 0; i < nr_digits; i++) {
			if (i)
				cout << ' ';
			cout << digits_counts[n][i];
		}
		cout << endl;
	}
	return 0;
}

