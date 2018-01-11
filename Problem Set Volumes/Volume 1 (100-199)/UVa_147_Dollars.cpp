
/*
	UVa 147 - Dollars

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_147_Dollars.cpp
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_notes_and_coins = 11;
const int notes_and_coins[] =
	{5 / 5, 10 / 5, 20 / 5, 50 / 5, 100 / 5, 200 / 5, 500 / 5, 1000 / 5, 2000 / 5, 5000 / 5, 10000 / 5};
const int amount_max = 30000;
long long ways[amount_max / 5 + 1];

int main()
{
	memset(ways, 0, sizeof(ways));
	ways[0] = 1;
	for (int i = 0; i < nr_notes_and_coins; i++)
		for (int j = 1; j <= amount_max / 5; j++)
            if (j >= notes_and_coins[i])
                ways[j] += ways[j - notes_and_coins[i]];
	while (true) {
		int dollars, cents;
		char decimal_point;
		cin >> dollars >> decimal_point >> cents;
		if (!dollars && !cents)
			break;
		printf("%3d.%02d%17lld\n", dollars, cents, ways[(dollars * 100 + cents) / 5]);
	}
	return 0;
}

