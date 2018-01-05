
/*
	UVa 10947 - Bear with me, again..

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10947_Bear_with_me_again.cpp
*/

#include <cstdio>
#include <cmath>

const int n_max = 100;

struct island {
	int x_, y_, r_;
} islands[n_max + 2];

bool matrix[n_max + 2][n_max + 2];

void floyd_warshall(int n)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (matrix[i][k] && matrix[k][j])
					matrix[i][j] = true;
}

int main()
{
	int k, m;
	while (scanf("%d %d", &k, &m) != EOF) {
		double d_max = static_cast<double>(k) * m;
		scanf("%d %d %d", &islands[0].x_, &islands[0].y_, &islands[0].r_); // current island
		scanf("%d %d %d", &islands[1].x_, &islands[1].y_, &islands[1].r_); // home island
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d %d %d", &islands[i + 2].x_, &islands[i + 2].y_, &islands[i + 2].r_);
		for (int i = 0; i < n + 2; i++) {
			matrix[i][i] = true;
			for (int j = i + 1; j < n + 2; j++) {
				double dx = islands[i].x_ - islands[j].x_, dy = islands[i].y_ - islands[j].y_;
				double d = dx * dx + dy * dy, dr = d_max + islands[i].r_ + islands[j].r_;
				matrix[i][j] = matrix[j][i] = d <= dr * dr; // sqrt(d) - islands[i].r_ - islands[j].r_ <= d_max
			}
		}
		floyd_warshall(n + 2);
		puts((matrix[0][1]) ? "Larry and Ryan will escape!" : "Larry and Ryan will be eaten to death.");
	}
	return 0;
}

