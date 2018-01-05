
/*
	UVa 10980 - Lowest Price in Town

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10980_Lowest_Price_in_Town.cpp
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstdio>
using namespace std;

/*
Dynamic programming. Only 1 dimension that is the itemCount.
For each uninitialized price for a certain itemCount, search among all given prices, 
and then search among all smaller cases to find the best price, and then save and return it.
*/

const int M_max = 20, K_max = 100;

struct item_price {
	int N_;
	double P_;
} item_prices[M_max];

double lowest_prices[K_max + 1];

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		string s;
		istringstream iss;
		if (!getline(cin, s))
			break;
		iss.str(s);
		double price;
		int M;
		iss >> price >> M;
		iss.clear();
		for (int i = 0; i < M; i++) {
			getline(cin, s);
			iss.str(s);
			iss >> item_prices[i].N_ >> item_prices[i].P_;
			iss.clear();
		}
		for (int k = 1; k <= K_max; k++) {
			double p = price * k;
			for (int i = 0; i < M; i++) {
				const item_price& ip = item_prices[i];
				p = min(p, ip.P_ * (k + ip.N_ - 1) / ip.N_);
				for (int j = 1; j <= ip.N_; j++)
					if (k - j >= 0)
						p = min(p, lowest_prices[k - j] + ip.P_);
					else
						break;
			}
			lowest_prices[k] = p;
#ifdef DEBUG
			printf("%d: %lf\n", k, p);
#endif
		}
		cout << "Case " << case_nr << ":\n";
		getline(cin, s);
		iss.str(s);
		int K;
		while (iss >> K)
			cout << "Buy " << K << " for $" << fixed << setprecision(2) << lowest_prices[K] << endl;
		iss.clear();
	}
	return 0;
}

