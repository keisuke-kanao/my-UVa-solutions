
/*
	UVa 1347 - Tour

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1347_Tour.cpp
*/

#include <algorithm>
#include <vector>
#include <utility>
#include <limits>
#include <cstdio>
#include <cmath>
using namespace std;

const double infinite = numeric_limits<double>::max();

int main()
{
	int n;
	while (scanf("%d", &n) != EOF) {
		vector< pair<double, double> > points(n);
		for (int i = 0; i < n; i++)
			scanf("%lf %lf", &points[i].first, &points[i].second);
		vector< vector<double> > distances(n, vector<double>(n));
		for (int i = 0; i < n - 1; i++) {
			distances[i][i] = 0.0;
			for (int j = i + 1; j < n; j++)
				distances[i][j] = distances[j][i] = hypot(points[i].first - points[j].first, points[i].second - points[j].second);
		}

		vector< vector<double> > bitonic_tsp(n, vector<double>(n));
		bitonic_tsp[0][0] = 0.0;
		bitonic_tsp[0][1] = distances[0][1];
		// fill the first row
		for (int j = 2; j < n; j++)
			bitonic_tsp[0][j] = bitonic_tsp[0][j - 1] + distances[j - 1][j];
		// fill the remaining rows
		for (int i = 1; i < n; i++) {
			for (int j = i; j < n; j++) {
				if (i == j || i == j - 1) {
					bitonic_tsp[i][j] = infinite;
					for (int k = 0; k < i; k++)
						bitonic_tsp[i][j] = min(bitonic_tsp[i][j], bitonic_tsp[k][i] + distances[k][j]);
				}
				else
					bitonic_tsp[i][j] = bitonic_tsp[i][j - 1] + distances[j - 1][j];
			}
		}
		printf("%.2lf\n", bitonic_tsp[n - 1][n - 1]);
	}
	return 0;
}

