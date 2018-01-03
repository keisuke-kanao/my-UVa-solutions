/*
	UVa 534 - Frogger

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_534_Frogger.cpp
*/

#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cmath>
using namespace std;

const int n_max = 200;
pair<double, double> stones[n_max];
double matrix[n_max][n_max];

double euclidean_distance(const pair<double, double>& p, const pair<double, double>& q)
{
	double dx = p.first - q.first, dy = p.second - q.second;
	return sqrt(dx * dx + dy * dy);
}

void minimax_floyd_warshall(int n) // the minmax Floyd-Warshall algorithm
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix[i][j] = min(matrix[i][j], max(matrix[i][k], matrix[k][j]));
}

int main()
{
	for (int sn = 1; ; sn++) {
		int n;
		cin >> n;
		if (!n)
			break;
		for (int i = 0; i < n; i++) {
			cin >> stones[i].first >> stones[i].second;
		}
		for (int i = 0; i < n; i++)
			matrix[i][i] = 0 /* numeric_limits<double>::min() */;
		for (int i = 0; i < n - 1; i++)
			for (int j = i + 1; j < n; j++)
				matrix[i][j] = matrix[j][i] = euclidean_distance(stones[i], stones[j]);
		minimax_floyd_warshall(n);
		cout << "Scenario #" << sn << endl;
		cout << "Frog Distance = " << fixed << setprecision (3) << matrix[0][1] << endl << endl;
	}
	return 0;
}

