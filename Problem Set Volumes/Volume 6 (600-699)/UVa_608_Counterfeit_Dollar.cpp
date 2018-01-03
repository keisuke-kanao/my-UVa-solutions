
/*
	UVa 608 - Counterfeit Dollar

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_608_Counterfeit_Dollar.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_coins_max = 'L' - 'A' + 1, nr_weighings = 3;

struct weighing {
	char left_coins_[nr_coins_max + 1], right_coins_[nr_coins_max + 1];
	int result_; // 1 for "up", 0 for "even", -1 for "down"
};

bool weigh_coins(char coin, int light_or_heavy /* 1 for light, -1 for heavy */, weighing& w)
{
	int left_weight = 0, right_weight = 0;
	for (const char* p = w.left_coins_; *p; p++)
		if (*p == coin) {
			left_weight = light_or_heavy;
			break;
		}
	for (const char* p = w.right_coins_; *p; p++)
		if (*p == coin) {
			right_weight = light_or_heavy;
			break;
		}
	return (right_weight == left_weight && !w.result_ || right_weight > left_weight && w.result_ > 0 ||
		right_weight < left_weight && w.result_ < 0) ? true : false;
}

int main()
{
	bool coins[nr_coins_max]; // coins[i] is true if coin of 'A' + i is used for the weighings
	weighing weighings[nr_weighings];
	int t;
	scanf("%d", &t);
	while (t--) {
		memset(coins, 0, sizeof(coins));
		for (int i = 0; i < nr_weighings; i++) {
			char result[nr_coins_max + 1];
			scanf("%s %s %s", weighings[i].left_coins_, weighings[i].right_coins_, result);
			for (const char *p = weighings[i].left_coins_; *p; p++)
				coins[*p - 'A'] = true;
			for (const char *p = weighings[i].right_coins_; *p; p++)
				coins[*p - 'A'] = true;
			weighings[i].result_ = ((!strcmp(result, "even")) ? 0 : ((!strcmp(result, "up")) ? 1 : -1));
		}
		for (int i = 0; i < nr_coins_max; i++)
			if (coins[i]) {
				int j;
				// see if the coin of 'A' + i is the heavy counterfeit
				for (j = 0; j < nr_weighings; j++)
					if (!weigh_coins('A' + i, -1, weighings[j]))
						break;
				if (j == nr_weighings) {
					printf("%c is the counterfeit coin and it is heavy.\n", 'A' + i);
					break;
				}
				// see if the coin of 'A' + i is the light counterfeit
				for (j = 0; j < nr_weighings; j++)
					if (!weigh_coins('A' + i, 1, weighings[j]))
						break;
				if (j == nr_weighings) {
					printf("%c is the counterfeit coin and it is light.\n", 'A' + i);
					break;
				}
			}
	}
	return 0;
}

