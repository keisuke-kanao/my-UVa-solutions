
/*
	UVa 640 - Self Numbers

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_640_Self_Numbers.cpp
*/

#include <iostream>
using namespace std;

const int n_max = 1000000;
bool generated_numbers[n_max + 1]; // generated_numbers[i] is true if i has a generater

int digitadition(int n)
{
	for (int m = n; m; m /= 10)
		n += m % 10;
	return n;
}

int main()
{
	for (int n = 1; n <= n_max; n++) {
		int d = digitadition(n);
		if (d <= n_max)
			generated_numbers[d] = true;
	}
	for (int n = 1; n <= n_max; n++)
		if (!generated_numbers[n])
			cout << n << endl;
	return 0;
}

