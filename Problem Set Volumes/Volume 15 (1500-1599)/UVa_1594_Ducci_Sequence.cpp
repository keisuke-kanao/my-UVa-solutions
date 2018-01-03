
/*
	UVa 1594 - Ducci Sequence

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1594_Ducci_Sequence.cpp
*/

#include <set>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int n_max = 15, seq_max = 1024;

struct tuple_ {
	int integers_[n_max];
} tuples[seq_max];

struct tuple_comparator {
	int n_;
	tuple_comparator(int n) : n_(n) {}
	bool operator() (const tuple_* ti, const tuple_* tj) const {
		for (int i = 0; i < n_; i++)
			if (ti->integers_[i] != tj->integers_[i])
				return ti->integers_[i] < tj->integers_[i];
		return false;
	}
};

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		bool zero = true;
		for (int i = 0; i < n; i++) {
			scanf("%d", &tuples[0].integers_[i]);
			if (tuples[0].integers_[i])
				zero = false;
		}
		if (!zero) {
			set<tuple_*, tuple_comparator> st(n);
			st.insert(&tuples[0]);
			for (int i = 1; ; i++) {
				zero = true;
				for (int j = 0; j < n; j++)
					if (tuples[i].integers_[j] = abs(tuples[i - 1].integers_[j] - tuples[i - 1].integers_[(j + 1) % n]))
						zero = false;
				if (zero)
					break;
#ifdef DEBUG
				for (int j = 0; j < n; j++)
					printf("%d%c", tuples[i].integers_[j], ((j < n - 1) ? ' ' : '\n'));
#endif
				pair<set<tuple_*, tuple_comparator>::iterator, bool> result = st.insert(&tuples[i]);
				if (!result.second)
					break;
			}
		}
		puts((zero) ? "ZERO" : "LOOP");
	}
	return 0;
}

