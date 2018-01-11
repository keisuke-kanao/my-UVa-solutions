
/*
	UVa 562 - Dividing coins

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_562_Dividing_coins.cpp

	An accepted solution
*/

#include <iostream>
#include <vector>
using namespace std;

int divide_coins(int m, int sum, const vector<int>& coins)
{
	int half = sum / 2;
	vector<bool> p(half + 1, false);
		// p[i] is true is some subset of coins has a sum of i
	p[0] = true;
	int i, j;
	for (i = 1; i <= m; i++)
		for (j = half; j >= coins[i]; j--)
			if (p[j - coins[i]])
				p[j] = true;
	for (i = half; !p[i]; i--)
		;
	// at this point, i is the nearest to the half of sum
	return sum - 2 * i; // (sum - i) - i
}

int main()
{
	int n;
	cin >> n;
	while (n--) {
		int m;
		cin >> m;
		vector<int> coins(m + 1);
		int sum = 0;
		for (int i = 1; i <= m; i++) {
			cin >> coins[i];
			sum += coins[i];
		}
		cout << divide_coins(m, sum, coins) << endl;
	}
	return 0;
}

