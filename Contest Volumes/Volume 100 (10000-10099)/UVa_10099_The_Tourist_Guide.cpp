
/*
	9.6.3 The Tourist Guide
	PC/UVa IDs: 110903/10099, Popularity: B, Success rate: average Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10099_The_Tourist_Guide.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

void floyd(int n, vector< vector<int> >& matrix) // the maximin Floyd-Warshall algorithm
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++) {
			if (matrix[i][k] != INT_MIN)
				for (int j = 0; j < n; j++)
					if (matrix[k][j] != INT_MIN)
						matrix[i][j] = max(matrix[i][j], min(matrix[i][k], matrix[k][j]));
		}
}

int main(int /* argc */, char** /* argv */)
{
	for (int scenario = 1; ; scenario++) {
		int n /* number of cities */, r /* number of road segments */;
		cin >> n >> r;
		if (!n && !r)
			break;
		vector< vector<int> > matrix(n, vector<int>(n, INT_MIN));
		for (int i = 0; i < n; i++)
			matrix[i][i] = 0;
		for (int i = 0; i < r; i++) {
			int c1, c2, p;
			cin >> c1 >> c2 >> p;
			c1--; c2--;
			matrix[c1][c2] = matrix[c2][c1] = p;
		}
		int start, end, tourists;
		cin >> start >> end >> tourists;
		start--; end--;
		int trips = 0;
		if (start == end)
			trips = 1;
		else {
			floyd(n, matrix); // the maximin Floyd-Warshall algorithm
#ifdef DEBUG
			cout << matrix[start][end] << endl;
#endif
			int max_capacity = matrix[start][end] - 1; // each trip should be accompanied by the turist guide
			trips = tourists / max_capacity;
			if (tourists % max_capacity)
				trips++;
		}
		cout << "Scenario #" << scenario << endl;
		cout << "Minimum Number of Trips = " << trips << endl << endl;
	}
	return 0;
}

