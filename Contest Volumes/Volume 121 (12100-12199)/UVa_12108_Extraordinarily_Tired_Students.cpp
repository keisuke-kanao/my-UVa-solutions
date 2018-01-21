
/*
	UVa 12108 - Extraordinarily Tired Students

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_12108_Extraordinarily_Tired_Students.cpp
*/

#include <algorithm>
#include <set>
#include <cstdio>
using namespace std;

const int n_max = 10;

struct student {
	int awaken_, sleeping_, initial_;
} students[n_max];

int main()
{
	for (int cn = 1; ; cn++) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		for (int i = 0; i < n; i++) {
			student& s = students[i];
			scanf("%d %d %d", &s.awaken_, &s.sleeping_, &s.initial_);
			s.sleeping_ += s.awaken_, s.initial_--;
		}
		long long status = 0;
			// i-th (i >= 0) student's status is stored between bit (i * 4) and bit (i * 4 + 3)
		for (int i = 0, j = 0; i < n; i++, j += 4)
			status |= static_cast<long long>(students[i].initial_) << j;
		int time = 1;
		set<long long> statuses;
		statuses.insert(status);
#ifdef DEBUG
		printf("%d: %010llx\n", time, status);
#endif
		while (true) {
			int nr_awaken_ = 0;
			for (int i = 0, j = 0; i < n; i++, j += 4) {
				const student& s = students[i];
				int k = static_cast<int>(status >> j & 0x0f) + 1;
				if (k <= s.awaken_)
					nr_awaken_++;
			}
			if (nr_awaken_ == n)
				break;
			long long ns = 0;
			for (int i = 0, j = 0; i < n; i++, j += 4) {
				const student& s = students[i];
				int k = static_cast<int>(status >> j & 0x0f);
				if (nr_awaken_ * 2 >= n && k == s.awaken_ - 1)
					k = 0;
				else if (++k >= s.sleeping_)
					k -= s.sleeping_;
				ns |= static_cast<long long>(k) << j;
			}
			time++, status = ns;
#ifdef DEBUG
			printf("%d: %010llx\n", time, status);
#endif
			pair<set<long long>::iterator, bool> r = statuses.insert(status);
			if (!r.second) {
				time = -1; break;
			}
		}
		printf("Case %d: %d\n", cn, time);
	}
	return 0;
}

