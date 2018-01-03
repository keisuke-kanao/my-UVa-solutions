
/*
	UVa 924 - Spreading The News

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_924_Spreading_The_News.cpp
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

const int e_max = 2500;
vector< vector<int> > adjacency_list(e_max);
int days[e_max]; // days[i] is i-th boom's day
int booms[e_max]; // booms[i] is the number of booms at i-th day

int bfs(int v)
{
	int day_max = 0;
	queue< pair<int, int> > q;
	days[v] = day_max;
	q.push(make_pair(v, day_max));
	while (!q.empty()) {
		pair<int, int>& u = q.front();
		const vector<int>& l = adjacency_list[u.first];
		int d = u.second + 1;
		for (size_t i = 0, e = l.size(); i < e; i++) {
			v = l[i];
			if (days[v] == -1) {
				days[v] = d;
				q.push(make_pair(v, d));
				if (d > day_max)
					day_max = d;
			}
		}
		q.pop();
	}
	return day_max;
}

int main()
{
	int e;
	cin >> e;
	for (int i = 0; i < e; i++) {
		int n;
		cin >> n;
		while (n--) {
			int j;
			cin >> j;
			adjacency_list[i].push_back(j);
		}
	}
	int t;
	cin >> t;
	while (t--) {
		for (int i = 0; i < e; i++) {
			days[i] = -1;
			booms[i] = 0;
		}
		int i;
		cin >> i;
		int days_max = bfs(i);
		int m = 0, d;
		if (days_max) {
			for (int i = 0; i < e; i++)
				if (days[i] != -1)
					booms[days[i]]++;
			for (int i = 1; i <= days_max; i++)
				if (booms[i] > m) {
					m = booms[i]; d = i;
				}
		}
		cout << m;
		if (m)
			cout << ' ' << d;
		cout << endl;
	}
	return 0;
}

