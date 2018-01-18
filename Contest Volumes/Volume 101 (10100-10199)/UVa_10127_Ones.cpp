
/*
	5.9.4 Ones
	PC/UVa IDs: 110504/10127, Popularity: A, Success rate: high Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10127_Ones.cpp
*/

#include <iostream>
using namespace std;

int ones(int n)
{
	int nr_ones = 0, sum = 0;
	do {
		int i = 0;
		for ( ; ; i++)
			if ((sum + n * i) % 10 == 1)
				break;
		nr_ones++;
		sum += n * i; sum /= 10;
	} while (sum);
	return nr_ones; 
}

int main(int /* argc */, char** /* argv */)
{
	int n;
	while (cin >> n)
		cout << ones(n) << endl;
	return 0;
}

