
/*
	UVa 10881 - Piotr's Ants

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10881_Piotrs_Ants.cpp

	An accepted solution.
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int n_max = 10000;

struct ant {
	int index_;
	int loc_;
	bool turning_;
	char dir_;
} ants[n_max];

int input_orders[n_max];

bool compare_location(const ant& i, const ant& j)
{
	return i.loc_ < j.loc_;
}

int main()
{
	int N;
	cin >> N;
	for (int cn = 1; cn <= N; cn++) {
		int L, T, n;
		cin >> L >> T >> n;
		for (int i = 0; i < n; i++) {
			ants[i].index_ = i;
			ants[i].turning_ = false;
			cin >> ants[i].loc_ >> ants[i].dir_;
		}
		sort(ants, ants + n, compare_location);
		for (int i = 0; i < n; i++) {
			input_orders[ants[i].index_] = i;
			if (ants[i].dir_ == 'R')
				ants[i].loc_ += T;
			else
				ants[i].loc_ -= T;
		}
		sort(ants, ants + n, compare_location);
		for (int i = 0; i < n - 1; i++) {
			if (ants[i].loc_ < 0 || ants[i].loc_ > L)
				continue;
			if (ants[i].loc_ == ants[i + 1].loc_)
				ants[i].turning_ = ants[i + 1].turning_ = true;
		}
		cout << "Case #" << cn << ":\n";
		for (int i = 0; i < n; i++) {
			int j = input_orders[i];
			if (ants[j].loc_ < 0 || ants[j].loc_ > L)
				cout << "Fell off\n";
			else {
				cout << ants[j].loc_;
				if (ants[j].turning_)
					cout << " Turning\n";
				else
					cout << ' ' << ants[j].dir_ << endl;
			}
		}
		cout << endl;
	}
	return 0;
}

