
/*
	UVa 10113 - Exchange Rates

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10113_Exchange_Rates.cpp
*/

#include <iostream>
#include <string>
#include <map>
using namespace std;

struct exchange_rate {
	int numerator_, denominator_;
		// exchange rate = numerator_ / denominoator_
};

const int nr_items_max = 60;

exchange_rate exchange_rates[nr_items_max][nr_items_max];
	// exchange_rate[i][j] means (j-th item) = exchange_rate[i][j] * (i-th item)

int nr_items;
map<string, int> items;

int register_item(const string& s)
{
	pair<map<string, int>::iterator, bool> result = items.insert(make_pair(s, nr_items));
	if (result.second)
		nr_items++;
	return result.first->second;
}

int get_item(const string& s)
{
	return items[s];
}

int gcd(int x, int y)
{
	if (x < y)
		return gcd(y, x);
	else
	    return y == 0 ? x : gcd(y, x % y);
}

void calculate_exchange_rates()
{
	for (int k = 0; k < nr_items; k++)
		for (int i = 0; i < nr_items; i++)
			for (int j = 0; j < nr_items; j++)
				if (exchange_rates[i][k].numerator_ && exchange_rates[k][j].numerator_) {
					int n = exchange_rates[i][k].numerator_ * exchange_rates[k][j].numerator_,
						d = exchange_rates[i][k].denominator_ * exchange_rates[k][j].denominator_;
					int g = gcd(n, d);
					n /= g; d /= g;
					if (!exchange_rates[i][j].numerator_ ||
						exchange_rates[i][j].numerator_ * d < n * exchange_rates[i][j].denominator_) {
						exchange_rates[i][j].numerator_ = n;
						exchange_rates[i][j].denominator_ = d;
					}
			}
}

int main()
{
	char c;
	while (cin >> c) {
		if (c == '.')
			break;
		char d;
		int m, n;
		string a, b;
		if (c == '!') {
			cin >> m >> a >> d >> n >> b;
			int i = register_item(a), j = register_item(b);
			int g = gcd(m, n);
			exchange_rates[i][j].numerator_ = exchange_rates[j][i].denominator_ = m / g;
			exchange_rates[i][j].denominator_ = exchange_rates[j][i].numerator_ = n / g;
		}
		else {
			cin >> a >> d >> b;
			int i = get_item(a), j = get_item(b);
			calculate_exchange_rates();
			if (exchange_rates[i][j].numerator_)
				cout << exchange_rates[i][j].numerator_ << ' ' << a << " = " <<
					exchange_rates[i][j].denominator_ << ' ' << b << endl;
			else
				cout << "? " << a << " = ? " << b << endl;
		}
	}
	return 0;
}


