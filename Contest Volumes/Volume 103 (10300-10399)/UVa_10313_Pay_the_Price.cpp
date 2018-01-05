
/*
	UVa 10313 - Pay the Price

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_10313_Pay_the_Price.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int n_max = 300;
long long nr_ways[n_max + 1][n_max + 1];
	// nr_ways[i][j] is the number of ways in which i dollars can be paid using j or less coins

int main()
{
	for (int i = 0; i <= n_max; i++)
		nr_ways[i][0] = 0;
	for (int j = 0; j <= n_max; j++)
		nr_ways[0][j] = 1;
	for (int i = 1; i <= n_max; i++)
		for (int j = 1; j <= n_max; j++) {
			long long nr = 0;
			if (i < j)
				nr = nr_ways[i][j - 1];
			else
				for (int k = 1; k <= j; k++)
					nr +=nr_ways[i - k][k];
			nr_ways[i][j] = nr;
		}

	string s;
	while (getline(cin, s)) {
		istringstream iss(s);
		int n, l1 = -1, l2 = -1;
		iss >> n;
		if (iss)
			iss >> l1;
		if (iss)
			iss >> l2;
		if (l2 > n_max)
			l2 = n;
		if (l1 > n_max)
			l1 = n;
		if (l1 >= 0 && l2 >= 0) {
			if (l1)
				cout << nr_ways[n][l2] - nr_ways[n][l1 - 1] << endl;
			else
				cout << nr_ways[n][l2] << endl;
		}
		else if (l1 >= 0)
			cout << nr_ways[n][l1] << endl;
		else
			cout << nr_ways[n][n] << endl;
	}
	return 0;
}

