
/*
	UVa 10819 - Trouble of 13-Dots

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10819_Trouble_of_13_Dots.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int m_max = 10000 + 200, n_max = 100;
int max_favours[m_max + 1]; // max_favours[i] is the max. total favour valus for the expense of i

int main()
{
	int m, n;
	while (scanf("%d %d", &m, &n) != EOF) {
		int expense = m;
		if (m > 1800) // m + 200 > 2000
			expense += 200;
		memset(max_favours, 0, sizeof(max_favours));
		for (int i = 0; i < n; i++) {
			int p, f;
			scanf("%d %d", &p, &f);
			for (int j = expense; j > p; j--)
				if (max_favours[j - p])
					max_favours[j] = max(max_favours[j], max_favours[j - p] + f);
			max_favours[p] = max(max_favours[p], f);
#ifdef DEBUG
		for (int j = 0; j <= expense; j++)
			if (max_favours[j])
				printf("\t%d %d\n", j, max_favours[j]);
#endif
		}
		int max_f = 0;
		for (int i = 1; i <= expense; i++) {
			if (m <= 2000 && i > m && i <= 2000)
				continue;
			if (max_favours[i] > max_f)
				max_f = max_favours[i];
		}
		printf("%d\n", max_f);
	}
	return 0;
}

