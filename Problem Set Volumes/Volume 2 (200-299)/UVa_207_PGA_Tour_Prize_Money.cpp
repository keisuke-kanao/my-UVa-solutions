
/*
	UVa 207 - PGA Tour Prize Money

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_207_PGA_Tour_Prize_Money.cpp

	This is an accepted solution.
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <limits>
using namespace std;

const int infinite = numeric_limits<int>::max() / 2;
const int nr_purses = 70;
double total_purse, purses[nr_purses], prizes[nr_purses];
const int nr_rounds = 4, nr_players_max = 144, nr_chars_player_max = 20, nr_chars_line_max = 33;
char player_names[nr_players_max][nr_chars_player_max + 1];
int nr_players;
struct player {
	int i_;
	int amateur_;
	int rd_[nr_rounds], first_, total_;
	int place_;
	bool tie_, prized_;
	double prize_;
} players[nr_players_max];

bool compare_by_first(const player& i, const player& j)
{
	if (i.first_ < j.first_)
		return true;
	else if (i.first_ > j.first_)
		return false;
	else
		return strcmp(player_names[i.i_], player_names[j.i_]) < 0;
}

bool compare_by_total(const player& i, const player& j)
{
	if (i.total_ < j.total_)
		return true;
	else if (i.total_ > j.total_)
		return false;
	else if (i.total_ < infinite && j.total_ < infinite)
		return strcmp(player_names[i.i_], player_names[j.i_]) < 0;
	else if (i.first_ + i.rd_[2] < j.first_ + j.rd_[2])
		return true;
	else if (i.first_ + i.rd_[2] > j.first_ + j.rd_[2])
		return false;
	else
		return strcmp(player_names[i.i_], player_names[j.i_]) < 0;
}

int main()
{
	int nr_cases;
	scanf("%d", &nr_cases);
	while (nr_cases--) {
		scanf("%lf", &total_purse);
		for (int i = 0; i < nr_purses; i++) {
			scanf("%lf", &purses[i]);
			prizes[i] = purses[i] / 100.0 * total_purse;
		}
		int nr;
		scanf("%d", &nr);
		while (getchar() != '\n')
			;
		nr_players = 0;
		while (nr--) {
			char line[nr_chars_line_max + 1];
			fgets(line, nr_chars_line_max + 1, stdin);
			memcpy(player_names[nr_players], line, nr_chars_player_max);
			player& p = players[nr_players];
			p.i_ = nr_players;
			const char* pn = &player_names[nr_players][nr_chars_player_max - 1];
			while (*pn == ' ')
				pn--;
			p.amateur_ = (*pn == '*') ? 1 : 0;
			p.rd_[0] = p.rd_[1] = p.rd_[2] = p.rd_[3] = p.first_ = p.total_ = infinite;
			for (int i = 0; i < nr_rounds; i++) {
				char rd[3];
				sscanf(line + 20 + i * 3, "%s", rd);
				if (rd[0] == 'D') // "DQ"
					break;
				p.rd_[i] = atoi(rd);
			}
			if (p.rd_[0] != infinite && p.rd_[1] != infinite) {
				p.first_ = p.rd_[0] + p.rd_[1];
				if (p.rd_[2] != infinite && p.rd_[3] != infinite)
					p.total_ = p.first_ + p.rd_[2] + p.rd_[3];
				p.tie_ = p.prized_ = false, p.prize_ = 0.0;
				nr_players++;
			}
		}
		sort(players, players + nr_players, compare_by_first);
		if (nr_players > nr_purses) { // cut the number of players to 70 with ties
			nr = nr_purses;
			while (nr < nr_players && players[nr].first_ == players[nr_purses - 1].first_)
				nr++;
			nr_players = nr;
		}
		sort(players, players + nr_players, compare_by_total);
		for (int i = 0, place = 1; i < nr_players && players[i].total_ < infinite; ) {
			players[i].place_ = place;
			int j;
			for (j = i + 1; j < nr_players && players[j].total_ == players[i].total_; j++)
				players[j].place_ = place;
			place += j - i;
			i = j;
		}
		for (int i = 0, j = 0; i < nr_players && j < nr_purses && players[i].total_ < infinite; ) {
			if (players[i].amateur_) {
				i++;
				continue;
			}
			double prize = prizes[j];
			int ci = 1, cp = 1, cj = 1;
			for ( ; i + ci < nr_players && players[i + ci].total_ == players[i].total_; ci++)
				if (!players[i + ci].amateur_) {
					cp++;
					if (j + cj < nr_purses)
						prize += prizes[j + cj++];
				}
			for (int k = 0; k < ci; k++)
				if (!players[i + k].amateur_)
					players[i + k].tie_ = cp > 1, players[i + k].prized_ = true, players[i + k].prize_ = prize / cp;
			i += ci, j += cj;
		}
		printf("Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n"
			"-----------------------------------------------------------------------\n");
		for (int i = 0; i < nr_players; i++) {
			const player& p = players[i];
			printf("%-21s", player_names[p.i_]);
			if (p.total_ == infinite)
				printf("          ");
			else {
				char s[5];
            	sprintf(s, "%d%c", p.place_, ((p.tie_) ? 'T' : ' '));
				printf("%-10s", s);
			}
			printf("%-5d%-5d", p.rd_[0], p.rd_[1]);
			if (p.rd_[2] != infinite) {
				printf("%-5d", p.rd_[2]);
				if (p.rd_[3] != infinite) {
					if (p.amateur_ || !p.prized_)
						printf("%-5d%d\n", p.rd_[3], p.total_);
					else
						printf("%-5d%-10d$%9.2lf\n", p.rd_[3], p.total_, p.prize_);
				}
				else
					printf("     DQ\n");
			}
			else
				printf("          DQ\n");
		}
		if (nr_cases)
			putchar('\n');
	}
	return 0;
}

