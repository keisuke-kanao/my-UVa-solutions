
/*
	UVa 10591 - Happy Number

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10591_Happy_Number.cpp
*/

#include <iostream>
#include <set>
#include <cstring>
using namespace std;

const int nr_happy_numbers_max = 9 * 9 * 9;
bool happy_numbers[nr_happy_numbers_max + 1];
	// happy_numbers[i] is true if i is a happy number

bool is_happy_number(int n)
{
	if (n <= nr_happy_numbers_max && happy_numbers[n])
		return true;
	set<int> numbers;
	numbers.insert(n);
	while (true) {
		int s = 0; // sum of the square of the digits of n
		while (n / 10) {
			int i = n % 10;
			s += i * i;
			n /= 10;
		}
		s += n * n;
#ifdef DEBUG
		cout << s << endl;
#endif
		if (s <= nr_happy_numbers_max && happy_numbers[s]) {
			for (set<int>::const_iterator j = numbers.begin(), e = numbers.end(); j != e; ++j)
				if (*j <= nr_happy_numbers_max)
					happy_numbers[*j] = true;
			return true;
		}
		pair<set<int>::iterator, bool> result = numbers.insert(s);
		if (!result.second)
			return false;
		n = s;
	}
}

int main()
{
	memset(happy_numbers, 0, sizeof(happy_numbers));
	happy_numbers[1] = true;
	int t;
	cin >> t;
	for (int c = 1; c <= t; c++) {
		int n;
		cin >> n;
		cout << "Case #" << c << ": " << n <<
		((is_happy_number(n)) ? " is a Happy number.\n" : " is an Unhappy number.\n");
	}
	return 0;
}

