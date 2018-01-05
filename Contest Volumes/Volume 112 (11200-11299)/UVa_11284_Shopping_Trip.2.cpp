
/*
	UVa 11284 - Shopping Trip

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11284_Shopping_Trip.cpp

	This si another accepted solution.
*/

#include <algorithm>
#include <limits>
#include <cstdio>
using namespace std;

const int infinite = numeric_limits<int>::max();
const int N_max = 50, P_max = 12;

int matrix[N_max + 1][N_max + 1];
	// matrix[i][j] is the min. distances between the store i and j
struct store {
	int i_;
	int cost_;
} stores[P_max + 1];

int costs[P_max + 1][P_max + 1];
	// costs[i][j] is the cost between the stores of i and j where DVD may be bought
int bitmasks[1 << (P_max + 1)][P_max + 1];

int main()
{
	int s;
	scanf("%d", &s);
	while (s--) {
		int N, M;
		scanf("%d %d", &N, &M);
		for (int i = 0; i <= N; i++)
			for (int j = 0; j <= N; j++)
				matrix[i][j] = (i != j) ? infinite : 0;
		while (M--) {
			int i, j, dollars, cents, cost;
			scanf("%d %d %d.%d", &i, &j, &dollars, &cents);
			cost = dollars * 100 + cents;
			if (cost < matrix[i][j])
				matrix[i][j] = matrix[j][i] = cost;
		}
		int P;
		scanf("%d", &P);
		for (int i = 1; i <= P; i++) {
			int dollars, cents;
			scanf("%d %d.%d", &stores[i].i_, &dollars, &cents);
			stores[i].cost_ = dollars * 100 + cents;
		}
		for (int k = 0; k <= N; k++)
			for (int i = 0; i <= N; i++)
				if (matrix[i][k] < infinite)
					for (int j = 1; j <= N; j++)
						if (matrix[k][j] < infinite)
							matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
		for (int i = 1; i <= P; i++)
			costs[0][i] = costs[i][0] = matrix[0][stores[i].i_];
		for (int i = 1; i <= P; i++)
			for (int j = 1; j <= P; j++)
				costs[i][j] = matrix[stores[i].i_][stores[j].i_];
		int places = 1 << (P + 1);
		for (int i = 0; i < places; i++)
			for (int j = 0; j <= P; j++)
				bitmasks[i][j] = infinite;
		for (int j = 0; j <= P; j++)
			bitmasks[places - 1][j] = costs[0][j];
        for (int mask = places - 1; mask >= 0; mask--)
			for (int i= 0; i <= P; i++)
				if (mask & (1 << i))
					for (int j = 0; j <= P; j++)
                        if (!(mask & (1 << j)))
							bitmasks[mask][i] = min(bitmasks[mask][i],
								min(bitmasks[mask | (1 << j)][i], bitmasks[mask | (1 << j)][j] + costs[j][i] - stores[j].cost_));
		int min_cost = bitmasks[1][0];
		if (min_cost < 0) {
			min_cost = -min_cost;
			printf("Daniel can save $%d.%02d\n", min_cost / 100, min_cost % 100);
		}
		else
			puts("Don't leave the house");
	}
	return 0;
}

