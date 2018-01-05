
/*
	UVa 10604 - Chemical Reaction

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10604_Chemical_Reaction.cpp

	This is another accepted solution.
*/

#include <algorithm>
#include <limits>
#include <cstdio>
#include <cstring>
using namespace std;

const int m_max = 6, k_max = 10;

int ncs[m_max + 1]; // types[i] is the number of i-th chemical type
struct {
	int type_, heat_;
} table[m_max + 1][m_max + 1];

bool visited[k_max + 1][k_max + 1][k_max + 1][k_max + 1][k_max + 1][k_max + 1];
int heats[k_max + 1][k_max + 1][k_max + 1][k_max + 1][k_max + 1][k_max + 1];

#ifdef DEBUG
int mix(int m, int index)
#else
int mix(int m)
#endif
{
#ifdef DEBUG
	for (int i = 0; i < index; i++)
		putchar(' ');
	printf("[%d][%d][%d][%d][%d][%d]\n", ncs[1], ncs[2], ncs[3], ncs[4], ncs[5], ncs[6]);
#endif
	if (visited[ncs[1]][ncs[2]][ncs[3]][ncs[4]][ncs[5]][ncs[6]])
		return heats[ncs[1]][ncs[2]][ncs[3]][ncs[4]][ncs[5]][ncs[6]];

	int min_heat = numeric_limits<int>::max(), type, heat;
	if (ncs[1] + ncs[2] + ncs[3] + ncs[4] + ncs[5] + ncs[6] == 1)
		min_heat = 0;
	else {
		for (int i = 1; i <= m; i++) {
			if (!ncs[i])
				continue;
			if (ncs[i] > 1) {
				type = table[i][i].type_, heat = table[i][i].heat_;
				ncs[i] -= 2, ncs[type]++;
#ifdef DEBUG
				heat += mix(m, index + 1);
#else
				heat += mix(m);
#endif
				ncs[i] += 2, ncs[type]--;
				min_heat = min(min_heat, heat);
			}
			for (int j = 1; j <= m; j++) {
				if (i == j || !ncs[j])
					continue;
				type = table[i][j].type_, heat = table[i][j].heat_;
				ncs[i]--, ncs[j]--, ncs[type]++;
#ifdef DEBUG
				heat += mix(m, index + 1);
#else
				heat += mix(m);
#endif
				ncs[i]++, ncs[j]++, ncs[type]--;
				min_heat = min(min_heat, heat);
			}
		}
	}
	visited[ncs[1]][ncs[2]][ncs[3]][ncs[4]][ncs[5]][ncs[6]] = true;
	heats[ncs[1]][ncs[2]][ncs[3]][ncs[4]][ncs[5]][ncs[6]] = min_heat;
#ifdef DEBUG
	for (int i = 0; i < index; i++)
		putchar(' ');
	printf("[%d][%d][%d][%d][%d][%d]: %d\n", ncs[1], ncs[2], ncs[3], ncs[4], ncs[5], ncs[6], min_heat);
#endif
	return min_heat;
}

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		int m;
		scanf("%d", &m);
		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d %d", &table[i][j].type_, &table[i][j].heat_);
		for (int i = 1; i <= m_max; i++)
			ncs[i] = 0;
		int k;
		scanf("%d", &k);
		while (k--) {
			int c;
			scanf("%d", &c);
			ncs[c]++;
		}
		scanf("%*s");
		memset(visited, 0, sizeof(visited));
#ifdef DEBUG
		printf("%d\n", mix(m, 0, ncs));
#else
		printf("%d\n", mix(m));
#endif
	}
	return 0;
}

