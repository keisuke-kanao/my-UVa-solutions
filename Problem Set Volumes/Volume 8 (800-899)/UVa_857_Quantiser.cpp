
/*
	UVa 857 - Quantiser

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_857_Quantiser.cpp
*/

#include <set>
#include <algorithm>
#include <cstdio>
using namespace std;

const int n_max = 2000;

struct timestamp {
	int i_, note_, m_, b_, t_;

	timestamp() {}
	timestamp(int i, int note, int m, int b, int t) : i_(i), note_(note), m_(m), b_(b), t_(t) {}

	bool operator<(const timestamp& t) const {
		if (m_ != t.m_)
			return m_ < t.m_;
		else if (b_ != t.b_)
			return b_ < t.b_;
		else if (t_ != t.t_)
			return t_ < t.t_;
		else
			return note_ < t.note_;
	}
};

struct message {
	int code_, note_, m_, b_, t_;
	bool filtered_;

	bool operator<(const message& m) const {
		if (m_ != m.m_)
			return m_ < m.m_;
		else if (b_ != m.b_)
			return b_ < m.b_;
		else
			return t_ < m.t_;
	}
} messages[n_max];

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (n == -1) {
			printf("%d\n", n);
			break;
		}
		int nr_messages = 0;
		multiset<timestamp> timestamps;
		for (int i = 0; i < n; i++) {
			message& m = messages[nr_messages];
			m.filtered_ = false;
			scanf("%d %d %d %d %d", &m.code_, &m.note_, &m.m_, &m.b_, &m.t_);
			int j = m.t_ / 60, k = m.t_ % 60;
			if (k >= 30)
				j++;
			if ((m.t_ = 60 * j) == 480) {
				m.t_ = 0;
				if ((m.b_ += 1) == 5) {
					m.b_ = 1;
					m.m_++;
				}
			}
#ifdef DEBUG
			printf("    %d %d %d %d %d\n", m.code_, m.note_, m.m_, m.b_, m.t_);
#endif
			timestamp ts(nr_messages, m.note_, m.m_, m.b_, m.t_);
			if (m.code_) {
				timestamps.insert(ts);
				nr_messages++;
			}
			else {
				pair<multiset<timestamp>::iterator, multiset<timestamp>::iterator> result = timestamps.equal_range(ts);
				if (result.first == result.second)
					nr_messages++;
				else {
					for (multiset<timestamp>::iterator ti = result.first; ti != result.second; ++ti)
						messages[ti->i_].filtered_ = true;
				}
			}
		}
		stable_sort(messages, messages + nr_messages);
		int nr_filtered = 0;
		for (int i = 0; i < nr_messages; i++)
			if (messages[i].filtered_)
				nr_filtered++;
		printf("%d\n", nr_messages - nr_filtered);
		for (int i = 0; i < nr_messages; i++) {
			const message& m = messages[i];
			if (!m.filtered_)
				printf("%d %d %d %d %d\n", m.code_, m.note_, m.m_, m.b_, m.t_);
		}
	}
	return 0;
}

