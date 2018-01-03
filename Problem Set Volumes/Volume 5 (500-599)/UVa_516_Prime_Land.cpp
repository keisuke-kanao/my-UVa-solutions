
/*
	UVa 516 - Prime Land

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_516_Prime_Land.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
using namespace std;

int fast_exp(int base, int power)
{
	if (!power)
		return 1;
	else if (!(power & 1)) {
		int fe = fast_exp(base, power >> 1);
		return fe * fe;
	}
	else
		return base * fast_exp(base, power - 1);
}

int prime_factorization(int n, vector<int>& powers)
{
	int max_power = -1;
	for (int i = 0; i <= n; i++)
		powers[i] = 0;
	for ( ; !(n & 1); n >>= 1) {
		max_power = 2;
		powers[2]++;
	}
	for (int i = 3, e = static_cast<int>(sqrt(static_cast<double>(n) + 1.0)); i <= e; ) {
		if (!(n % i)) {
			max_power = i;
			powers[i]++;
			n /= i;
		}
		else
			i += 2;
	}
	if (n > 1) {
		max_power = n;
		powers[n]++;
	}
	return max_power;
}

int main()
{
	const int n_max = 32767;
	vector<int> powers(n_max + 1); // powers[i] is the number of occurrences for the prime number of i
	while (true) {
		string line;
		getline(cin, line);
		istringstream iss(line);
		int p, e;
		iss >> p;
		if (!p)
			break;
		iss >> e;
		int n = fast_exp(p, e);
		while (iss >> p >> e)
			n *= fast_exp(p, e);
		n--;
		int max_power = prime_factorization(n, powers);
		bool printed = false;
		for (int i = max_power; i > 1; i--) {
			if (!powers[i])
				continue;
			if (printed)
				cout << ' ';
			else
				printed = true;
			cout << i << ' ' << powers[i];
		}
		cout << endl;
	}
	return 0;
}

