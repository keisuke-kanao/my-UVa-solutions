
/*
	UVa 822 - Queue and A

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_822_Queue_and_A.cpp
*/

#include <algorithm>
#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <cstdio>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int infinite = numeric_limits<int>::max();
const int nr_topics_max = 20, nr_personnel_max = 5;

struct person {
	int id_, nr_topics_;
	int t_last_start_, t_last_end_;
	int topics_[nr_topics_max];
} persons[nr_personnel_max];

struct person_comparator
{
	bool operator() (int i, int j) const
	{
		const person& pi = persons[i];
		const person& pj = persons[j];
		if (pi.t_last_start_ > pj.t_last_start_)
			return true;
		else if (pi.t_last_start_ < pj.t_last_start_)
			return false;
		else
			return i > j;
	}
};

struct topic {
	int nr_reqs_, t_first_req_, t_service_req_, t_between_reqs_;
	int t_arrived_;
	priority_queue<int, vector<int>, person_comparator> persons_; // candidate persons to handle a request

	topic() {}
	topic(int nr_reqs, int t_first_req, int t_service_req, int t_between_reqs) :
		nr_reqs_(nr_reqs), t_first_req_(t_first_req), t_service_req_(t_service_req), t_between_reqs_(t_between_reqs),
		t_arrived_(t_first_req_) {}
};

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	for (int scn = 1; ; scn++) {
		int nr_topics;
		scanf("%d", &nr_topics);
		if (!nr_topics)
			break;
		map<int, topic> topics;
		while (nr_topics--) {
			int id, nr_reqs, t_first_req, t_service_req, t_between_reqs;
			scanf("%d %d %d %d %d", &id, &nr_reqs, &t_first_req, &t_service_req, &t_between_reqs);
			topics[id] = topic(nr_reqs, t_first_req, t_service_req, t_between_reqs);
		}
		int nr_personnel;
		scanf("%d", &nr_personnel);
		for (int i = 0; i < nr_personnel; i++) {
			person& p = persons[i];
			p.t_last_start_ = p.t_last_end_ = 0;
			scanf("%d %d", &p.id_, &p.nr_topics_);
			for (int j = 0; j < p.nr_topics_; j++)
				scanf("%d", &p.topics_[j]);
		}
		for (int t = 0; ; t++) {
			int t_arrived = infinite;
			for (map<int, topic>::const_iterator i = topics.begin(); i != topics.end(); ++i)
				if (i->second.nr_reqs_)
					t_arrived = min(t_arrived, i->second.t_arrived_);
			if (t_arrived == infinite) // no more requests
				break;
			if (t < t_arrived)
				t = t_arrived;
#ifdef DEBUG
			printf("%d: arrived: %d\n", t, t_arrived);
#endif
			for (int i = 0; i < nr_personnel; i++) {
				person& p = persons[i];
				if (p.t_last_end_ <= t) {
					for (int j = 0; j < p.nr_topics_; j++) // add a person to the topic queue that the person can handle
						if (topics[p.topics_[j]].nr_reqs_ && topics[p.topics_[j]].t_arrived_ <= t)
							topics[p.topics_[j]].persons_.push(i);
				}
			}
			for (map<int, topic>::iterator i = topics.begin(); i != topics.end(); ++i) {
				topic& tp = i->second;
				if (tp.nr_reqs_ && tp.t_arrived_ <= t) {
					priority_queue<int, vector<int>, person_comparator>& pq = tp.persons_;
					while (!pq.empty()) {
						int j = pq.top();
						pq.pop();
						if (persons[j].t_last_end_ <= t) {
							persons[j].t_last_start_ = t, persons[j].t_last_end_ = t + tp.t_service_req_;
#ifdef DEBUG
							printf("  topic %d is dispatched to person %d, start: %d, end: %d\n",
								i->first, persons[j].id_, persons[j].t_last_start_, persons[j].t_last_end_);
#endif
							if (--(tp.nr_reqs_))
								tp.t_arrived_ += tp.t_between_reqs_;
							break;
						}
					}
					while (!pq.empty())
						pq.pop();
				}
			}
		}
		int m = 0;
		for (int i = 0; i < nr_personnel; i++)
			m = max(m, persons[i].t_last_end_);
		printf("Scenario %d: All requests are serviced within %d minutes.\n", scn, m);
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

