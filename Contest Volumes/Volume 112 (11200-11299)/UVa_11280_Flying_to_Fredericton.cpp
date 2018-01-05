
/*
	UVa 11280 - Flying to Fredericton

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11280_Flying_to_Fredericton.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
using namespace std;

const int infinite = numeric_limits<int>::max();

struct edge {
	int v_; // destination vertex
	int weight_; // cost

	edge() : v_(-1), weight_(-1) {}
	edge(int v, int weight) : v_(v), weight_(weight) {}
};

int main()
{
	int nr_scenarios;
	cin >> nr_scenarios;
	for (int sn = 1; sn <= nr_scenarios; sn++) {
		int N;
		cin >> N;
		map<string, int> cities;
		for (int i = 0; i < N; i++) {
			string s;
			cin >> s;
			cities[s] = i;
		}
		vector< vector<edge> > edges(N);
		int M;
		cin >> M;
		while (M--) {
			string s, t;
			int w;
			cin >> s >> t >> w;
			edges[cities[s]].push_back(edge(cities[t], w));
		}
		vector< vector<int> > distances(N, vector<int>(N, infinite));
			// distances[i][j] is the distance to vertex j with the number of paths of i
		distances[0][0] = 0;
		for (int i = 1; i < N; i++) {
			for (int j = 0; j < N; j++) {
				int d = distances[i - 1][j];
				if (d < infinite)
					for (size_t k = 0; k < edges[j].size(); k++) {
						const edge& e = edges[j][k];
						distances[i][e.v_] = min(distances[i][e.v_], d + e.weight_);
					}
			}
		}
		vector<int> min_distances(N - 1, infinite);
			// min_distances[i] is the min. distance to the destination vertex with at most i stepovers
		int min_d = infinite;
		for (int i = 1; i < N; i++) {
			min_d = min(min_d, distances[i][N - 1]);
			min_distances[i - 1] = min_d;
#ifdef DEBUG
			cout << min_distances[i - 1] << ((i < N - 1) ? ' ' : '\n');
#endif
		}
		cout << "Scenario #" << sn << endl;
		int Q;
		cin >> Q;
		while (Q--) {
			int stopovers;
			cin >> stopovers;
			stopovers = min(stopovers, N - 2);
			if (min_distances[stopovers] < infinite)
				cout << "Total cost of flight(s) is $" << min_distances[stopovers] << endl;
			else
				cout << "No satisfactory flights\n";
		}
		if (sn < nr_scenarios)
			cout << endl;
	}
	return 0;
}

