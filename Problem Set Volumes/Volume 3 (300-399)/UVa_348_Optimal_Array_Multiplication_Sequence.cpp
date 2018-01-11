
/*
	UVa 348 - Optimal Array Multiplication Sequence

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_348_Optimal_Array_Multiplication_Sequence.cpp

	from 1996 ACM North Central Programming Contest November 9, 1996 Problem D
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1996/)
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>
using namespace std;

/*
	Let m[i][j] be the minimum number of muliplications between arrays[i] and arrays[j], then:
		m[i][j] = min{m[i][k], m[k + 1][j] +
			rows(arrays[i]) * columns(arrays[j]) * columns(arrays[k]} (i <= k < j).
		m[i][i] = 0.
*/

int calculate_number_of_multiplications(int n, const vector< pair<int, int> >& arrays,
	vector< vector<int> >& multiplications, vector< vector<int> >& multiplicands)
{
	for (int i = 0; i < n; i++)
		multiplications[i][i] = 0;
	for (int na = 1; na < n; na++) // number of intervales between the first and last arrays to multiply
		for (int i = 0, j = na; j < n; i++, j++)
			for (int k = i; k < j; k++) {
				int m = multiplications[i][k] + multiplications[k + 1][j] +
					arrays[i].first * arrays[j].second * arrays[k].second;
				if (m < multiplications[i][j]) {
					multiplications[i][j] = m; multiplicands[i][j] = k;
				}
			}
	return multiplications[0][n - 1];
}

void print_multiplication_sequence(int i, int j, vector< vector<int> >& multiplicands)
{
	cout << '(';
	int k = multiplicands[i][j];
	if (i == k)
		cout << 'A' << i + 1 << " x ";
	else {
		print_multiplication_sequence(i, k, multiplicands);
		cout << " x ";
	}
	if (j == k + 1)
		cout << 'A' << j + 1;
	else
		print_multiplication_sequence(k + 1, j, multiplicands);
	cout << ')';
}

int main()
{
	for (int c = 1; ; c++) {
		int n;
		cin >> n;
		if (!n)
			break;
		vector< pair<int, int> > arrays(n);
			// arrays[i].first is the i-th array's row, arrays[i].first is the i-th array's column.
		for (int i = 0; i < n; i++)
			cin >> arrays[i].first >> arrays[i].second;
		vector< vector<int> > multiplications(n, vector<int>(n, numeric_limits<int>::max()));
			// multiplications[i][j] is the minimum number of muliplications between arrays[i] and arrays[j].
		vector< vector<int> > multiplicands(n, vector<int>(n, -1));
			// multiplicands[i][j] is the index to arrays in which muliplications between arrays[i] and arrays[j]
			// are parenthesized for the case when it has the minimum number of muliplications.
		if (n > 1)
			calculate_number_of_multiplications(n, arrays, multiplications, multiplicands);
		cout << "Case " << c << ": ";
		if (n > 1)
			print_multiplication_sequence(0, n - 1, multiplicands);
		else
			cout << "(A1)";
		cout << endl;
	}
	return 0;
}

