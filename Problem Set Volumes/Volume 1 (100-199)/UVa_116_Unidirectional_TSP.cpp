
/*
	11.6.4 Unidirectional TSP
	PC/UVa IDs: 111104/116, Popularity: A, Success rate: low Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_116_Unidirectional_TSP.cpp
*/

#include <iostream>
#include <vector>
#include <utility>
#include <numeric>
#include <algorithm>
using namespace std;

void print_path(int columns, const pair<long long, vector<int> >& path)
{
	for (int i = 0; i < columns; i++)
		cout << path.second[i] + 1 << ((i == columns - 1) ? '\n' : ' ');
	cout << path.first << endl;
}

bool compare_partial_path(int columns, const pair<long long, int>& i, const pair<long long, int>& j,
	const vector< pair<long long, vector<int> > >& previous_paths) // return true if i < j, false otherwise
{
	// first, compare theier weights
	if (i.first < j.first)
		return true;
	else if (i.first > j.first)
		return false;
	else { // if their weights are the same, then compare their paths so far
		const vector<int>& path_i = previous_paths[i.second].second;
		const vector<int>& path_j = previous_paths[j.second].second;
		for (int k = 0; k < columns; k++) {
			if (path_i[k] < path_j[k])
				return true;
			else if (path_i[k] > path_j[k])
				return false;
		}
		return false;
	}
}

void unidirectional_tsp(int m, int n, const vector< vector<long long> >& weights,
	vector< pair<long long, vector<int> > >& paths)
{
	for (int i = 0; i < m; i++) {
		paths[i].first = weights[i][0];
		paths[i].second[0] = i;
	}
	for (int j = 1; j < n; j++) {
		vector< pair<long long, vector<int> > > previous_paths(m, pair<long long, vector<int> >(0, vector<int>(n)));
		for (int i = 0; i < m; i++) // copy the previous paths
			previous_paths[i] = paths[i];
		for (int i = 0; i < m; i++) {
			// first is the weight of a path, second is the previous row of the path
			pair<long long, int> upper_left = make_pair(previous_paths[(i - 1 + m) % m].first, (i - 1 + m) % m);
			pair<long long, int> left = make_pair(previous_paths[i].first, i);
			pair<long long, int> lower_left = make_pair(previous_paths[(i + 1) % m].first, (i + 1) % m);
			// choose the minimum weight path of the three
			pair<long long, int> min_path = upper_left;
			if (compare_partial_path(j, left, min_path, previous_paths))
				min_path = left;
			if (compare_partial_path(j, lower_left, min_path, previous_paths))
				min_path = lower_left;
			paths[i].first = min_path.first + weights[i][j];
			paths[i].second = previous_paths[min_path.second].second; paths[i].second[j] = i;
		}
#if 0 // #ifdef _DEBUG
		for (int i = 0; i < m; i++)
			print_path(j + 1, paths[i]);
		cout << endl;
#endif
	}
}

bool compare_path(int n, const pair<long long, vector<int> >& i, const pair<long long, vector<int> >& j)
// return true if i < j, false oterwise
{
	// first, compare theier weigthts
	if (i.first < j.first)
		return true;
	else if (i.first > j.first)
		return false;
	else { // if their weights are the same, then compare their paths
		for (int k = 0; k < n; k++) {
			if (i.second[k] < j.second[k])
				return true;
			else if (i.second[k] > j.second[k])
				return false;
		}
		return false;
	}
}

int main(int /* argc */, char** /* argv */)
{
	int m, n;
	while (cin >> m >> n) {
		vector< vector<long long> > weights(m, vector<long long>(n));
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				cin >> weights[i][j];
		if (m == 1) {
			for (int j = 0; j < n; j++)
				cout << m << ((j < (n - 1)) ? ' ' : '\n');
			cout << accumulate(weights[0].begin(), weights[0].end(), static_cast<long long>(0)) << endl;
		}
		else {
			vector< pair<long long, vector<int> > > paths(m, pair<long long, vector<int> >(0, vector<int>(n)));
/*
			Each item of the vector is a pair of:
		 		the weight (first field)
				the path (second field): the array of row numbers so far
			for a row.
*/
			unidirectional_tsp(m, n, weights, paths);
#ifdef _DEBUG
			for (int i = 0; i < m; i++)
				print_path(n, paths[i]);
#endif
			pair<long long, vector<int> > min_path = paths[0];
			for (int i = 1; i < m; i++)
				if (compare_path(n, paths[i], min_path))
					min_path = paths[i];
			print_path(n, min_path);
		}
	}
	return 0;
}

