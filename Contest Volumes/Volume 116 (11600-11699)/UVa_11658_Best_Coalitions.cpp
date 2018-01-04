
/*
	UVa 11658 - Best Coalitions

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11658_Best_Coalitions.cpp
*/

#include <cstdio>
#include <cstring>

const int n_max = 100, p_max = 10000;
int percentages[n_max + 1];
bool coalitions[p_max + 1];

int main()
{
	while (true) {
		int n, x;
		scanf("%d %d", &n, &x);
		if (!n)
			break;
		x--;
		int px;
		for (int i = 0, j = 0; i < n; i++) {
			int integral, decimal;
			scanf("%d.%d", &integral, &decimal);
			percentages[j] = integral * 100 + decimal;
			if (i == x)
				px = percentages[j];
			else
				j++;
		}
		if (px > 5000) {
			printf("%.2lf\n", 100.0);
			continue;
		}
		memset(coalitions, 0, sizeof(coalitions));
		int ci = 0;
		for (int i = 0; i < n - 1; i++) {
			int p = percentages[i];
			for (int j = ci; j; j--)
				if (coalitions[j])
					coalitions[j + p] = true;
			coalitions[p] = true;
			ci += p;
#ifdef DEBUG
			for (int j = 1; j <= ci; j++)
				if (coalitions[j])
					printf("%d%c", j, ((j < ci) ? ' ' : '\n'));
#endif
		}
		double sp = 0.0;
		for (int i = 5001 - px; i <= ci; i++)
			if (coalitions[i]) {
				sp = static_cast<double>(px) * 100.0 / static_cast<double>(px + i);
				break;
			}
		printf("%.2lf\n", sp);
	}
	return 0;
}

