
/*
	UVa 336 - A Node Too Far

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_336_A_Node_Too_Far_bfs.cpp

	from ACM North Central Regionals 1994
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1994/index.html)

	This is an accepted solution.
*/

#include <iostream>
#include <map>
#include <queue>
#include <limits>
#include <cstring>
using namespace std;

const int nr_nodes_max = 30;
bool matrix[nr_nodes_max][nr_nodes_max];
bool visited[nr_nodes_max];
int distances[nr_nodes_max];

int find_vertex(int node, map<int, int>& nodes)
{
	map<int, int>::iterator i = nodes.find(node);
	return (i != nodes.end()) ? i->second : -1;
}

int get_vertex(int node, map<int, int>& nodes)
{
	map<int, int>::iterator i = nodes.find(node);
	if (i != nodes.end())
		return i->second;
	else {
		int j = nodes.size();
		nodes.insert(make_pair(node, j));
		return j;
	}
}

int count_unreachable_vertices(int n, int v, int ttl)
{
	memset(visited, 0, sizeof(visited));
	for (int i = 0; i < n; i++)
		distances[i] = numeric_limits<int>::max();
	queue<int> q;
	visited[v] = true;
	distances[v] = 0;
	q.push(v);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (v = 0; v < n; v++)
			if (matrix[u][v] && !visited[v]) {
				visited[v] = true;
				distances[v] = distances[u] + 1;
				q.push(v);
			}
	}
	int nr_unreachable_vertices = 0;
	for (v = 0; v < n; v++)
		if (distances[v] > ttl)
			nr_unreachable_vertices++;
	return nr_unreachable_vertices;
}

int main()
{
	int case_nr = 1;
	while (true) {
		int nc;
		cin >> nc;
		if (!nc)
			break;
		map<int, int> nodes; // key is a node number, value is its vertex number
		memset(matrix, 0, sizeof(matrix));
		while (nc--) {
			int nu, nv;
			cin >> nu >> nv;
			int u = get_vertex(nu, nodes), v = get_vertex(nv, nodes);
			matrix[u][v] = matrix[v][u] = true;
		}
		int n = nodes.size();
		while (true) {
			int node, ttl;
			cin >> node >> ttl;
			if (!node && !ttl)
				break;
			int nr_unreachable_vertices = n;
			int u = find_vertex(node, nodes);
			if (u != -1)
				nr_unreachable_vertices = count_unreachable_vertices(n, u, ttl);
			cout << "Case " << case_nr << ": " << nr_unreachable_vertices <<
				" nodes not reachable from node " << node << " with TTL = " << ttl << ".\n";
			case_nr++;
		}
	}
	return 0;
}

