
/*
	UVa 12667 - Last Blood

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12667_Last_Blood.cpp
*/

#include <cstdio>

const int n_max = 12, t_max = 100;

struct {
	int time_, team_id_;
} last_accepted[n_max];

bool accepted[n_max][t_max + 1];

int main()
{
	int n, t, m;
	scanf("%d %d %d", &n, &t, &m);
	for (int i = 0; i < n; i++)
		last_accepted[i].time_ = -1;
	while (m--) {
		int time, team_id;
		char problem[2], verdict[4];
		scanf("%d %d %s %s", &time, &team_id, problem, verdict);
		int p = problem[0] - 'A';
		if (verdict[0] == 'Y' && !accepted[p][team_id]) {
			accepted[p][team_id] = true;
			last_accepted[p].time_ = time, last_accepted[p].team_id_ = team_id;
		}
	}
	for (int i = 0; i < n; i++) {
		printf("%c ", 'A' + i);
		if (last_accepted[i].time_ != -1)
			printf("%d %d\n", last_accepted[i].time_, last_accepted[i].team_id_);
		else
			puts("- -");
	}
	return 0;
}

