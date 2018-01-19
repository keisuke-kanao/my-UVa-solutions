
/*
	7.6.1 Light, More Light
	PC/UVa IDs: 110701/10110, Popularity: A, Success rate: average Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10110_Light_More_Light.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

/*
	For every factor n has below sqrt(n) it has one above sqrt(n).
	This suggests that unless n is a perfect square, it has an even number of factors. 
	So, the problem boils down to deciding if n is a perfect square or not.
*/

bool have_odd_divisors(unsigned int n)
{
	unsigned int sqrt_n = static_cast<unsigned int>(sqrt(static_cast<double>(n)));
	return sqrt_n * sqrt_n == n;
}

int main(int /* argc */, char** /* argv */)
{
	unsigned int n;
	while (cin >> n) {
		if (!n)
			break;
		cout << ((have_odd_divisors(n)) ? "yes\n" : "no\n");
	}
	return 0;
}

