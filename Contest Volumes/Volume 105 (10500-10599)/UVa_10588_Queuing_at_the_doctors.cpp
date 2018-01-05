
/*
	UVa 10588 - Queuing at the doctors

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10588_Queuing_at_the_doctors.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int n_max = 1000, m_max = 1000;

struct member { // ICORE member
	int t_; // arrival time
	int k_; // number of doctor's offices to visit
	int ki_; // next doctor's office to visit
	vector<int> offices_; // doctor's offices to visit
} members[n_max];

struct visitor_comparator {
	bool operator() (const int& i, const int& j) {
		const member& mi = members[i]; const member& mj = members[j];
		// in ascending order of arrival time or in ascending order of member's number
		if (mi.t_ > mj.t_)
			return true;
		else if (mi.t_ < mj.t_)
			return false;
		else
			return i > j;
	}
};

priority_queue<int, vector<int>, visitor_comparator> arrivals, leaves;
priority_queue<int, vector<int>, visitor_comparator> offices[m_max];
	// offices[i] is the queue at the i-th doctor's office, items of which are indices to members[i]

int main()
{
	int c;
	cin >> c;
	while (c--) {
		int n, m;
		cin >> n >> m;
		for (int i = 0; i < n; i++) {
			member& m = members[i];
			cin >> m.t_ >> m.k_;
			m.ki_ = 0;
			m.offices_.resize(m.k_);
			for (int j = 0; j < m.k_; j++) {
				cin >> m.offices_[j];
				m.offices_[j]--;
			}
			arrivals.push(i);
		}
		int t = 0;
		size_t remained = arrivals.size();
		while (true) {
			while (!arrivals.empty()) {
				int i = arrivals.top();
				member& m = members[i];
				if (m.t_ < t)
					break;
				arrivals.pop();
				if (m.ki_ < m.k_)
					offices[m.offices_[m.ki_++]].push(i);
				else
					leaves.push(i);
			}
			for (int i = 0; i < m; i++) {
				priority_queue<int, vector<int>, visitor_comparator>& office = offices[i];
				if (!office.empty()) {
					int j = office.top();
					member& m = members[j];
					if (m.t_ <= t) {
						office.pop();
						m.t_ = t + 1;
						if (m.ki_ < m.k_)
							offices[m.offices_[m.ki_++]].push(j);
						else
							leaves.push(j);
					}
				}
			}
			while (!leaves.empty()) {
				int i = leaves.top();
				member& m = members[i];
				if (m.t_ > t)
					break;
				leaves.pop();
				remained--;
			}
			if (!remained)
				break;
			t++;
		}
		cout << t << endl;
	}
	return 0;
}

