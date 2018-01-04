
/*
	UVa 344 - Roman Digititis

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_344_Roman_Digititis.cpp
*/

#include <iostream>
using namespace std;

struct roman_numeral {
	int nr_i_, nr_v_, nr_x_, nr_l_, nr_c_;
	roman_numeral() : nr_i_(0), nr_v_(0), nr_x_(0), nr_l_(0), nr_c_(0) {}
};

const int nr_max = 100;
roman_numeral numerals[nr_max + 1];

int main()
{
	roman_numeral n;
	for (int i = 1; i <= nr_max; i++) {
		if (i == nr_max)
			n.nr_c_++;
		else {
			int j = i / 10;
			if (j) {
				if (j == 4) {
					n.nr_x_++; n.nr_l_++;
				}
				else if (j == 5)
					n.nr_l_++;
				else if (j == 9) {
					n.nr_x_++; n.nr_c_++;
				}
				else if (j <= 3)
					n.nr_x_ += j;
				else {
					n.nr_l_++; n.nr_x_ += j - 5;
				}
			}
			j = i % 10;
			if (j == 4) {
				n.nr_i_++; n.nr_v_++;
			}
			else if (j == 5)
				n.nr_v_++;
			else if (j == 9) {
				n.nr_i_++; n.nr_x_++;
			}
			else if (j <= 3)
				n.nr_i_ += j;
			else {
				n.nr_v_++; n.nr_i_ += j - 5;
			}
		}
		numerals[i] = n;
	}

	while (true) {
		int p;
		cin >> p;
		if (!p)
			break;
		cout << p << ": " << numerals[p].nr_i_ << " i, " << numerals[p].nr_v_ << " v, " <<
			numerals[p].nr_x_ << " x, " << numerals[p].nr_l_ << " l, " << numerals[p].nr_c_ << " c\n";
	}
	return 0;
}

