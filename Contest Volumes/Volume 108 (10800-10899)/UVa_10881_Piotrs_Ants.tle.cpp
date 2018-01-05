
/*
	UVa 10881 - Piotr's Ants

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10881_Piotrs_Ants.cpp
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

bool compare_location(const ant& i, const ant& j)
{
	return i.loc_ < j.loc_;
}

bool compare_index(const ant& i, const ant& j)
{
	return i.index_ < j.index_;
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
		while (T--) {
			for (int i = 0; i < n; i++) {
				if (ants[i].loc_ < 0 || ants[i].loc_ > L)
					continue;
				if (ants[i].turning_) {
					ants[i].turning_ = false;
					ants[i].dir_ = (ants[i].dir_ == 'L') ? 'R' : 'L';
				}
				if (ants[i].dir_ == 'L')
					ants[i].loc_--;
				else
					ants[i].loc_++;
			}
			for (int i = 0; i < n - 1; i++) {
				if (ants[i].loc_ < 0 || ants[i].loc_ > L || ants[i + 1].loc_ < 0 || ants[i + 1].loc_ > L)
					continue;
				if (ants[i].loc_ == ants[i + 1].loc_)
					ants[i].turning_ = ants[i + 1].turning_ = true;
				else if (ants[i].loc_ > ants[i + 1].loc_) {
					swap(ants[i].loc_, ants[i + 1].loc_);
					swap(ants[i].dir_, ants[i + 1].dir_);
				}
			}
		}
		sort(ants, ants + n, compare_index);
		cout << "Case #" << cn << ":\n";
		for (int i = 0; i < n; i++) {
			if (ants[i].loc_ < 0 || ants[i].loc_ > L)
				cout << "Fell off\n";
			else {
				cout << ants[i].loc_;
				if (ants[i].turning_)
					cout << " Turning\n";
				else
					cout << ' ' << ants[i].dir_ << endl;
			}
		}
		cout << endl;
	}
	return 0;
}

