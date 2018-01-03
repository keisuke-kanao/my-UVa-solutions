
/*
	UVa 647 - Chutes and Ladders

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_647_Chutes_and_Ladders.cpp

	from ACM Pacific Northwest Regionals 1998
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_PacNW/1998/index.html)
*/

#include <cstdio>

const int nr_dice_max = 1000;
int nr_dice, dice[nr_dice_max + 1];
const int nr_squares = 100;

struct square {
	int chute_ladder_; // end of chute_ladder
	int turn_; // loss-a-turn for -1, extra-turn for 1
} squares[nr_squares + 1];

int main()
{
	const int nr_players_max = 6;
	while (true) {
		scanf("%d", &dice[nr_dice]);
		if (dice[nr_dice])
			nr_dice++;
		else
			break;
	}
	while (true) {
		int nr_players, players[nr_players_max];
		bool loss_turns[nr_players_max]; // true if loss-turn
		scanf("%d", &nr_players);
		if (!nr_players)
			break;
		for (int i = 0; i < nr_players; i++) {
			players[i] = 0;
			loss_turns[i] = false;
		}
		for (int i = 1; i <= nr_squares; i++)
			squares[i].chute_ladder_ = squares[i].turn_ = 0;
		while (true) {
			int start, end;
			scanf("%d %d", &start, &end);
			if (!start && !end)
				break;
			squares[start].chute_ladder_ = end;
		}
		while (true) {
			int turn;
			scanf("%d", &turn);
			if (!turn)
				break;
			if (turn < 0)
				squares[-turn].turn_ = -1;
			else
				squares[turn].turn_ = 1;
		}
		int pi = 0;
		for (int i = 0; i < nr_dice; i++) {
			while (loss_turns[pi]) {
				loss_turns[pi] = false;
				pi = (pi + 1) % nr_players;
			}
			if (players[pi] + dice[i] > nr_squares)
				pi = (pi + 1) % nr_players;
			else {
				players[pi] += dice[i];
				int p = players[pi], c, t;
				if (p == nr_squares)
					break;
				if (c = squares[p].chute_ladder_)
					players[pi] = c;
				if (t = squares[p].turn_) {
					if (t == -1) {
						loss_turns[pi] = true;
						pi = (pi + 1) % nr_players;
					}
				}
				else
					pi = (pi + 1) % nr_players;
			}
		}
		printf("%d\n", pi + 1);
	}
}

