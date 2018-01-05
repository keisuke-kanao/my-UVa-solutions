
/*
	UVa 11088 - End up with More Teams

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11088_End_up_with_More_Teams.cpp
*/

#include <algorithm>
#include <functional>
#include <cstdio>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int n_max = 15, members_max = 3, promising = 20;
int integers[n_max];
int sums[n_max]; // sums[i] is the sum between integers[i] and integers[n - 1]
int members[n_max / members_max]; // members[i] is the number of members of i-th team
int points[n_max / members_max]; // ability points of i-th team

bool more_teams(int n, int m, int ti, int nr_teams, int& max_nr_teams)
{
	if (ti == n) {
		max_nr_teams = max(max_nr_teams, nr_teams);
		return max_nr_teams == m;
	}
	else if (n - ti + nr_teams > max_nr_teams) {
		bool more = false;
		for (int i = 0; i < m; i++)
			if (members[i] < members_max && points[i] + sums[ti] >= promising) {
				more = true;
				members[i]++;
				int nr = nr_teams;
				points[i] += integers[ti];
				if (members[i] == members_max && points[i] >= promising)
					nr++;
				if (more_teams(n, m, ti + 1, nr, max_nr_teams))
					return true;
				members[i]--;
				points[i] -= integers[ti];
			}
		if (!more) {
			max_nr_teams = max(max_nr_teams, nr_teams);
			return max_nr_teams == m;
		}
	}
	return false;
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	for (int cn = 1; ; cn++) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		int m = n / members_max; // number of teams
		for (int i = 0; i < n; i++)
			scanf("%d", &integers[i]);
		for (int i = 0; i < m; i++)
			members[i] = points[i] = 0;
		sort(integers, integers + n, greater<int>());
		for (int i = n - 1, s = 0; i >= 0; i--) {
			s += integers[i];
			sums[i] = s;
		}
		int max_nr_teams = 0;
		more_teams(n, m, 0, 0, max_nr_teams);
		printf("Case %d: %d\n", cn, max_nr_teams);
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

