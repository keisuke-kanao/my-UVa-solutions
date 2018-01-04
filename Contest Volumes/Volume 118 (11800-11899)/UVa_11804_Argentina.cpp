
/*
	UVa 11804 - Argentina

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11804_Argentina.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_name_chars_max = 31;
const int nr_players = 10, nr_attackers = 5, nr_defenders = 5;
struct player {
	char name_[nr_name_chars_max + 1];
	int attacking_, defending_;

	bool operator<(const player& p) const {return strcmp(name_, p.name_) < 0;}
} players[nr_players];

int max_attacking, max_defending;
bool attackers[nr_players], defenders[nr_players];
bool decided_attackers[nr_players], decided_defenders[nr_players];

void decision(int ni, int ai, int di, int attacking, int defending)
{
	if (ni == nr_players) {
		if (attacking > max_attacking || attacking == max_attacking && defending > max_defending) {
			max_attacking = attacking;
			max_defending = defending;
			memcpy(decided_attackers, attackers, sizeof(decided_attackers));
			memcpy(decided_defenders, defenders, sizeof(decided_defenders));
		}
	}
	else {
		if (ai < nr_attackers) {
			attackers[ni] = true;
			decision(ni + 1, ai + 1, di, attacking + players[ni].attacking_, defending);
			attackers[ni] = false;
		}
		if (di < nr_defenders) {
			defenders[ni] = true;
			decision(ni + 1, ai, di + 1, attacking, defending +  + players[ni].defending_);
			defenders[ni] = false;
		}
	}
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int cn = 1; cn <= t; cn++) {
		for (int i = 0; i < nr_players; i++)
			scanf("%s %d %d", players[i].name_, &players[i].attacking_, &players[i].defending_);
		sort(players, players + nr_players);
		memset(attackers, 0, sizeof(attackers));
		memset(defenders, 0, sizeof(defenders));
		max_attacking = max_defending = 0;
		decision(0, 0, 0, 0, 0);
		printf("Case %d:\n", cn);
		for (int i = 0, j = 0; j < nr_attackers; i++)
			if (decided_attackers[i]) {
				printf("%c%s%c", ((j) ? ' ' : '('), players[i].name_, ((j == nr_attackers - 1) ? ')' : ','));
				j++;
			}
		putchar('\n');
		for (int i = 0, j = 0; j < nr_defenders; i++)
			if (decided_defenders[i]) {
				printf("%c%s%c", ((j) ? ' ' : '('), players[i].name_, ((j == nr_defenders - 1) ? ')' : ','));
				j++;
			}
		putchar('\n');
	}
	return 0;
}

