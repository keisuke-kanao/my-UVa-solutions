
/*
	UVa 812 - Trade on Verweggistan

	To build using Visucal Studio 2012:
		cl -EHsc UVa_812_Trade_on_Verweggistan.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int w_max = 50, b_max = 20;
int boxes[w_max], max_profits[w_max];
int profits[w_max][b_max];
	// profits[i][j] is the accumulated profits up to j-th pile of i-th workyard
bool pruls[w_max + 1][w_max * b_max + 1];
	// pruls[][i] is true if i pruls have to be bought to get the max. profits

int main()
{
	const int price = 10;
	for (int wn = 1; ; wn++) {
		int w;
		scanf("%d", &w);
		if (!w)
			break;
		if (wn > 1)
			putchar('\n');
		int max_p = 0;
		for (int i = 0; i < w; i++) {
			scanf("%d", &boxes[i]);
			max_profits[i] = -1;
			for (int j = 0, k = 0; j < boxes[i]; j++) {
				int p;
				scanf("%d", &p);
				p = price - p;
				k += p;
				profits[i][j] = k;
				max_profits[i] = max(max_profits[i], k);
			}
#ifdef DEBUG
			printf("%d:", max_profits[i]);
			for (int j = 0; j < boxes[i]; j++)
				printf(" %d", profits[i][j]);
			putchar('\n');
#endif
			if (max_profits[i] >= 0)
				max_p += max_profits[i];
		}
		pruls[0][0] = true;
		int pi = 0, sb = 0;
		for (int i = 0; i < w; i++)
			if (max_profits[i] >= 0) {
				pi++;
				for (int k = 0; k <= sb + boxes[i]; k++)
					pruls[pi][k] = false;
				if (!max_profits[i])
					for (int k = 0; k <= sb; k++)
						if (pruls[pi - 1][k])
							pruls[pi][k] = true;
				for (int j = 0; j < boxes[i]; j++)
					if (profits[i][j] == max_profits[i])
						for (int k = 0; k <= sb; k++)
								if (pruls[pi - 1][k])
									pruls[pi][k + j + 1] = true;
				sb += boxes[i];
#ifdef DEBUG
				for (int k = 0; k <= sb; k++)
					if (pruls[pi][k])
						printf("%d ", k);
				putchar('\n');
#endif
			}
		printf("Workyards %d\n", wn);
		printf("Maximum profit is %d.\n", max_p);
		printf("Number of pruls to buy:");
		for (int i = 0, j = 0; i <= sb && j < 10; i++)
			if (pruls[pi][i]) {
				printf(" %d", i);
				j++;
			}
		putchar('\n');
	}
	return 0;
}

