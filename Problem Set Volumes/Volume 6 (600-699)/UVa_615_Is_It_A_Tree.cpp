
/*
	UVa 615 - Is It A Tree?

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_615_Is_It_A_Tree.cpp

	from ACM  North Central Regionals 1997
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1997/index.html)
*/

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

int get_node_index(map<int, int>& nodes, int i)
{
	pair<map<int, int>::iterator, bool> result = nodes.insert(make_pair(i, nodes.size()));
	return result.first->second;
}

int get_root_node(const vector<int>& in_degrees)
{
	int root = -1;
	for (int i = 0, j = in_degrees.size(); i < j; i++) {
		if (!in_degrees[i]) {
			if (root == -1)
				root = i;
			else
				return -1;
		}
		else if (in_degrees[i] > 1)
			return -1;
	}
	return root;
}

int get_connected_nodes(int n, int s, const vector< vector<int> >& edges)
{
	vector<bool> visited(n);
	queue<int> q;
	int nr_visited = 1;
	q.push(s);
	while (!q.empty()) {
		const vector<int>& e = edges[q.front()];
		q.pop();
		for (size_t i = 0, j = e.size(); i < j; i++) {
			int k = e[i];
			if (!visited[k]) {
				visited[k] = true;
				nr_visited++;
				q.push(k);
			}
		}
	}
	return nr_visited;
}

int main()
{
	for (int nr_case = 1; ; nr_case++) {
		int i, j;
		cin >> i >> j;
		if (i < 0 && j < 0)
			break;
		map<int, int> nodes; // key is the number, value is indices to in_degrees and edges
		vector<int> in_degrees;
		vector< vector<int> > edges;
		while (i && j) {
			i = get_node_index(nodes, i);
			j = get_node_index(nodes, j);
			if (i >= in_degrees.size())
				in_degrees.push_back(0);
			if (j >= in_degrees.size())
				in_degrees.push_back(0);
			in_degrees[j]++;
			if (i >= edges.size())
				edges.push_back(vector<int>());
			edges[i].push_back(j);
			if (j >= edges.size())
				edges.push_back(vector<int>());
			cin >> i >> j;
		}
		bool is_tree = false;
		if (nodes.empty())
			is_tree = true;
		else {
			int root_node = get_root_node(in_degrees);
			if (root_node != -1) {
				int n = nodes.size();
				is_tree = n == get_connected_nodes(n, root_node, edges);
			}
		}
		if (is_tree)
			cout << "Case " << nr_case << " is a tree.\n";
		else
			cout << "Case " << nr_case << " is not a tree.\n";
	}
	return 0;
}

