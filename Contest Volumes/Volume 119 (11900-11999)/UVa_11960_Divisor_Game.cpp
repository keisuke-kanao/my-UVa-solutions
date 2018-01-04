
/*
	UVa 11960 - Divisor Game

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11960_Divisor_Game.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int N_max = 1000000;
int nr_of_divisors[N_max + 1], most_divisors[N_max + 1];

int main()
{
	for (int i = 1; i <= N_max; i++)
		for (int j = i; j <= N_max; j += i)
			nr_of_divisors[j]++;
	for (int i = 1, most = 0, most_i = 0; i <= N_max; i++) {
		if (most <= nr_of_divisors[i]) {
			most = nr_of_divisors[i];
			most_i = i;
		}
		most_divisors[i] = most_i;
	}
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		printf("%d\n", most_divisors[n]);
	}
	return 0;
}

