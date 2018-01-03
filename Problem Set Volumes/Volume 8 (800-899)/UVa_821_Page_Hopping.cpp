
/*
	UVa 821 - Page Hopping

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_821_Page_Hopping.cpp
*/

#include <iostream>
#include <iomanip>
#include <map>
#include <limits>
using namespace std;

const int n_max = 100;
int matrix[n_max][n_max];

int get_vertex(int n, map<int, int>& numbers)
{
	pair< map<int, int>::iterator, bool> result = numbers.insert(make_pair(n, numbers.size()));
	return result.first->second;
}

void floyd_warshall(int n)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (matrix[i][k] != numeric_limits<int>::max() && matrix[k][j] != numeric_limits<int>::max()) {
					int through_k = matrix[i][k] + matrix[k][j]; // distance through vertex k
 					if (through_k < matrix[i][j])
						matrix[i][j] = through_k;
				}
}

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int u, v;
		cin >> u >> v;
		if (!u && !v)
			break;
		for (int i = 0; i < n_max; i++)
			for (int j = 0; j < n_max; j++)
				matrix[i][j] = numeric_limits<int>::max();
		map<int, int> numbers;
		do {
			int i = get_vertex(u, numbers), j = get_vertex(v, numbers);
			matrix[i][j] = 1;
			cin >> u >> v;
		} while (u && v);
		int n = numbers.size();
		floyd_warshall(n);
		int path_length = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (i != j)
					path_length += matrix[i][j];
		cout << "Case " << case_nr << ": average length between pages = " <<
			fixed << setprecision(3) << static_cast<double>(path_length) / (n * (n - 1)) << " clicks\n";
	}
	return 0;
}

