
/*
	UVa 662 - Fast Food

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_662_Fast_Food.cpp
*/

#include <algorithm>
#include <limits>
#include <cstdio>
#include <cstdlib>
using namespace std;

const int n_max = 200, k_max = 30;

int distances[n_max + 1];

struct cost { // shopping cost
	int c_; // cost
	int di_; // index of the depot

	cost() {}
	cost(int c, int di) : c_(c), di_(di) {}
	cost& operator=(const cost& c) {c_ = c.c_; di_ = c.di_; return *this;}
};

cost costs[n_max + 1][n_max + 1];
	// costs[i][j]j is the shopping cost for restaurants i and j
cost min_costs[n_max + 1][n_max + 1][k_max + 1];
	// min_cost[i][j][k] is the min. shopping cost for restaurants i and j with k depots

#ifdef DEBUG
void print_costs(int n)
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			printf("{%d %d}%c", costs[i][j].c_, costs[i][j].di_, ((j < n) ? ' ' : '\n'));
	putchar('\n');
}
#endif

void calculate_costs(int n)
{
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++) {
			cost& c = costs[i][j];
			c.di_ = (i + j) / 2; // median
//			c.di_ = (i + j + 1) / 2; // median
			int d = distances[c.di_];
			c.c_ = 0;
			for (int x = i; x <= j; x++)
				c.c_ += abs(distances[x] - d);
		}
}

#ifdef DEBUG
void print_min_costs(int n, int k)
{
	printf("k: %d\n", k);
	for (int i = 1; i <= n; i++)
		printf("{%d %d}%c",min_costs[i][n][k].c_, min_costs[i][n][k].di_, ((i < n) ? ' ' : '\n'));
	putchar('\n');
}
#endif

void partition(int n, int k)
{
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			min_costs[i][j][1] = costs[i][j];
	for (int j = 1; j <= n; j++)
		min_costs[1][j][1] = costs[1][j];
#ifdef DEBUG
	print_min_costs(n, 1);
#endif
	for (int x = 2; x <= k; x++) {
		for (int i = 1; i <= n - x; i++) {
			int c = numeric_limits<int>::max(), di;
			for (int j = i; j <= n - x + 1; j++) {
#ifdef DEBUG
				printf("{%d-%d: %d} ", i, j, costs[i][j].c_ + min_costs[j + 1][n][x - 1].c_);
#endif
				if (costs[i][j].c_ + min_costs[j + 1][n][x - 1].c_ < c) {
					c = costs[i][j].c_ + min_costs[j + 1][n][x - 1].c_;
					di = j;
				}
			}
			min_costs[i][n][x] = cost(c, di);
#ifdef DEBUG
			printf("{%d %d}\n", min_costs[i][n][x].c_, min_costs[i][n][x].di_);
#endif
		}
		min_costs[n - x + 1][n][x] = cost(0, n - x + 1);
#ifdef DEBUG
		print_min_costs(n, x);
#endif
	}
}

void print_partition(int x, int i, int j, int di)
{
	if (i != j)
		printf("Depot %d at restaurant %d serves restaurants %d to %d\n", x, di, i, j);
	else
		printf("Depot %d at restaurant %d serves restaurant %d\n", x, di, i);
}

void print_partitions(int n, int i, int k, int x)
{
	int j = min_costs[i][n][k - x + 1].di_;
	if (x < k) {
		print_partition(x, i, j, costs[i][j].di_);
		print_partitions(n, j + 1, k, x + 1);
	}
	else
		print_partition(x, i, n, j);
}

int main()
{
	for (int chain_nr = 1; ; chain_nr++) {
		int n, k;
		scanf("%d %d", &n, &k);
		if (!n && !k)
			break;
		for (int i = 1; i <= n; i++)
			scanf("%d", &distances[i]);
		printf("Chain %d\n", chain_nr);
		if (k == n) {
			for (int i = 1; i <= n; i++)
				print_partition(i, i, i, i);
			puts("Total distance sum = 0");
		}
		else {
			calculate_costs(n);
#ifdef DEBUG
			print_costs(n);
#endif
			if (k == 1) {
				print_partition(k, 1, n, costs[1][n].di_);
				printf("Total distance sum = %d\n", costs[1][n].c_);
			}
			else {
				partition(n, k);
				print_partitions(n, 1, k, 1);
				printf("Total distance sum = %d\n", min_costs[1][n][k].c_);
			}
		}
		putchar('\n');
	}
	return 0;
}

