
/*
	UVa 10724 - Road Construction

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10724_Road_Construction.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
using namespace std;

const double infinite = numeric_limits<int>::max(), epsilon = numeric_limits<double>::epsilon();

struct point {
	double x_, y_;
};

double euclidean_distance(const point& a, const point& b)
{
	double dx = a.x_ - b.x_, dy = a.y_ - b.y_;
	return sqrt(dx * dx + dy * dy);
}

int main()
{
	while (true) {
		int N, M;
		cin >> N >> M;
		if (!N && !M)
			break;
		vector<point> points(N + 1);
		for (int i = 1; i <= N; i++)
			cin >> points[i].x_ >> points[i].y_;
		vector< vector<bool> > roads(N + 1, vector<bool>(N + 1, false));
		vector< vector<double> > matrix(N + 1, vector<double>(N + 1, infinite));
		for (int i = 1; i <= N; i++)
			matrix[i][i] = 0.0;
		while (M--) {
			int i, j;
			cin >> i >> j;
			roads[i][j] = roads[j][i] = true;
			matrix[i][j] = matrix[j][i] = euclidean_distance(points[i], points[j]);
		}

		// apply Floyd-Warshall all-pairs shortest path algorithm
		for (int k = 1; k <= N; k++)
			for (int i = 1; i <= N; i++)
				for (int j = 1; j <= N; j++)
					if (matrix[i][k] + matrix[k][j] < matrix[i][j])
						matrix[i][j] = matrix[i][k] + matrix[k][j];

		double max_cuv = 1.0;
		int max_u, max_v;
		for (int u = 1; u < N; u++)
			for (int v = u + 1; v <= N; v++) {
				if (roads[u][v])
					continue;
				double cuv = 0.0, duv = euclidean_distance(points[u], points[v]);
				for (int i = 1; i <= N; i++)
					for (int j = 1; j <= N; j++) {
						double d = matrix[i][j] - min(matrix[i][u] + matrix[v][j] + duv, matrix[i][v] + matrix[u][j] + duv);
						if (d > epsilon)
							cuv += d;
					}
				if (cuv - 1.0 > epsilon && cuv - max_cuv > epsilon) {
					max_cuv = cuv; max_u = u; max_v = v;
				}
			}
		if (max_cuv - 1.0 > epsilon)
			cout << max_u << ' ' << max_v << endl;
		else
			cout << "No road required\n";
	}
	return 0;
}

