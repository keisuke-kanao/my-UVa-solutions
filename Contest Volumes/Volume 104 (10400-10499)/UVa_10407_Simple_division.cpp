
/*
	UVa 10407 - Simple division

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10407_Simple_division.cpp
*/

/*
From Method to Solve (http://www.comp.nus.edu.sg/~stevenha/programming/volC4.html#10407_-_Simple_division):

The idea is to find GCD of multiple numbers.

Example from sample input 1:
The value d = 179 can divide the set of integers { 701 1059 1417 2312 },
leaving the same remainder r = 164.

Value d can be calculated by finding the GCD of =
GCD (1059-701, 1417-701, 2312-701) =
GCD (358, 716, 1611) = 179

Since GCD (179) will exactly divides 358, 716, 1611 without any remainders..., 
then all the original numbers {701 1059 1417 2312} will have remainder of exactly 701 mod 179 = 164. 
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int n_max = 1000;
int numbers[n_max + 1];

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

int main()
{
	while (true) {
		cin >> numbers[0];
		if (!numbers[0])
			break;
		int n = 1, min_number = numbers[0];
		while (true) {
			cin >> numbers[n];
			if (!numbers[n])
				break;
			min_number = min(min_number, numbers[n]);
			n++;
		}
		for (int i = 0; i < n; i++)
			numbers[i] -= min_number;
		int d = gcd(numbers[0], numbers[1]);
		for (int i = 2; i < n; i++)
			d = gcd(d, numbers[i]);
		cout << d << endl;
	}
	return 0;
}

