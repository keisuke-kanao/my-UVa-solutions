
/*
	UVa 166 - Making Change

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_166_Making_Change.cpp

	from ACM South Pacific Regionals - 1991
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_VV_SouthPac/1991/index.html)
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

const int nr_coin_values = 6;
const int coin_values[nr_coin_values + 1] = {0, 1, 2, 4, 10, 20, 40}; // in units of 5c
int nr_coins[nr_coin_values + 1];
const int value_max = 140; // in units of 5c
int min_nr_coins[nr_coin_values + 1][value_max + 1];
  // min_nr_coins[k][i] is the minimum number of coins to pay the value of i using the first k coin values

int get_value(const string &s)
{
	const char* p = s.c_str();
	int value = (*p++ - '0') * 100;
	if (*p) {
		p++;
		value += (*p++ - '0') * 10;
		if (*p)
			value += *p - '0';
	}
	return value / 5;
}

int nr_change_coins(int value /* in units of 5c */)
{
	int nr = 0;
	for (int i = nr_coin_values; i > 0; i--) {
		int j = value / coin_values[i];
		if (j) {
			nr += j;
			value -= j * coin_values[i];
		}
	}
	return nr;
}

int main()
{
	while (true) {
		int sum_nr_coins = 0;
		for (int i = 1; i <= nr_coin_values; i++) {
			cin >> nr_coins[i];
			sum_nr_coins += nr_coins[i];
		}
		if (!sum_nr_coins)
			break;
		string s;
		cin >> s;
		int value = get_value(s);

		for (int k = 1; k <= nr_coin_values; k++)
			for (int i = 1; i <= value_max; i++)
				min_nr_coins[k][i] = sum_nr_coins + 1;
		for (int i = 1; i <= nr_coins[1]; i++) {
			int cv = coin_values[1] * i;
			if (cv > value_max)
				break;
			min_nr_coins[1][cv] = i;
		}
		for (int k = 2; k <= nr_coin_values; k++)
			for (int i = 0; i <= nr_coins[k]; i++) {
				int cv = coin_values[k] * i;
				for (int j = 1; j <= value_max; j++)
					min_nr_coins[k][j] = (j < cv) ?
						min(min_nr_coins[k - 1][j], min_nr_coins[k][j]) :
						min(min_nr_coins[k - 1][j], min_nr_coins[k - 1][j - cv] + i);
			}
#ifdef DEBUG
		for (int k = 1; k <= nr_coin_values; k++) {
			for (int i = 1; i <= value + coin_values[nr_coin_values]; i++)
				cout << setfill(' ') << setw(3) << min_nr_coins[k][i];
			cout << endl;
		}
#endif
		int min_nr_changes = numeric_limits<int>::max();
		for (int i = value; i <= value + coin_values[nr_coin_values]; i++) {
			if (min_nr_coins[nr_coin_values][i] <= sum_nr_coins)
				min_nr_changes = min(min_nr_changes, min_nr_coins[nr_coin_values][i] + nr_change_coins(i - value));
		}
		cout << setfill(' ') << setw(3) << min_nr_changes << endl;
	}
	return 0;
}

