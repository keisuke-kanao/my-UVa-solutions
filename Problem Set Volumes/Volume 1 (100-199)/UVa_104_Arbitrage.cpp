
/*
	UVa 104 - Arbitrage

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_104_Arbitrage.cpp
*/

#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;

void all_pairs_shortest_path(int n, const vector< vector<double> >& weights,
	vector< vector< vector<double> > >& distances, vector <vector< vector<int> > >& nexts)
{
	for (int u = 0; u < n; u++)
		for (int v = 0; v < n; v++)
			distances[u][v][0] = weights[u][v];
	for (int k = 1; k < n; k++)
		for (int u = 0; u < n; u++)
			for (int v = 0; v < n; v++) {
				distances[u][v][k] = numeric_limits<float>::max();
				for (int x = 0; x < n; x++) {
					double through_x = distances[u][x][k - 1] + weights[x][v];
					if (through_x < distances[u][v][k]) {
						distances[u][v][k] = through_x; nexts[u][v][k] = x;
					}
				}
			}
}

void print_path(int u, int v, int k, const vector <vector< vector<int> > >& nexts)
{
	int x = nexts[u][v][k];
	if (k) {
		print_path(u, x, k - 1, nexts);
		cout << ' ' << v + 1;
	}
	else
		cout << u + 1 << ' ' << v + 1;
}

bool print_arbitrage(int n, const vector< vector< vector<double> > >& distances, const vector <vector< vector<int> > >& nexts)
{
	for (int k = 0; k < n; k++)
		for (int u = 0; u < n; u++) {
			double profit = 1.0 / exp(distances[u][u][k]);
			if (profit > 1.01) {
				print_path(u, u, k, nexts);
				cout << endl;
				return true;
			}
		}
	return false;
}

int main()
{
	int n;
	while (cin >> n) {
		vector< vector<double> > weights(n, vector<double>(n));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (i == j)
					weights[i][j] = 0.0; // log(1.0)
				else {
					double r;
					cin >> r;
					weights[i][j] = -log(r);
				}
		vector< vector< vector<double> > > distances(n, vector< vector<double> >(n, vector<double>(n)));
			// distance[u][v][k] is the shortest path from u to v that passes at most (k + 1) edges
		vector <vector< vector<int> > > nexts(n, vector< vector<int> >(n, vector<int>(n, -1)));
		all_pairs_shortest_path(n, weights, distances, nexts);
		if (!print_arbitrage(n, distances, nexts))
			cout << "no arbitrage sequence exists\n";
	}
	return 0;
}

