
/*
	11.6.3 Weights and Measures
	PC/UVa IDs: 111103/10154, Popularity: C, Success rate: average Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10154_Weights_and_Measures.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

struct turtle {
	int weight;
	int strength;
	turtle(int _weight, int _strength) : weight(_weight), strength(_strength) {}
};

bool compare_turtle(const turtle& i, const turtle& j)
{
	return i.strength < j.strength;
}

int turtle_stack(const vector<turtle>& turtles)
{
	vector<turtle> t = turtles;
	t.push_back(turtle(0, 0)); // to match the indices to the vector of turtles with the ones to the below mw
	sort(t.begin(), t.end(), compare_turtle);
	int n = t.size();
	vector< vector<int> > mw(2, vector<int>(n, 0)); // just to hold the previous and current states
	for (int i = 0; i < mw.size(); i++)
		for (int k = 0; k < n; k++)
			mw[i][k] = (k) ? INT_MAX : 0;
	for (int i = 1; i < n; i++) {
		int mw_pi = (i - 1) % 2, mw_ci = i % 2; // indices to the previous and current slot in mw
		for (int k = 1; k <= i; k++) {
			long long w = static_cast<long long>(mw[mw_pi][k - 1]) + t[i].weight;
			if (w <= t[i].strength)
				mw[mw_ci][k] = min(static_cast<long long>(mw[mw_pi][k]), w);
			else
				mw[mw_ci][k] = mw[mw_pi][k];
		}
	}
	int k = n - 1;
	for ( ; mw[(n - 1) % 2][k] == INT_MAX; k--)
		;
/*
	vector< vector<int> > mw(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++)
		for (int k = 0; k < n; k++)
			mw[i][k] = (k) ? INT_MAX : 0;
	for (int i = 1; i < n; i++)
		for (int k = 1; k <= i; k++) {
			long long w = static_cast<long long>(mw[i - 1][k - 1]) + t[i].weight;
			if (w <= t[i].strength)
				mw[i][k] = min(static_cast<long long>(mw[i - 1][k]), w);
			else
				mw[i][k] = mw[i - 1][k];
		}
	int k = n - 1;
	for ( ; mw[n - 1][k] == INT_MAX; k--)
		;
*/
	return k;
}

int main(int /* argc */, char** /* argv */)
{
	int weight, strength;
	vector<turtle> turtles;
	while (cin >> weight >> strength)
		turtles.push_back(turtle(weight, strength));
	cout << turtle_stack(turtles) << endl;
	return 0;
}

