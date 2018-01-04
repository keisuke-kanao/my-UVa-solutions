
/*
	UVa 12205 - Happy Telephones

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12205_Happy_Telephones.cpp
*/

#include <algorithm>
#include <map>
#include <cstdio>
using namespace std;

/*
First, applied the line sweep algorithm to calucalte the number of connections at each start/stop time of the telephone calls.
For a given interval, found the number of calls at the start time of the interval 
and then iterated over the telephone call times till the end time of the interval and added the phone calls that started during the interval.
*/

const int N_max = 10000, M_max = 100;

struct event {
	int s_; // 0 for start, 1 for stop
	int t_; // time

	event() {}
	event(int s, int t) : s_(s), t_(t) {}
	bool operator<(const event& e) const {
		if (t_ != e.t_)
			return t_ < e.t_;
		else
			return s_ > e.s_;
	}
} events[N_max * 2];

int main()
{
	while (true) {
		int N, M;
		scanf("%d %d", &N, &M);
		if (!N)
			break;
		int n = 0;
		while (N--) {
			int s, d;
			scanf("%*d %*d %d %d", &s, &d);
			events[n].s_ = 0, events[n].t_ = s;
			n++;
			events[n].s_ = 1, events[n].t_ = s + d;
			n++;
		}
		sort(events, events + n);
#ifdef DEBUG
		for (int i = 0; i < n; i++)
			printf("%d:%d%c", events[i].t_, events[i].s_, ((i < n - 1) ? ' ' : '\n'));
#endif
		int nr = 0;
		map<int, int> nr_calls; // key is the time, value is the number of calls from the time
		for (int i = 0; i < n; i++) {
			if (!events[i].s_)
				nr++;
			else
				nr--;
			nr_calls[events[i].t_] = nr;
		}
#ifdef DEBUG
		for (map<int, int>::const_iterator i = nr_calls.begin(); i != nr_calls.end(); ++i)
			printf("%d:%d ", i->first, i->second);
		putchar('\n');
#endif
		while (M--) {
			int s, d;
			scanf("%d %d", &s, &d);
			nr = 0;
			map<int, int>::const_iterator i = nr_calls.upper_bound(s);
			if (i != nr_calls.end()) {
#ifdef DEBUG
				printf("%d:%d\n", i->first, i->second);
#endif
				if (i != nr_calls.begin())
					nr = (--i)->second;
				int j = upper_bound(events, events + n, event(0, s)) - events;
#ifdef DEBUG
				if (j < n)
					printf("%d:%d\n", events[j].t_, events[j].s_);
#endif
				for ( ; j < n && events[j].t_ < s + d; j++)
					if (!events[j].s_)
						nr++;
			}
			printf("%d\n", nr);
		}
	}
	return 0;
}

