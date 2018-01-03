
/*
	UVa 703 - Triple Ties: The Organizer's Nightmare

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_703_Triple_Ties.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int n_max = 100;
int tournaments[n_max + 1][n_max + 1];

struct triple_tie {
	int i_, j_, k_;

	triple_tie(int i, int j, int k) : i_(i), j_(j), k_(k) {}
	bool operator<(const triple_tie& tt) const {
		if (i_ != tt.i_)
			return i_ < tt.i_;
		else if (j_ != tt.j_)
			return j_ < tt.j_;
		else
			return k_ < tt.k_;
	}
};

int get_result(int i, int j)
{
	if (tournaments[i][j] /* > tournaments[j][i] */)
		return 1; // i beats j
	else if (/* tournaments[i][j] < */ tournaments[j][i])
		return -1; // j beats i
	else
		return 0; // draw

}

int main()
{
	int n;
	while (cin >> n) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				cin >> tournaments[i][j];

		vector<triple_tie> triple_ties;
		for (int i = 1; i <= n - 2; i++)
			for (int j = i + 1; j <= n - 1; j++)
				for (int k = j + 1; k <= n; k++) {
					int rij = get_result(i, j), rjk = get_result(j, k), rki = get_result(k, i);
					if (rij == 0 && rjk == 0 && rki == 0 || // draws
						rij == 1 && rjk == 1 && rki == 1) // i beats j, j beats k, k beats i
						triple_ties.push_back(triple_tie(i, j, k));
					else if (get_result(k, j) == 1 && get_result(j, i) == 1 && get_result(i, k) == 1) // k beats j, j beats i, i beats k
						triple_ties.push_back(triple_tie(k, j, i));
				}
		sort(triple_ties.begin(), triple_ties.end());
		cout << triple_ties.size() << endl;
		for (vector<triple_tie>::const_iterator ti = triple_ties.begin(), te = triple_ties.end(); ti != te; ++ti)
			cout << ti->i_ << ' ' << ti->j_ << ' ' << ti->k_ << endl;
	}
	return 0;
}

