
/*
	UVa 11703 - sqrt log sin

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11703_sqrt_log_sin.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

const int i_max = 1000000;
int x[i_max + 1]; // x[i] is the x(i) mod 1000000

int main()
{
	int i;
	x[0] = 1;
	for (i = 1; i <= i_max; i++) {
		double di = static_cast<double>(i);
		x[i] = x[static_cast<int>(di - sqrt(di))] + x[static_cast<int>(log(di))] +
			x[static_cast<int>(di * sin(di) * sin(di))];
		x[i] %= i_max;
	}
	while (true) {
		cin >> i;
		if (i == -1)
			break;
		cout << x[i] << endl;
	}
	return 0;
}

