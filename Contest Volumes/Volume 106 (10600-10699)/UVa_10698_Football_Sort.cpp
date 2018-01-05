
/*
	UVa 10698 - Football Sort

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10698_Football_Sort.cpp
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef ONLINE_JUDGE
#define _stricmp strcasecmp
#endif

const int T_max = 28;

struct team_name {
	char name_[15 + 1];
} team_names[T_max];

struct classification {
	int ni_; // name index
	int nr_points_;
	int nr_games_played_;
	int nr_scored_goals_;
	int nr_suffered_goals_;
	int goal_difference_;
} classifications[T_max];

int compare_name(const void* i, const void* j)
{
	const team_name *ni = reinterpret_cast<const team_name*>(i),
		*nj = reinterpret_cast<const team_name*>(j);
	return _stricmp(ni->name_, nj->name_);
}

int compare_team(const void* i, const void* j)
{
	const classification *ci = reinterpret_cast<const classification*>(i),
		*cj = reinterpret_cast<const classification*>(j);
	if (ci->nr_points_ != cj->nr_points_)
		return cj->nr_points_ - ci->nr_points_;
	else if (ci->goal_difference_ != cj->goal_difference_)
		return cj->goal_difference_ - ci->goal_difference_;
	else if(ci->nr_scored_goals_ != cj->nr_scored_goals_)
		return cj->nr_scored_goals_ - ci->nr_scored_goals_;
	else
		return _stricmp(team_names[ci->ni_].name_, team_names[cj->ni_].name_);
}

int main()
{
	bool printed = false;
	while (true) {
		int T, G;
		scanf("%d %d", &T, &G);
		if (!T && !G)
			break;
		if (printed)
			putchar('\n');
		else
			printed = true;

		for (int i = 0; i < T; i++)
			scanf("%s", team_names[i].name_);
		qsort(team_names, T, sizeof(team_name), compare_name);
		for (int i = 0; i < T; i++) {
			classification& c = classifications[i];
			c.ni_ = i;
			c.nr_points_ = c.nr_games_played_ = c.nr_scored_goals_ = c.nr_suffered_goals_ = c.goal_difference_ = 0;
		}
		while (G--) {
			team_name ht, at;
			int hs, as;
			scanf("%s %d - %d %s", ht.name_, &hs, &as, at.name_);
			int hti = reinterpret_cast<team_name*>(bsearch(&ht, team_names, T, sizeof(team_name), compare_name)) - team_names,
				ati = reinterpret_cast<team_name*>(bsearch(&at, team_names, T, sizeof(team_name), compare_name)) - team_names;
			classification& hc = classifications[hti];
			classification& ac = classifications[ati];
			hc.nr_games_played_++; ac.nr_games_played_++;
			if (hs > as)
				hc.nr_points_ += 3;
			else if (hs < as)
				ac.nr_points_ += 3;
			else {
				hc.nr_points_++; ac.nr_points_++;
			}
			hc.nr_scored_goals_ += hs; ac.nr_scored_goals_ += as;
			hc.nr_suffered_goals_ += as; ac.nr_suffered_goals_ += hs;
			hc.goal_difference_ += hs - as; ac.goal_difference_ += as - hs;
		}
		qsort(classifications, T, sizeof(classification), compare_team);
		for (int i = 0; i < T; i++) {
			classification& c = classifications[i];
			if (!i || (c.nr_points_ != classifications[i - 1].nr_points_ ||
				c.goal_difference_ != classifications[i - 1].goal_difference_ ||
				c.nr_scored_goals_ != classifications[i - 1].nr_scored_goals_))
				printf("%2d. ", i + 1);
			else
				printf("    ");
			printf("%15s %3d %3d %3d %3d %3d", team_names[c.ni_].name_, c.nr_points_, c.nr_games_played_,
				c.nr_scored_goals_, c.nr_suffered_goals_, c.goal_difference_);
			if (c.nr_games_played_)
				printf(" %6.2lf\n", (static_cast<double>(c.nr_points_) * 100.0) / (static_cast<double>(c.nr_games_played_) * 3.0));
			else
				puts("    N/A");
		}
	}
	return 0;
}

