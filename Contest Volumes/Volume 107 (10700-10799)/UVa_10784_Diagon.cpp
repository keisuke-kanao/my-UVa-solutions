
/*
	UVa 10784 - Diagonal

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10784_Diagon.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

/*
	Let d(n) be the maximum number of diagonals for the n-gon, then:
		d(3) = 0.
		d(n) = d(n - 1) + (n - 2) (n >= 4).
			 = Σ(i - 2) (i = 4 to n)
			 = n * (n - 3) / 2
*/

int main()
{
	for (int c = 1; ; c++) {
		long long N;
		cin >> N;
		if (!N)
			break;
		long long n = static_cast<long long>((3.0 + sqrt(9.0 + static_cast<double>(N) * 8.0)) / 2.0);
		if ((n * (n - 3)) / 2 < N)
			n++;
		cout << "Case " << c << ": " << n << endl;
	}
	return 0;
}

