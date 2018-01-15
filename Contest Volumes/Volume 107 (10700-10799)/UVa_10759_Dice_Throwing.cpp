
/*
	UVa 10759 - Dice Throwing

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10759_Dice_Throwing.cpp
*/

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

const int n_max = 24, x_max = 150;
long long dice_throwings[n_max + 1][x_max + 1]; // cache
	// dice_throwings[n][x] is the number of cases in which the sum of all thrown dice is less than x when n dice are thrown

void intialize_cache()
{
	for (int i = 0; i <= n_max; i++)
		for (int j = 0; j <= x_max; j++)
			dice_throwings[i][j] = -1;
	dice_throwings[1][0] = 0;
	for (int j = 1; j <= 6; j++)
		dice_throwings[1][j] = j - 1;
	for (int j = 7; j <= x_max; j++)
		dice_throwings[1][j] = 6;
}

long long dice_throwing(int n, int x)
// return the number of cases in which the sum of all thrown dice is less than x when n dice are thrown
{
	if (dice_throwings[n][x] != -1)
		return dice_throwings[n][x];
	else {
		long long nr_cases = 0;
		for (int i = 1, j = min(x, 6); i <= j; i++)
			nr_cases += dice_throwing(n - 1, x - i);
		dice_throwings[n][x] = nr_cases;
		return nr_cases;
	}
}

long long calculate_gcd(long long a, long long b)
{
	if (a < b)
		return calculate_gcd(b, a);
	if (!b)
		return a;
	else
		return calculate_gcd(b, a % b);
}

int main()
{
	intialize_cache();
	while (true) {
		int n, x;
		cin >> n >> x;
		if (!n && !x)
			break;
		long long denominator = static_cast<long long>(pow(6.0, static_cast<double>(n)));
		long long numerator = denominator - dice_throwing(n, x);
		if (numerator) {
			long long gcd = calculate_gcd(numerator, denominator);
			numerator /= gcd; denominator /= gcd;
		}
		if (!numerator)
			cout << 0 << endl;
		else if (denominator == 1)
			cout << 1 << endl;
		else
			cout << numerator << '/' << denominator << endl;
	}
	return 0;
}

