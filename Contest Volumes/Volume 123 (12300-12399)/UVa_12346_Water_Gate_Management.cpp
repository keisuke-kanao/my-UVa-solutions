
/*
	UVa 12346 - Water Gate Management

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12346_Water_Gate_Management.cpp
*/

#include <cstdio>
#include <algorithm>
using namespace std;

const int n_max = 20;

struct gate {
	int flow_rate_, cost_;
	long long volume_;

	bool operator<(const gate& g) const {
		return (flow_rate_ != g.flow_rate_) ? flow_rate_ > g.flow_rate_ : cost_ < g.cost_;
	}
} gates[n_max];

long long sums[n_max];
	// sums[i] is the sum of volumes between i-th gate and (n - 1)-th gate

void gate_management(int n, int ni, long long V, long long s, int cost, int& min_cost)
{
	if (s >= V) {
		if (min_cost == -1 || cost < min_cost)
			min_cost = cost;
	}
	else if (ni < n && s + sums[ni] >= V) {
		gate_management(n, ni + 1, V, s + gates[ni].volume_, cost + gates[ni].cost_, min_cost);
		gate_management(n, ni + 1, V, s, cost, min_cost);
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d %d", &gates[i].flow_rate_, &gates[i].cost_);
	sort(gates, gates + n);
	int m;
	scanf("%d", &m);
	for (int case_nr = 1; case_nr <= m; case_nr++) {
		long long V, T;
		scanf("%lld %lld", &V, &T);
		long long s = 0;
		for (int i = n - 1; i >= 0; i--) {
			gates[i].volume_ = gates[i].flow_rate_ * T;
			s += gates[i].volume_;
			sums[i] = s;
		}
		int min_cost = -1;
		gate_management(n, 0, V, 0, 0, min_cost);
		printf("Case %d: ", case_nr);
		if (min_cost != -1)
			printf("%d\n", min_cost);
		else
			puts("IMPOSSIBLE");
	}
	return 0;
}

