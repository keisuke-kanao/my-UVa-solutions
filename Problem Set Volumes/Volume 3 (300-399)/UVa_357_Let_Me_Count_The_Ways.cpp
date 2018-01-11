
/*
	UVa 357 - Let Me Count The Ways

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_357_Let_Me_Count_The_Ways.cpp
*/

#include <iostream>
#include <cstring>
using namespace std;

const int nr_coins = 5;
const int coins[] = {1, 5, 10, 25, 50};
const int amount_max = 30000;
long long changes[amount_max + 1];

int main()
{
	memset(changes, 0, sizeof(changes));
	changes[0] = 1;
	for (int i = 0; i < nr_coins; i++)
		for (int j = 1; j <= amount_max; j++)
            if (j >= coins[i])
                changes[j] += changes[j - coins[i]];
	int amount;
	while (cin >> amount) {
		if (changes[amount] > 1)
			cout << "There are " << changes[amount] << " ways to produce " << amount << " cents change.\n";
		else
			cout << "There is only 1 way to produce " << amount <<" cents change.\n";
	}
	return 0;
}

