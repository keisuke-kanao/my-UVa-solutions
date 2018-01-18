/*
	5.9.6 Polynomial Coefficients
	PC/UVa IDs: 110506/10105, Popularity: B, Success rate: high Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10105_Polynomial_Coefficients.cpp
*/

#include <iostream>
#include <vector>
using namespace std;

int factorial(int n)
{
	if (n <= 1)
		return 1;
	else
		return n * factorial(n - 1);
}

int calculate_coefficient(int n, int k, int i, const int* coefficients)
{
	// calculate the coefficient using the binomial coefficients formula and recursion
	if (i == k)
		return 1;
	else {
		int coefficient = *(coefficients + i);
		return factorial(n) / (factorial(n - coefficient) * factorial(coefficient)) *
			calculate_coefficient(n - coefficient, k, i + 1, coefficients);
	}
}

#ifdef DEBUG
int calculate_coefficient_ex(int n, int k, const int* coefficients)
{
	// calculate the coefficient using the multinomial theorem
	int coefficient = factorial(n);
	for (int i = 0; i < k; i++)
		coefficient /= factorial(coefficients[i]);
	return coefficient;
}
#endif

int main(int /* argc */, char** /* argv */)
{
	int n, k;
	while (cin >> n >> k) {
		vector<int> coefficients(k);
		for (int i = 0; i < k; i++)
			cin >> coefficients[i];
		cout << calculate_coefficient(n, k, 0, &coefficients[0]) << endl;
#ifdef DEBUG
		cout << calculate_coefficient_ex(n, k, &coefficients[0]) << endl;
#endif
	}
	return 0;
}

