
/*
	UVa 12694 - Meeting Room Arrangement

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_12694_Meeting_Room_Arrangement.cpp
*/

/*
	A straight-forward interval scheduling problem.
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int nr_events_max = 20;

struct event {
	int s_, f_;

	bool operator<(const event& e) const {return f_ < e.f_;}
} events[nr_events_max];

int main()
{
	int n;
	scanf("%d", &n);
	while (n--) {
		int nr_events = 0;
		for ( ; ; nr_events++) {
			scanf("%d %d", &events[nr_events].s_, &events[nr_events].f_);
			if (!events[nr_events].s_ && !events[nr_events].f_)
				break;
		}
		int max_nr_events = 0;
		if (nr_events) {
			sort(events, events + nr_events); // sort the events in ascending order of their finish times
			max_nr_events = 1;
			int f = events[0].f_;
			for (int i = 1; i < nr_events; i++)
				if (events[i].s_ >= f) {
					max_nr_events++;
					f = events[i].f_;
				}
		}
		printf("%d\n", max_nr_events);
	}
	return 0;
}

