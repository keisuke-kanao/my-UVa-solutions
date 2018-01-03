
/*
	UVa 1235 - Anti Brute Force Lock

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1235_Anti_Brute_Force_Lock.cpp
*/

#include <algorithm>
#include <vector>
#include <set>
#include <limits>
#include <cstdio>
using namespace std;

const int nr_digits = 4, N_max = 500;
int keys[N_max + 1][nr_digits], edges[N_max + 1][N_max + 1];

int get_number_of_rolls(const int* ki, const int* kj)
{
	int d = 0;
	for (int k = 0; k < nr_digits; k++, ki++, kj++) {
		int i = *ki, j = *kj;
		if (i < j)
			swap(i, j);
		d += min(i - j, j + 10 - i);
	}
	return d;
}

struct distance_comparator {
	const vector<int>& distances_;

	distance_comparator(const vector<int>& distances) : distances_(distances) {}
	bool operator() (int i, int j) const
	{
		return (distances_[i] != distances_[j]) ? distances_[i] < distances_[j] : i < j;
	}
};

int mst_prim(int n, int s)
{
	vector<bool> visited(n, false);
	vector<int> distances(n, numeric_limits<int>::max());
	distances[s] = 0;
	int mst_distance = 0;
	set<int, distance_comparator> pq(distances); // priority queue
	if (!s) { // zero key (0000) is not in the unlock key list
		int u = 0, d = numeric_limits<int>::max();
		for (int v = 1; v < n; v++)
			if (edges[s][v] < d) {
				u = v; d = edges[s][v];
			}
		distances[u] = d;
		pq.insert(u);
	}
	else
		pq.insert(s);
	while (!pq.empty()) {
		int u = *pq.begin();
		pq.erase(pq.begin());
		visited[u] = true;
		mst_distance += distances[u];
		for (int v = 1; v < n; v++)
			if (!visited[v] && edges[u][v] < distances[v]) {
				pq.erase(v); // remove v if it has already been in the queue
				distances[v] = edges[u][v];
				pq.insert(v);
			}
	}
	return mst_distance;
}

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int N;
		scanf("%d", &N);
		int zero_key = 0;
		for (int i = 1; i <= N; i++) {
			char s[nr_digits + 1];
			scanf("%s", s);
			int k = 0;
			for (int j = 0; j < nr_digits; j++) {
				keys[i][j] = s[j] - '0';
				k += keys[i][j];
			}
			if (!k)
				zero_key = i;
		}
		for (int i = 0; i < N; i++)
			for (int j = i + 1; j <= N; j++)
				edges[i][j] = edges[j][i] = get_number_of_rolls(keys[i], keys[j]);
		// apply Prim's minimum spanning tree algorithm
		printf("%d\n", mst_prim(N + 1, zero_key));
	}
	return 0;
}

