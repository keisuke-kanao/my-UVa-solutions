
/*
	UVa 193 - Graph Coloring

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_193_Graph_Coloring.cpp

	from ACM Southwestern European Regional Contest - 1995
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_SWERC/1995/index.html)
*/

#include <iostream>
#include <vector>
using namespace std;

void graph_coloring(int n, int ni, const vector< vector<int> >& adjacency_list,
	int nr_black_nodes, vector<bool>& black_nodes, int& max_nr_black_nodes, vector<bool>& max_black_nodes)
{
	if (ni == n) {
		if (nr_black_nodes > max_nr_black_nodes) {
			max_nr_black_nodes = nr_black_nodes;
#ifdef DEBUG
			cout << max_nr_black_nodes << endl;
#endif
			for (int i = 0; i < n; i++)
				max_black_nodes[i] = black_nodes[i];
		}
	}
	else if (nr_black_nodes + n - ni <= max_nr_black_nodes)
		return;
	else {
		const vector<int>& al = adjacency_list[ni];
		if (al.empty()) {
			black_nodes[ni] = true; // color ni-th node black
			graph_coloring(n, ni + 1, adjacency_list, nr_black_nodes + 1, black_nodes, max_nr_black_nodes, max_black_nodes);
		}
		else {
			size_t i = 0, e = al.size();
			for ( ; i < e; i++)
				if (black_nodes[al[i]])
					break;
			if (i == e) { // all of the connected nodes are white
				black_nodes[ni] = true;
				graph_coloring(n, ni + 1, adjacency_list, nr_black_nodes + 1, black_nodes, max_nr_black_nodes, max_black_nodes);
				black_nodes[ni] = false;
			}
			// color ni-th node white
			graph_coloring(n, ni + 1, adjacency_list, nr_black_nodes, black_nodes, max_nr_black_nodes, max_black_nodes);
		}
	}
}

int main()
{
	int m;
	cin >> m;
	while (m--) {
		int n, k;
		cin >> n >> k;
		vector< vector<int> > adjacency_list(n, vector<int>()); // adjacency list
		for (int i = 0; i < k; i++) {
			int u, v;
			cin >> u >> v;
			u--; v--;
			adjacency_list[u].push_back(v);
			adjacency_list[v].push_back(u);
		}
		vector<bool> black_nodes(n, false); // black_nodes[i] is is true if i-th node is black
		vector<bool> max_black_nodes(n);
		int max_nr_black_nodes = 0;
		graph_coloring(n, 0, adjacency_list, 0, black_nodes, max_nr_black_nodes, max_black_nodes);
		cout << max_nr_black_nodes << endl;
		bool first = true;
		for (int i = 0; i < n; i++)
			if (max_black_nodes[i]) {
				if (first)
					first = false;
				else
					cout << ' ';
				cout << i + 1;
			}
		cout << endl;
	}
	return 0;
}

