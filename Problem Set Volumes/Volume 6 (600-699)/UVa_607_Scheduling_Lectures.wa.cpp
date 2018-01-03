
/*
	UVa 607 - Scheduling Lectures

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_607_Scheduling_Lectures.cpp

	A Wrong answer.
*/

#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

struct schedule {
	int lecs_; // number of completed lectures
	int di_; // sum of dissatisfaction index

	schedule() {}
	schedule(int nr_lectures, int sum_of_DI) : lecs_(nr_lectures), di_(sum_of_DI) {}

	bool is_valid() const {return lecs_ != numeric_limits<int>::max();}
	bool operator<(const schedule& s) const {
		return (lecs_ != s.lecs_) ? lecs_ < s.lecs_ : di_ < s.di_;
	}
};

const int n_max = 1000, L_max = 500;
schedule schds[n_max + 1][L_max];

struct dissatisfaction_index {
	int L_, C_;

	dissatisfaction_index(int L, int C) : L_(L), C_(C) {}
	int get(int t) const;
};

int dissatisfaction_index::get(int t) const
{
	t = L_ - t;
	if (!t)
		return 0;
	else if (t <= 10)
		return -C_;
	else
		return (t - 10) * (t - 10);
}

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int n;
		cin >> n;
		if (!n)
			break;
		if (case_nr > 1)
			cout << endl;
		int L, C;
		cin >> L >> C;
		dissatisfaction_index dsi(L, C);
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= L; j++)
				schds[i][j].lecs_ = schds[i][j].di_ = numeric_limits<int>::max();
		int t;
		cin >> t;
		schds[1][t] = schedule(0, 0);
		for (int i = 2; i <= n; i++) {
			cin >> t;
			for (int l = 0; l <= L - t; l++) {
				const schedule& s = schds[i - 1][l];
				if (s.is_valid()) {
					schds[i][t] = min(schds[i][t], schedule(s.lecs_ + 1, s.di_ + dsi.get(l)));
						// partition the current lecture by the previous topic
					if (t + l < L)
						schds[i][t + l] = min(schds[i][t + l], schedule(s.lecs_, s.di_));
							// add the current topic to the current lecture
					else
						schds[i][0] = min(schds[i][0], schedule(s.lecs_ + 1, s.di_));
							// add the current topic to the current lecture and partition the current lecture
				}
			}
			for (int l = L - t + 1; l < L; l++) {
				const schedule& s = schds[i - 1][l];
				if (s.is_valid()) {
					if (t < L)
						schds[i][t] = min(schds[i][t], schedule(s.lecs_ + 1, s.di_ + dsi.get(l)));
						// partition the current lecture by the previous topic
					else
						schds[i][0] = min(schds[i][0], schedule(s.lecs_ + 2, s.di_ + dsi.get(l)));
						// partition the two lectures by the previous topic and the current topic
				}
			}
#ifdef DEBUG
			for (int l = 0; l < L; l++)
				if (schds[i][l].is_valid())
					cout << "schds[" << i << "][" << l  << "] " << schds[i][l].lecs_ << ' '  << schds[i][l].di_ << endl;
#endif
		}
		int min_lecs = numeric_limits<int>::max(), min_di = numeric_limits<int>::max();
		for (int l = 0; l < L; l++)
			if (schds[n][l].is_valid()) {
				int lecs = schds[n][l].lecs_, di = schds[n][l].di_;
				if (l) {
					lecs++; di += dsi.get(l);
				}
				if (lecs < min_lecs || lecs == min_lecs && di < min_di) {
					min_lecs = lecs; min_di = di;
				}
			}
		cout << "Case " << case_nr << ":\n";
		cout << "Minimum number of lectures: " << min_lecs << endl;
		cout << "Total dissatisfaction index: " << min_di << endl;
	}
	return 0;
}

/*
int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int n;
		cin >> n;
		if (!n)
			break;
		if (case_nr > 1)
			cout << endl;
		int L, C;
		cin >> L >> C;
		dissatisfaction_index di(L, C);
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= L; j++)
				schds[i][j].lecs_ = schds[i][j].di_ = numeric_limits<int>::max();
		int t;
		cin >> t;
		schds[1][t] = schedule(0, 0);
		for (int i = 2; i <= n; i++) {
			cin >> t;
			for (int l = 0; l < L - t; l++) {
				const schedule& s = schds[i - 1][l];
				if (s.is_valid()) 
					schds[i][t] = min(schds[i][t], schedule(s.lecs_ + 1, s.di_ + di.get(l)));
						// partition the current lecture by the previous topic
					schds[i][t + l] = min(schds[i][t + l], schedule(s.lecs_, s.di_));
						// add the current topic to the current lecture
				}
			}
			const schedule& s = schds[i - 1][L - t];
			if (s.is_valid()) {
				schds[i][L - t] = min(schds[i][L - t], schedule(s.lecs_ + 1, s.di_ + di.get(L - t)));
				// partition the current lecture by the previous topic

				schds[i][0] = min(schds[i][0], schedule(s.lecs_ + 1, s.di_));
					// add the current topic to the current lecture and partition the current lecture
			}
			for (int l = L - t + 1; l < L; l++) {
				const schedule& s = schds[i - 1][l];
				if (s.is_valid()) {
					if (t < L)
						schds[i][t] = min(schds[i][t], schedule(s.lecs_ + 1, s.di_ + di.get(l)));
						// partition the current lecture by the previous topic
					else
						schds[i][0] = min(schds[i][0], schedule(s.lecs_ + 2, s.di_ + di.get(l)));
						// partition the two lectures by the previous topic and the current topic
				}
			}
#ifdef DEBUG
			for (int l = 0; l < L; l++)
				if (schds[i][l].is_valid())
					cout << "schds[" << i << "][" << l  << "] " << schds[i][l].lecs_ << ' '  << schds[i][l].di_ << endl;
#endif
		}
		int min_t = -1;
		schedule min_schedule(numeric_limits<int>::max(), numeric_limits<int>::max());
		for (int l = 0; l < L; l++)
			if (schds[n][l] < min_schedule) {
				min_t = l; min_schedule = schds[n][l];
			}
		cout << "Case " << case_nr << ":\n";
		cout << "Minimum number of lectures: " << min_schedule.lecs_ << endl;
		cout << "Total dissatisfaction index: " <<
			((min_t) ? min_schedule.di_ + di.get(min_t) : min_schedule.di_) << endl;
	}
	return 0;
}
*/

