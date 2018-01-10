
/*
	UVa 11198 - Dancing Digits

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11198_Dancing_Digits.cpp
*/

#include <iostream>
#ifdef DEBUG
#include <iomanip>
#endif
#include <queue>
#include <map>
#include <cstdlib>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int nr_digits = 8;

bool dancing_digits(int i, int j, long long digits, int nr_dances, queue<long long>& q, map<long long, int>& cache);
int dancing_digits(long long digits);

bool are_digits_sorted(long long digits) // see if the digits are sorted
{
	for (int i = 0; i < nr_digits; i++, digits >>= 8) {
		char d = static_cast<char>(digits & 0xff);
		if (abs(d) != i + 1) // see if d is at the right place
			return false;
	}
	return true;
}

int get_digit(int i, long long digits) // return i-th digit from digits
{
	char d = static_cast<char>((digits >> (i * 8)) & 0xff);
	return static_cast<int>(d);
}

long long set_digit(int i, int d, long long digits)
{
	long long mask = static_cast<long long>(0xff) << (i * 8);
	digits &= ~mask;
	digits |= static_cast<long long>(static_cast<unsigned char>(d)) << (i * 8);
	return digits;
}

bool are_dancing_pairs(int i, int j, long long digits)
{
	int d = get_digit(i, digits), e = get_digit(j, digits);
	if (d * e > 0)
		return false;
	d = abs(d); e = abs(e);
	return (d == 1 && (e == 2 || e == 4 || e == 6) || d == 2 && (e == 1 || e == 3 || e == 5) ||
			d == 3 && (e == 2 || e == 4 || e == 8) || d == 4 && (e == 1 || e == 3 || e == 7) ||
			d == 5 && (e == 2 || e == 6 || e == 8) || d == 6 && (e == 1 || e == 5 || e == 7) ||
			d == 7 && (e == 4 || e == 6) || d == 8 && (e == 3 || e == 5));
}

long long insert_digit(int i, int j, long long digits) // insert i-th digit before j-th digit in digits
{
	if (i < j - 1) {
		int d = get_digit(i, digits);
		for ( ; i < j - 1; i++)
			digits = set_digit(i, get_digit(i + 1, digits), digits);
		digits = set_digit(j - 1, d, digits);
	}
	else if (i > j) {
		int d = get_digit(i, digits);
		for ( ; i > j; i--)
			digits = set_digit(i, get_digit(i - 1, digits), digits);
		digits = set_digit(j, d, digits);
	}
	return digits;
}

bool dancing_digits(int i, int j, long long digits, int nr_dances, queue<long long>& q, map<long long, int>& cache)
{
	digits = insert_digit(i, j, digits);
	pair<map<long long, int>::iterator, bool> result = cache.insert(make_pair(digits, nr_dances));
	if (result.second)
		q.push(digits);
	return result.second;
}

int dancing_digits(long long digits)
{
	map<long long, int> cache;
		// key is a state (digits), value is the number of dances that leads to it
	cache.insert(make_pair(digits, 0));
	queue<long long> q;
	q.push(digits);
	bool sorted;
	int nr_dances;
	while (!q.empty()) {
		digits = q.front(); q.pop();
		nr_dances = cache[digits];
		if (sorted = are_digits_sorted(digits))
			break;
		nr_dances++;
		for (int i = 0; i < nr_digits - 1; i++)
			for (int j = i + 1; j < nr_digits; j++)
				if (are_dancing_pairs(i, j, digits)) {
					if (j != i + 1) {
						dancing_digits(i, j, digits, nr_dances, q, cache);
						dancing_digits(j, i, digits, nr_dances, q, cache);
						dancing_digits(j, i + 1, digits, nr_dances, q, cache);
					}
					if (j < nr_digits - 1)
						dancing_digits(i, j + 1, digits, nr_dances, q, cache);
				}
	}
	return (sorted) ? nr_dances : -1;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	for (int c = 1; ; c++) {
		int d;
		cin >> d;
		if (!d)
			break;
		long long digits = static_cast<unsigned char>(d); // i-th (i >= 0) digit occupies bit (i * 8) - (i * 8 + 7)
		for (int i = 1; i < nr_digits; i++) {
			cin >> d;
			digits |= static_cast<long long>(static_cast<unsigned char>(d)) << (8 * i);
		}
#ifdef DEBUG
		cout << hex << setfill('0') << setw(16) << digits << dec << endl;
#endif
		cout << "Case " << c << ": " << dancing_digits(digits) << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

