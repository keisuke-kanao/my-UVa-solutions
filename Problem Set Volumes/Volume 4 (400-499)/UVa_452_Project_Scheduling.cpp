
/*
	UVa 452 - Project Scheduling

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_452_Project_Scheduling.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

const int nr_vertices = 26;
int nr_days[nr_vertices], nr_accumulated_days[nr_vertices], in_degrees[nr_vertices];
bool adjacency_matrix[nr_vertices][nr_vertices];

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
		memset(adjacency_matrix, 0, sizeof(adjacency_matrix));
		memset(nr_days, 0, sizeof(nr_days));
		while (getline(cin, line) && !line.empty()) {
			iss.str(line);
			char c;
			int d;
			iss >> c >> d;
			int u = c - 'A';
			nr_days[u] = d;
			while (iss >> c)
				adjacency_matrix[c - 'A'][u] = true;
			iss.clear();
		}
		memset(in_degrees, 0, sizeof(in_degrees));
		for (int u = 0; u < nr_vertices; u++)
			for (int v = 0; v < nr_vertices; v++)
				if (adjacency_matrix[u][v])
					in_degrees[v]++;
		memset(nr_accumulated_days, 0, sizeof(nr_accumulated_days));
		queue<int> q;
		for (int u = 0; u < nr_vertices; u++)
			if (nr_days[u] && !in_degrees[u]) {
				nr_accumulated_days[u] = nr_days[u];
				q.push(u);
			}
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int v = 0; v < nr_vertices; v++)
				if (adjacency_matrix[u][v]) {
					nr_accumulated_days[v] = max(nr_accumulated_days[v], nr_accumulated_days[u] + nr_days[v]);
#ifdef DEBUG
					cout << static_cast<char>(v + 'A') << ": " << nr_accumulated_days[v] << endl;
#endif
 					if (!--in_degrees[v])
						q.push(v);
				}
		}
		int max_nr_accumulated_days = 0;
		for (int u = 0; u < nr_vertices; u++)
			max_nr_accumulated_days = max(max_nr_accumulated_days, nr_accumulated_days[u]);
		cout << max_nr_accumulated_days  << endl;
		if (nr_cases)
			cout << endl;
	}
	return 0;
}

