
/*
	UVa 11005 - Cheapest Base

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11005_Cheapest_Base.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int nr_digits = 10, nr_letters = 26;
const int nr_bases = nr_digits + nr_letters;

struct base_cost {
	int base_;
	int cost_;

	bool operator<(const base_cost& bc) const {return cost_ < bc.cost_;}
};

int calculate_cost(int n, int base, const int* digit_costs, const int* letter_costs)
{
	int cost = 0;
	do {
		int m = n % base;
		if (m > 9)
			cost += letter_costs[m - 10];
		else
			cost += digit_costs[m];
		n /= base;
	} while (n);
	return cost;
}

int main()
{
	int digit_costs[nr_digits], letter_costs[nr_letters];
	base_cost costs[nr_bases + 1];
	int t;
	cin >> t;
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		for (int i = 0; i < nr_digits; i++)
			cin >> digit_costs[i];
		for (int i = 0; i < nr_letters; i++)
			cin >> letter_costs[i];
		int q;
		cin >> q;
		cout << "Case " << case_nr << ":\n";
		for (int i = 0; i < q; i++) {
			int n;
			cin >> n;
			for (int j = 2; j <= nr_bases; j++) {
				costs[j].base_ = j;
				costs[j].cost_ = calculate_cost(n, j, digit_costs, letter_costs);
			}
			stable_sort(costs + 2, costs + nr_bases + 1);
			cout << "Cheapest base(s) for number " << n << ':';
			for (int j = 2; j <= nr_bases; j++) {
				if (j > 2 && costs[j].cost_ > costs[j - 1].cost_)
					break;
				cout << ' ' << costs[j].base_;
			}
			cout << endl;
		}
		if (case_nr < t)
			cout << endl;
	}
	return 0;
}

