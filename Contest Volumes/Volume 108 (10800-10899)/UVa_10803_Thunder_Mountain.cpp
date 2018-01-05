
/*
	UVa 10803 - Thunder Mountain

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10803_Thunder_Mountain.cpp
*/

#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cmath>
using namespace std;

const int n_max = 100;
double matrix[n_max][n_max];

struct point {
	int x, y;
} points[n_max];

double euclidean_distance(const point& a, const point& b)
{
	double dx = static_cast<double>(a.x - b.x), dy = static_cast<double>(a.y - b.y);
	return sqrt(dx * dx + dy * dy);
}

void floyd_warshall(int n)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
}

int main()
{
	int t;
	cin >> t;
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		int n;
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> points[i].x >> points[i].y;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				 matrix[i][j] = (i == j) ? 0.0 : numeric_limits<float>::max();
		for (int i = 0; i < n - 1; i++)
			for (int j = i + 1; j < n; j++) {
				double d = euclidean_distance(points[i], points[j]);
				if (d <= 10.0)
					matrix[i][j] = matrix[j][i] = d;
			}
		floyd_warshall(n);
		double max_d = 0.0;
		for (int i = 0; i < n - 1; i++)
			for (int j = i + 1; j < n; j++)
				max_d = max(max_d, matrix[i][j]);
		cout << "Case #" << case_nr << ":\n";
		if (max_d == numeric_limits<float>::max())
			cout << "Send Kurdy\n\n";
		else
			cout << fixed << setprecision(4) << max_d << endl << endl;
	}
	return 0;
}

