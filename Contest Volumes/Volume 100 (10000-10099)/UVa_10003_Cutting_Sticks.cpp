
/*
	11.6.5 Cutting Sticks
	PC/UVa IDs: 111105/10003, Popularity: B, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10003_Cutting_Sticks.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
	Let the cutting ponts be p(i) (0 <= i <= n) where p(0) = 0 and p(n) = l (length of the stick).
	Let cs(i, j) be the minimum cutting cost for between p(i) and p(j) part of the stick.
	Then, the recursive relation is:
		cs(i, j) = p(j) - p(i) + min. {cs(i, k) + cs(k, j)} (for k = i + 1 to j - 1)
	The minimum cutting cost for the whole stick is cs(0, l).
*/

#ifdef __RECURSION__
int cutting_sticks(int i, int j, const vector<int>& points, int recursions)
{
	if (j - i < 2)
		return 0;
	int min_cost = INT_MAX;
	for (int k = i + 1; k < j; k++)
		min_cost = min(min_cost,
			cutting_sticks(i, k, points, recursions + 1) + cutting_sticks(k, j, points, recursions + 1));
	min_cost += points[j] - points[i];
#ifdef DEBUG
	while (recursions--)
		cout << ' ';
	cout << i << " - " << j << ": " << min_cost << endl;
#endif
	return min_cost;
}
#else // !__RECURSION__
int cutting_sticks(const vector<int>& points)
{
	int n = points.size();
	vector< vector<int> > costs(n, vector<int>(n, 0));
	// costs[i][j] represents the minimum. cutting cost between points[i] and points[j]
	for (int j = 2; j < n; j++)
		for (int i = 0; i < n - j; i++) {
			int cost = INT_MAX;
			for (int k = i + 1; k < i + j; k++)
				cost = min(cost, costs[i][k] + costs[k][i + j]);
			costs[i][i + j] = cost + points[i + j] - points[i];
		}
	return costs[0][n - 1];
}
#endif // __RECURSION__

int main(int /* argc */, char** /* argv */)
{
	while (true) {
		int l;
		cin >> l;
		if (!l)
			break;
		int n;
		cin >> n;
		vector<int> points(n + 2, 0);
		for (int i = 0; i < n; i++)
			cin >> points[i + 1];
		points[n + 1] = l;
#ifdef __RECURSION__
		cout << "The minimum cutting is " << cutting_sticks(0, n + 1, points, 0) << ".\n";
#else
		cout << "The minimum cutting is " << cutting_sticks(points) << ".\n";
#endif
	}
	return 0;
}

