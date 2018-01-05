
/*
	UVa 11264 - Coin Collector

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11264_Coin_Collector.cpp
*/

/*
from Methods to Solve (http://www.comp.nus.edu.sg/~stevenha/programming/volC12.html#11264_-_Coin_Collector):

This is quite a difficult greedy problem because it depends on the person attempting it to spot the pattern. 
counter is set to n. 
Start with the total equaling the first coin. 
Then start the loop from the second coin onwards. 
If the sum of the total and the current coin value exceeds or equals the value of the coin right after the current coin, 
the current coin's value is not taken into the total and counter is decremented by one. 
Output counter at the end of the loop.
*/

#include <cstdio>

const int n_max = 1000;
int coins[n_max];

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &coins[i]);
		int counter = n;
		long long total = coins[0];
		for (int i = 1; i < n - 1; i++) {
			if (total + coins[i] >= coins[i + 1])
				counter--;
			else
				total += coins[i];
		}
		printf("%d\n", counter);
	}
	return 0;
}

/*
2
6
		1  2  4  8 16 32
total	1  3  7 15 31

6
		1  3  6  8 15 20
total	1  4    12
*/

