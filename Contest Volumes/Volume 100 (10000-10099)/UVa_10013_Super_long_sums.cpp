
/*
	UVa 10013 - Super long sums

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10013_Super_long_sums.cpp
*/

#include <iostream>
using namespace std;

const int m_max = 1000000;
char one_number[m_max + 1], other_number[m_max + 1];

int main()
{
	int n;
	cin >> n;
	while (n--) {
		int m;
		cin >> m;
		for (int i = 0; i < m; i++)
			cin >> one_number[i] >> other_number[i];
		one_number[m] = other_number[m] = '\0';
		for (int i = m - 1, carry = 0; i >= 0; i--) {
			int s = (one_number[i] - '0') + (other_number[i] - '0') + carry;
			if (s >= 10) {
				s -= 10;
				carry = 1;
			}
			else
				carry = 0;
			one_number[i] = s + '0';
		}
		cout << one_number << endl;
		if (n)
			cout << endl;
	}
	return 0;
}

