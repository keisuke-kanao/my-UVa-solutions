
/*
	UVa 10296 Jogging Trails

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10296_Jogging_Trails.cpp

	from 1 June, 2002 - Waterloo local contest, Problem B

	This is a chinese postman problem (CPP), postman tour or route inspection problem.
*/

#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

const int n_max = 15;

int matrix[n_max][n_max], distances[1 << n_max];

void floyd_warshall(int n)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			if (matrix[i][k] != numeric_limits<int>::max())
				for (int j = 0; j < n; j++)
					if (matrix[k][j] != numeric_limits<int>::max() && matrix[i][k] + matrix[k][j] < matrix[i][j])
						matrix[i][j] = matrix[i][k] + matrix[k][j];
}

int matching(int n, int degrees)
{
	if (!degrees)
		return 0;
	if (distances[degrees] != -1)
		return distances[degrees];
	int i, j;
	for (i = 0; !(degrees & (1 << i)); i++)
		;
	int min_d = numeric_limits<int>::max();
	for (j = i + 1; j < n; j++)
		if (degrees & (1 << j)) {
			int k = matching(n, degrees - (1 << i) - (1 << j));
			if (matrix[i][j] + k < min_d)
				min_d = matrix[i][j] + k;
		}
	return distances[degrees] = min_d;
}

int main()
{
	while (true) {
		int n, m;
		cin >> n;
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matrix[i][j] = (i != j) ? numeric_limits<int>::max() : 0;
		for (int i = 0; i < (1 << n); i++)
			distances[i] = -1;
		cin >> m;
		int s = 0, degrees = 0; // i-th bit of degrees is 1 if i-th vertex has odd degrees
		while (m--) {
			int u, v, w;
			cin >> u >> v >> w;
			u--; v--;
			if (w < matrix[u][v])
				matrix[u][v] = matrix[v][u] = w;
			s += w;
			degrees ^= 1 << u; degrees ^= 1 << v;
		}
		floyd_warshall(n);
		cout << s + matching(n, degrees) << endl;
	}
	return 0;
}

/*
4 5
1 2 3
2 3 4
3 4 5
1 4 10
1 3 12
0

41
*/

