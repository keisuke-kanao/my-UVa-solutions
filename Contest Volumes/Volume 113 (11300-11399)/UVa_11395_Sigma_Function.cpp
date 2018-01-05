
/*
	UVa 11395 - Sigma Function

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11395_Sigma_Function.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

/*
Sigma Function of n is odd if and only if n is square or twice square.
*/

int main()
{
	while (true) {
		long long N;
		cin >> N;
		if (!N)
			break;
		int i = static_cast<int>(sqrt(static_cast<double>(N))),
			j = static_cast<int>(sqrt(static_cast<double>(N / 2)));
		cout << N - (i + j) << endl;
	}
	return 0;
}

