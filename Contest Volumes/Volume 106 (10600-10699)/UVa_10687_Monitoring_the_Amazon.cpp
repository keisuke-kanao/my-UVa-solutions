
/*
	UVa 10687 - Monitoring the Amazon

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10687_Monitoring_the_Amazon.cpp
*/

#include <queue>
#include <algorithm>
#include <cstdio>
#ifndef ONLINE_JUDGE
#include <cassert>
#endif
using namespace std;

const int N_max = 1000;

struct station {
	int i_;
	int x_, y_;

	station() {}
	station(const station& s) : i_(s.i_), x_(s.x_), y_(s.y_) {}
} stations[N_max];

bool visited[N_max];

struct station_comparator {
	const station& s_;

	station_comparator(const station& s) : s_(s) {}
	bool operator() (const station& si, const station& sj) const {
		if (si.i_ == s_.i_)
			return true;
		else if (sj.i_ == s_.i_)
			return false;
		else {
			int di = (si.x_ - s_.x_) * (si.x_ - s_.x_) + (si.y_ - s_.y_) * (si.y_ - s_.y_),
				dj = (sj.x_ - s_.x_) * (sj.x_ - s_.x_) + (sj.y_ - s_.y_) * (sj.y_ - s_.y_);
			if (di != dj)
				return di < dj;
			else if (si.x_ != sj.x_)
				return si.x_ < sj.x_;
			else
				return si.y_ < sj.y_;
		}
	}
};

void bsf(int N)
{
	queue<station> q;
	visited[0] = true;
	q.push(stations[0]);
	while (!q.empty()) {
		station s = q.front(); q.pop();
		sort(stations, stations + N, station_comparator(s));
#ifndef ONLINE_JUDGE
		assert(s.i_ == stations[0].i_);
#endif
		if (N > 1 && !visited[stations[1].i_]) {
			visited[stations[1].i_] = true;
			q.push(stations[1]);
		}
		if (N > 2 && !visited[stations[2].i_]) {
			visited[stations[2].i_] = true;
			q.push(stations[2]);
		}
	}
}

int main()
{
	while (true) {
		int N;
		scanf("%d", &N);
		if (!N)
			break;
		for (int i = 0; i < N; i++) {
			stations[i].i_ = i;
			scanf("%d %d", &stations[i].x_, &stations[i].y_);
			visited[i] = false;
		}
		bsf(N);
		bool reachable = true;
		for (int i = 0; i < N; i++)
			if (!visited[i]) {
				reachable = false;
				break;
			}
		puts((reachable) ? "All stations are reachable." : "There are stations that are unreachable.");
	}
	return 0;
}

