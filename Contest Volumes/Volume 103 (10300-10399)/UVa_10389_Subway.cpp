
/*
	UVa 10389 - Subway

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10389_Subway.cpp
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <set>
#include <limits>
#include <cmath>
#include <cstdlib>
using namespace std;

struct point {
	int x_, y_;
	int sl_; // subway line number
	int ss_; // subway station number
};

double euclidean_distance(const point& a, const point& b)
{
	double dx = a.x_ - b.x_, dy = a.y_ - b.y_;
	return sqrt(dx * dx + dy * dy);
}

struct edge {
	int v_;
	double w_;
	edge() {}
	edge(int v, double w) : v_(v), w_(w) {}
};

struct distance_comparator {
	vector<double>& distances_;
	distance_comparator(vector<double>& distances) : distances_(distances) {}
	bool operator() (const int i, const int j) const {
		if (distances_[i] != distances_[j])
			return distances_[i] < distances_[j];
		else
			return i < j;
	}
};

int main()
{
	string line;
	istringstream iss;
	getline(cin, line);
	iss.str(line);
	int nr_cases;
	iss >> nr_cases;
	iss.clear();
	getline(cin, line); // skip a blank line
	while (nr_cases--) {
		getline(cin, line);
		iss.str(line);
		vector<point> points;
		point s, e;
		s.sl_ = 0; e.sl_ = 1; s.ss_ = e.ss_ = -1;
		iss >> s.x_ >> s.y_ >> e.x_ >> e.y_;
		points.push_back(s);
		points.push_back(e);
		iss.clear();
		for (int sl = 2; getline(cin, line) && !line.empty(); sl++) {
			iss.str(line);
			point p;
			p.sl_ = sl;
			for (int ss = 0; ; ss++) {
				iss >> p.x_ >> p.y_;
				if (p.x_ == -1)
					break;
				p.ss_ = ss;
				points.push_back(p);
			}
			iss.clear();
		}
		const double walk = 10000.0 / 60.0, subway = 40000.0 / 60.0;
		int n = static_cast<int>(points.size());
		vector< vector<edge> > edges(n);
		for (int i = 0; i < n - 1; i++)
			for (int j = i + 1; j < n; j++) {
				double d;
				if (points[i].sl_ == points[j].sl_)  { // two points are on the same subway line
					if (abs(points[i].ss_ - points[j].ss_) == 1) { // station i and station j are adjacent
						d = euclidean_distance(points[i], points[j]) / subway;
						edges[i].push_back(edge(j, d));
						edges[j].push_back(edge(i, d));
					}
				}
//				else {
					d = euclidean_distance(points[i], points[j]) / walk;
					edges[i].push_back(edge(j, d));
					edges[j].push_back(edge(i, d));
//				}
			}

		// apply Dijkstra's shortest path
		vector<double> distances(n, numeric_limits<double>::max());
		vector<bool> visited(n, false);
		set<int, distance_comparator> pq(distances); // priority queue
		distances[0] = 0.0;
		pq.insert(0);
		while (!pq.empty()) {
			int u = *pq.begin();
			pq.erase(pq.begin());
			visited[u] = true;
			if (u == 1)
				break;
			const vector<edge>& es = edges[u];
			for (size_t i = 0, j = es.size(); i < j; i++) {
				const edge& e = es[i];
				if (!visited[e.v_] && distances[e.v_] > distances[u] + e.w_) {
					pq.erase(e.v_); // remove vt if it has already been in the queue
						// this must be done before updating distances[]
					distances[e.v_] = distances[u] + e.w_;
					pq.insert(e.v_);
				}
			}
		}
		cout << fixed << setprecision(0) << distances[1] << endl;
		if (nr_cases)
			cout << endl;
	}
	return 0;
}

