
/*
	UVa 541 - Error Correction

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_541_Error_Correction.cpp

	from University of Ulm Local Contest 1998 Problem E
		(http://www.informatik.uni-ulm.de/acm/Locals/1998/)
*/

#include <iostream>
using namespace std;

const int n_max = 100;
int matrix[n_max][n_max];

int parity_property(int n, int& r, int& c)
{
	r = c = -1;
	for (int i = 0; i < n; i++) {
		int nr_bits = 0;
		for (int j = 0; j < n; j++)
			if (matrix[i][j])
				nr_bits++;
		if (nr_bits & 1) {
			if (r == -1)
				r = i;
			else
				return 2; // corrupted
		}
	}
	for (int i = 0; i < n; i++) {
		int nr_bits = 0;
		for (int j = 0; j < n; j++)
			if (matrix[j][i])
				nr_bits++;
		if (nr_bits & 1) {
			if (c == -1)
				c = i;
			else
				return 2; // corrupted
		}
	}
	return (r == -1 && c == -1) ? 0 : 1;
}

int main()
{
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> matrix[i][j];
		int r, c;
		int result = parity_property(n, r, c);
		if (!result)
			cout << "OK\n";
		else if (result == 1)
			cout << "Change bit (" << r + 1 << ',' << c + 1 << ")\n";
		else
			cout << "Corrupt\n";
	}
	return 0;
}

