
/*
	UVa 11636 - Hello World!

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11636_Hello_World.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	const double log2 = log10(2.0);
	for (int c = 1; ; c++) {
		int n;
		cin >> n;
		if (n < 0)
			break;
		int nr_pastes = static_cast<int>(ceil(log10(static_cast<double>(n)) / log2));
		cout << "Case " << c << ": " << nr_pastes << endl;
	}
	return 0;
}

