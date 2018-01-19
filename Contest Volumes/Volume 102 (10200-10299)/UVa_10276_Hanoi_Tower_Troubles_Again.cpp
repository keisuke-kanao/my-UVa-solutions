
/*
	9.6.8 Hanoi Tower Troubles Again!
	PC/UVa IDs: 110908/10276, Popularity: B, Success rate: high Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10276_Hanoi_Tower_Troubles_Again.cpp
*/

/*
	Let nr_pegs be the number of pegs, starting with the balls of (nr_pegs + 1), 

	Generate a DAG (Directed Acyclic Graph) where vertices are balls and 
	there are edges (i, j) between any pair of balls of number i, j (i < j), provided 
	the sum of i and j is a perfect square.

	Generate a set of paths in the DAG in which each vertex belongs to only one of them, 
	and see if the number of paths is equal to or less than the number of pegs.
	If this condition is satisfied, add a vertex and repeat the process.
*/

#include <iostream>
#include <vector>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

bool perfect_square(int i, int j)
{
	int s = i + j;
	int r = static_cast<double>(sqrt(static_cast<double>(s)));
	return s == r * r;
}

#ifdef DEBUG
void print_path(int start, int end, const vector<int>& parents)
{
	if (parents[start] != start)
		print_path(parents[start], end, parents);
	cout << start << ' ';
	if (start == end)
		cout << endl;
}
#endif

void count_paths(int start, const vector< vector<int> >& dag, vector<int>& parents, int max_paths, int& min_paths)
{
	bool found_path = false;
	for (int i = 0; i < dag[start].size(); i++) {
		int j = dag[start][i];
		if (parents[j] == -1) {
			found_path = true;
			parents[j] = start;
			count_paths(j, dag, parents, max_paths, min_paths);
			parents[j] = -1;
		}
		if (min_paths <= max_paths)
			return;
	}
	if (!found_path) {
#ifdef DEBUG
		print_path(start, start, parents);
#endif
		int i;
		int nr_paths = 0;
		for (i = 0; i < parents.size(); i++) {
			if (parents[i] == -1)
				break;
			else if (parents[i] == i) // start vertex of each path
				nr_paths++;
		}
		if (i == parents.size()) { // all of the vertices have been visited
			if (nr_paths < min_paths)
				min_paths = nr_paths;
#ifdef DEBUG
			cout << "number of paths = " << nr_paths << endl;
#endif
		}
		else {
			parents[i] = i;
			count_paths(i, dag, parents, max_paths, min_paths);
		}
	}
}

int main(int /* argc */, char** /* argv */)
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		int nr_pegs;
		cin >> nr_pegs;
		int n = nr_pegs + 1;
		vector< vector<int> > dag(n);
		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				if (perfect_square(i + 1, j + 1))
					dag[i].push_back(j);
		while (true) {
			int min_paths = nr_pegs + 1;
			vector<int> parents(n, -1);
			parents[0] = 0;
#ifdef DEBUG
			cout << "number of balls = " << n << endl;
#endif
			count_paths(0, dag, parents, nr_pegs, min_paths);
			if (min_paths > nr_pegs)
				break;
			n++;
			dag.push_back(vector<int>());
			for (int i = 0; i < n - 1; i++)
				if (perfect_square(i + 1, n))
					dag[i].push_back(n - 1);
		}
		cout << n - 1 << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

