
/*
	UVa 208 - Firetruck

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_208_Firetruck.cpp

	form ACM ICPC World Finals - 1991 Problem A
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void bfs(int start, const vector< vector<int> >& adjacency_list, vector<bool>& reachables)
{
	queue<int> q;
	reachables[start] = true;
	q.push(start);
	while (!q.empty()) {
		int i = q.front(); q.pop();
		const vector<int>& al = adjacency_list[i];
		for(size_t j = 0, e = al.size(); j < e; j++) {
			int k = al[j];
			if (!reachables[k]) {
				reachables[k] = true;
				q.push(k);
			}
		}
	}
}


void firetruck(int ci, int fire, const vector< vector<int> >& adjacency_list, const vector<bool>& reachables, 
	vector<bool>& visited, int nr_corners, vector<int>& corners, int& nr_routes)
{
	if (ci == fire) {
		nr_routes++;
		for (int i = 0; i < nr_corners; i++)
			cout << corners[i] + 1 <<  ' ';
		cout << fire + 1 << endl;
	}
	else {
		const vector<int>& al = adjacency_list[ci];
		for (size_t i = 0, e = al.size(); i < e; i++) {
			int j = al[i];
			if (reachables[j] && !visited[j]) {
				visited[j] = true;
				corners[nr_corners] = ci;
				firetruck(j, fire, adjacency_list, reachables, visited, nr_corners + 1, corners, nr_routes);
				visited[j] = false;
			}
		}
	}
}

int main()
{
	const int nr_corners_max = 24;
	int nr_case = 1;
	int fire;
	while (cin >> fire) {
		fire--;
		vector< vector<int> > adjacency_list(nr_corners_max, vector<int>()); // adjacency list
		while (true) {
			int i, j;
			cin >> i >> j;
			if (!i && !j)
				break;
			i--; j--;
			adjacency_list[i].push_back(j);
			adjacency_list[j].push_back(i);
		}
		for (int i = 0; i < nr_corners_max; i++)
			sort(adjacency_list[i].begin(), adjacency_list[i].end());
		vector<bool> reachables(nr_corners_max, false);
			// reachables[i] is true if the fire is reachable from i-th corner
		bfs(fire, adjacency_list, reachables);
		cout << "CASE " << nr_case++ << ":\n";
		vector<bool> visited(nr_corners_max, false);
		visited[0] = true;
		vector<int> corners(nr_corners_max);
		int nr_routes = 0;
		firetruck(0, fire, adjacency_list, reachables, visited, 0, corners, nr_routes);
		cout << "There are " << nr_routes << " routes from the firestation to streetcorner " << fire + 1 << ".\n";
	}
	return 0;
}

