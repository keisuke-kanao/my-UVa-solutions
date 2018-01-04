
/*
	UVa 12157 - Tariff Plan

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12157_Tariff_Plan.cpp
*/

#include <iostream>
using namespace std;

int calculate_cost(int n, int calls[], int t, int c)
{
	int cost = 0;
	for (int i = 0; i < n; i++) {
		cost += (1 + calls[i] / t) * c;
	}
	return cost;
}

int main()
{
	const int n_max = 20, mile_t = 30, juice_t = 60, mile_c = 10, juice_c = 15;
	int calls[n_max];
	int t;
	cin >> t;
	for (int cn = 1; cn <= t; cn++) {
		int n;
		cin >> n;
		for (int i = 0; i < n; i++)
			cin >> calls[i];
		int mile_cost = calculate_cost(n, calls, mile_t, mile_c),
			juice_cost = calculate_cost(n, calls, juice_t, juice_c);
		cout << "Case " << cn;
		if (mile_cost < juice_cost)
			cout << ": Mile " << mile_cost << endl;
		else if (mile_cost > juice_cost)
			cout << ": Juice " << juice_cost << endl;
		else
			cout << ": Mile Juice " << mile_cost << endl;
	}
	return 0;
}

