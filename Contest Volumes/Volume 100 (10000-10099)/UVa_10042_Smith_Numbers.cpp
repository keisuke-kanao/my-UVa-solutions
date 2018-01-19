
/*
	7.6.6 Smith Numbers
	PC/UVa IDs: 110706/10042, Popularity: B, Success rate: average Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10042_Smith_Numbers.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

int sum_of_number_digits(int n)
{
	int sum = 0;
	for ( ; n; n /= 10)
		sum += n % 10;
	return sum;
}

int sum_of_prime_number_digits(int n)
{
	if (n == 2)
		return -1;
	int max_divisor = static_cast<int>(ceil(sqrt(static_cast<double>(n))));
	int sum = 0;
	for ( ; !(n & 1); n /= 2)
		sum += 2;
	for (int divisor = 3; n > 2 && divisor <= max_divisor; ) {
		if (!(n % divisor)) {
			n /= divisor;
			sum += sum_of_number_digits(divisor);
		}
		else
			divisor += 2;
	}
	if (n > 2) {
		if (!sum) // the given number is a prime
			return -1;
		else
			sum += sum_of_number_digits(n);
	}
	return sum;
}

int main(int /* argc */, char** /* argv */)
{
	int cases;
	cin >> cases;
	while (cases--) {
		int n;
		cin >> n;
		for (n++; ; n++)
			if (sum_of_prime_number_digits(n) == sum_of_number_digits(n)) {
				cout << n << endl;
				break;
			}
	}
	return 0;
}

