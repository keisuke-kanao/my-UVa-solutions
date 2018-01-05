
/*
	UVa 11042 - Complex, difficult and complicated

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11042_Complex_difficult_and_complicated.cpp
*/

#include <iostream>
using namespace std;

const long long abs_max = 1152921504606846976LL;

struct complex {
	long long r_, i_;
};

int multiply_complex(int n, const complex& multiplier, complex multiplicand)
{
	if (!multiplicand.i_)
		return n;
	else if (multiplicand.r_ * multiplicand.r_ + multiplicand.i_ * multiplicand.r_ > abs_max)
		return -1;
	else {
		complex c;
		c.r_ = multiplier.r_ * multiplicand.r_ - multiplier.i_ * multiplicand.i_;
		c.i_ = multiplier.r_ * multiplicand.i_ + multiplier.i_ * multiplicand.r_;
		return multiply_complex(n + 1, multiplier, c);
	}
}

int main()
{
	int M;
	cin >> M;
	while (M--) {
		int a, b;
		cin >> a >> b;
		complex multiplier, multiplicand;
		multiplier.r_ = multiplicand.r_ = a;
		multiplier.i_ = multiplicand.i_ = b;
		int n = multiply_complex(1, multiplier, multiplicand);
		if (n != -1)
			cout << n << endl;
		else
			cout << "TOO COMPLICATED\n";
	}
	return 0;
}

