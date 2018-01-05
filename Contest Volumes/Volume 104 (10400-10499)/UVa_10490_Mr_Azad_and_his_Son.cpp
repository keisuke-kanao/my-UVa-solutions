
/*
	UVa 10490 - Mr. Azad and his Son!!!!!

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10490_Mr_Azad_and_his_Son.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

bool is_prime(int n)
{
	if (n == 1)
		return false;
	else if (n == 2)
		return true;
	else if (!(n % 2))
		return false;
	else {
		for (int i = 3; i <= static_cast<int>(sqrt(static_cast<double>(n))) + 1; i += 2)
			if (!(n % i))
				return false;
	}
	return true;
}

int main()
{
	const int n_max = 31;
	long long even_perfect_numbers[n_max + 1];
	long long power_of_two = 1;
	for (int i = 1; i <= n_max; i++, power_of_two <<= 1) {
		if (is_prime(static_cast<int>((power_of_two << 1) - 1)))
			even_perfect_numbers[i] = power_of_two * ((power_of_two << 1) - 1);
		else if (is_prime(i))
			even_perfect_numbers[i] = 0;
		else
			even_perfect_numbers[i] = -1;
	}
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		if (even_perfect_numbers[n] > 0)
			cout << "Perfect: " << even_perfect_numbers[n] << "!\n";
		else if (!even_perfect_numbers[n])
			cout << "Given number is prime. But, NO perfect number is available.\n";
		else
			cout << "Given number is NOT prime! NO perfect number is available.\n";
	}
	return 0;
}

