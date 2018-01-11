
/*
	UVa 10130 - SuperSale

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10130_SuperSale.cpp

	This is a typical 0-1 knapsack problem.
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int calculate_max_price(int n, int w, const vector< pair<int, int> >& objects, vector<int>& prices)
{
	for (int i = 0; i < n; i++) {
		const pair<int, int>& object = objects[i];
		for (int j = w; j >= object.second; j--)
			prices[j] = max(prices[j], prices[j - object.second] + object.first);
	}
	return prices[w];
}

int main()
{
	const int max_weight = 30;
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		int n; // number of objects
		cin >> n;
		vector< pair<int, int> > objects(n);
			// objects[i].first is the price, objects[i].second is the weight
		for (int i = 0; i < n; i++)
			cin >> objects[i].first >> objects[i].second;
		vector<int> prices(max_weight + 1, 0);
		calculate_max_price(n, max_weight, objects, prices);
		int g; // number of people in the group
		cin >> g;
		int max_price = 0;
		for (int i = 0; i < g; i++) {
			int w; // max. weight
			cin >> w;
			max_price += prices[w];
		}
		cout << max_price << endl;
	}
	return 0;
}

