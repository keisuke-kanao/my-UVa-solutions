
/*
	UVa 10610 - Gopher and Hawks

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10610_Gopher_and_Hawks.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <utility>
#include <cmath>
using namespace std;

const int n_max = 1024; // when I defined n_max = 1000, I got a verdict of Runtime error.

pair<double, double> holes[n_max];
vector<int> edges[n_max];
bool visited[n_max];

double euclidean_distance(const pair<double, double>& p, const pair<double, double>& q)
{
	double dx = p.first - q.first, dy = p.second - q.second;
	return sqrt(dx * dx + dy * dy);
}

int bfs(int n, int s, int t, const vector<int> edges[])
{
	queue< pair<int, int> > q;
	visited[s] = true;
	q.push(make_pair(s, 0));
	while (!q.empty()) {
		pair<int, int> u = q.front();
		q.pop();
		if (u.first == t)
			return u.second - 1;
		const vector<int>& e = edges[u.first];
		for (size_t i = 0, j = e.size(); i < j; i++) {
			int k = e[i];
			if (!visited[k]) {
				visited[k] = true;
				q.push(make_pair(k, u.second + 1));
			}
		}
	}
	return -1;
}

int main()
{
	string line;
	istringstream iss;
	while (true) {
		getline(cin, line);
		iss.str(line);
		int v, m;
		iss >> v >> m;
		iss.clear();
		if (!v && !m)
			break;
		double d = 60.0 * v * m;
		int n = 0;
		while (true) {
			getline(cin, line);
			if (line.empty())
				break;
			iss.str(line);
			iss >> holes[n].first >> holes[n].second;
			iss.clear();
			n++;
		}
		for (int i = 0; i < n; i++) {
			edges[i].clear();
			visited[i] = false;
		}
		for (int i = 0; i < n - 1; i++)
			for (int j = i + 1; j < n; j++)
				if (euclidean_distance(holes[i], holes[j]) <= d) {
					edges[i].push_back(j);
					edges[j].push_back(i);
				}
		int nr_holes = bfs(n, 0, 1, edges);
		if (nr_holes != -1)
			cout << "Yes, visiting " << nr_holes << " other holes.\n";
		else
			cout << "No.\n";
	}
	return 0;
}

