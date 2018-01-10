
/*
	UVa 140 - Bandwidth

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_140_Bandwidth.cpp
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

int main()
{
	const int nr_nodes_max = 'Z' - 'A' + 1;
	while (true) {
		string s;
		cin >> s;
		if (s == "#")
			break;
		bool node_existences[nr_nodes_max];
		memset(node_existences, 0, sizeof(node_existences));
		bool matrix[nr_nodes_max][nr_nodes_max]; // adjacent matrix
		memset(matrix, 0, sizeof(matrix));
		for (const char* p = s.c_str(); *p; ) {
			int ni = *p++ - 'A';
			node_existences[ni] = true;
			for ( ; *p && *p != ';'; *p++) {
				int nj = *p - 'A';
				node_existences[nj] = true;
				matrix[ni][nj] = matrix[nj][ni] = true;
			}
			if (*p)
				p++;
		}
		int nr_nodes = 0;
		char nodes[nr_nodes_max + 1];
		for (int i = 0; i < nr_nodes_max; i++)
			if (node_existences[i])
				nodes[nr_nodes++] = i + 'A';
		nodes[nr_nodes] = '\0';
		int min_bandwidth = nr_nodes;
		char orderings[nr_nodes_max];
		memcpy(orderings, nodes, nr_nodes);
		do {
			int bandwidths[nr_nodes_max];
			memset(bandwidths, 0, sizeof(bandwidths));
			for (int i = 0; i < nr_nodes - 1; i++)
				for (int j = i + 1; j < nr_nodes; j++) {
					int ni = nodes[i] - 'A', nj = nodes[j] - 'A';
					if (matrix[ni][nj])
						bandwidths[i] = max(bandwidths[i], j - i);
				}
			int max_bandwidth = 0;
			for (int i = 0; i < nr_nodes; i++)
				max_bandwidth = max(max_bandwidth, bandwidths[i]);
			if (max_bandwidth < min_bandwidth) {
				min_bandwidth = max_bandwidth;
				memcpy(orderings, nodes, nr_nodes);
			}
		} while (next_permutation(nodes, nodes + nr_nodes));
		for (int i = 0; i < nr_nodes; i++)
			cout << orderings[i] << ' ';
		cout << "-> " << min_bandwidth << endl;
	}
	return 0;
}

