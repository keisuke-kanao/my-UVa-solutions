
/*
	UVa 11832 - Account Book

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11832_Account_Book.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int N_max = 40, F_min = -16000, F_max = 16000;

int Ti[N_max + 1];
bool cash_flow[N_max + 1][F_max - F_min + 1][2];
	// cash_flow[i][j][0/1] is the cash_flow of j, up to i-th transaction, with i-th transaction of income (1) or expense (0)
char transactions[N_max + 2];

void transaction(int n, int f)
{
	int t = Ti[n];
	if (cash_flow[n][f - F_min][0]) {
		cash_flow[n][f - F_min][0] = false;
		if (transactions[n] != '?')
			transactions[n] = (transactions[n] == '+') ? '?' : '-';
#ifdef DEBUG
		printf("[%d][%d][0]: %c\n", n, f, transactions[n]);
#endif
		if (n > 1)
			transaction(n - 1, f + t);
	}
	if (cash_flow[n][f - F_min][1]) {
		cash_flow[n][f - F_min][1] = false;
		if (transactions[n] != '?')
			transactions[n] = (transactions[n] == '-') ? '?' : '+';
#ifdef DEBUG
		printf("[%d][%d][1]: %c\n", n, f, transactions[n]);
#endif
		if (n > 1)
			transaction(n - 1, f - t);
	}
}

int main()
{
	while (true) {
		int N, F;
		scanf("%d %d", &N, &F);
		if (!N)
			break;
		for (int i = 1; i <= N; i++)
			scanf("%d", &Ti[i]);
		memset(cash_flow, 0, sizeof(cash_flow));
		int j_min = -Ti[1] - F_min, j_max = Ti[1] - F_min;
		cash_flow[1][j_min][0] = cash_flow[1][j_max][1] = true;
#ifdef DEBUG
		printf("[1][%d][0] [1][%d][1]\n", j_min + F_min, j_max + F_min);
#endif
		for (int i = 2; i <= N; i++) {
			int t = Ti[i];
			for (int j = j_min; j <= j_max; j++)
				if (cash_flow[i - 1][j][0] || cash_flow[i - 1][j][1]) {
					if (j - t >= 0)
						cash_flow[i][j - t][0] = true;
					if (j + t <= F_max - F_min)
					cash_flow[i][j + t][1] = true;
				}
			j_min = max(j_min - t, 0), j_max = min(j_max + t, F_max - F_min);
#ifdef DEBUG
			for (int j = j_min; j <= j_max; j++)
				for (int k = 0; k < 2; k++)
					if (cash_flow[i][j][k])
						printf("[%d][%d][%d] ", i, j + F_min, k);
			putchar('\n');
#endif
		}
		if (cash_flow[N][F - F_min][0] || cash_flow[N][F - F_min][1]) {
			memset(transactions, 0, sizeof(transactions));
			transaction(N, F);
			puts(transactions + 1);
		}
		else
			puts("*");
	}
	return 0;
}

