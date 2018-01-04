
/*
	UVa 181 - Hearts

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_181_Hearts.cpp

	from ACM South Pacific Regionals - 1993, Problem C
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_VV_SouthPac/1993/index.html)
*/

#include <functional>
#include <algorithm>
#include <cstdio>
using namespace std;

enum {s_Clubs, s_Diamonds, s_Hearts, s_Spades};
enum {d_2 = 2, d_3, d_4, d_5, d_6, d_7, d_8, d_9, d_10, d_Jack, d_Queen, d_King, d_Ace};

const int nr_suits = s_Spades - s_Clubs + 1, nr_denominations = d_Ace - d_2 + 1, nr_cards = nr_suits * nr_denominations;
const int nr_players = 5, nr_tricks = 10;
struct card {
	int suit_, denomination_;
} cards[nr_cards], player_cards[nr_players];

const int symbols[] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, d_2, d_3, d_4, d_5, d_6, d_7, d_8, d_9, 0, 0, 0, 0, 0, 0,
	0, d_Ace, 0, s_Clubs, s_Diamonds, 0, 0, 0, s_Hearts, 0, d_Jack, d_King, 0, 0, 0, 0,
	0, d_Queen, 0, s_Spades, d_10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

struct game_suit {
	int nr_denominations_;
	int denominations_[nr_denominations];
} game[nr_players][nr_suits];

int hearts[nr_players];

int get_trump()
{
	card& ci = cards[nr_players * nr_tricks];
	card& cj = cards[nr_players * nr_tricks + 1];
	if (ci.denomination_ < cj.denomination_)
		return cj.suit_;
	else if (ci.denomination_ > cj.denomination_)
		return ci.suit_;
	else
		return max(ci.suit_, cj.suit_);
}

void get_leader_card(int pi, int trump)
{
	int i = -1;
	for (int j = 0; j < nr_suits; j++) {
		game_suit& gsj = game[pi][j];
		if (!gsj.nr_denominations_)
			continue;
		if (i == -1)
			i = j;
		else {
			game_suit& gsi = game[pi][i];
			int di = gsi.denominations_[gsi.nr_denominations_ - 1], dj = gsj.denominations_[gsj.nr_denominations_ - 1];
			if (di < dj)
				i = j;
			else if (di == dj && i != trump)
				i = j;
		}
	}
	game_suit& gs = game[pi][i];
	player_cards[pi].suit_ = i, player_cards[pi].denomination_ = gs.denominations_[--gs.nr_denominations_];
}

void get_follower_card(int pi, int suit, int trump)
{
	int i = -1;
	if (game[pi][suit].nr_denominations_)
		i = suit;
	else if (game[pi][trump].nr_denominations_)
		i = trump;
	else {
		for (int j = 0; j < nr_suits; j++)
			if (j != suit && j != trump && game[pi][j].nr_denominations_) {
				if (i == -1)
					i = j;
				else if (game[pi][i].denominations_[game[pi][i].nr_denominations_ - 1] <=
					game[pi][j].denominations_[game[pi][j].nr_denominations_ - 1])
					i = j;
			}
	}
	game_suit& gs = game[pi][i];
	player_cards[pi].suit_ = i, player_cards[pi].denomination_ = gs.denominations_[--gs.nr_denominations_];
}

int get_winner(int suit, int trump)
{
	int i = -1, ti = -1;
	for (int j = 0; j < nr_players; j++) {
		if (player_cards[j].suit_ == trump) {
			if (ti == -1)
				ti = j;
			else if (player_cards[ti].denomination_ < player_cards[j].denomination_)
				ti = j;
		}
		else if (player_cards[j].suit_ == suit) {
			if (i == -1)
				i = j;
			else if (player_cards[i].denomination_ < player_cards[j].denomination_)
				i = j;
		}
	}
	return (ti != -1) ? ti : i;
}

void print_hearts()
{
	printf("%3d", hearts[nr_players - 1]);
	for (int i = 0; i < nr_players - 1; i++)
		printf("%3d", hearts[i]);
	putchar('\n');
}

int main()
{
	while (true) {
		char s[3];
		scanf("%s", s);
		if (s[0] == '#')
			break;
		cards[0].suit_ = symbols[s[1]], cards[0].denomination_ = symbols[s[0]];
		for (int i = 1; i < nr_cards; i++) {
			scanf("%s", s);
			cards[i].suit_ = symbols[s[1]], cards[i].denomination_ = symbols[s[0]];
		}
		int trump = get_trump();
#ifdef DEBUG
		printf("trump: %d\n", trump);
#endif
		for (int i = 0; i < nr_players; i++) {
			hearts[i] = 0;
			for (int j = 0; j < nr_suits; j++)
				game[i][j].nr_denominations_ = 0;
		}
		for (int i = 0; i < nr_tricks; i++) // deliver the cards to the players
			for (int j = 0; j < nr_players; j++) {
				const card& c = cards[i * nr_players + j];
				game_suit& gs = game[j][c.suit_];
				gs.denominations_[gs.nr_denominations_++] = c.denomination_;
			}
		for (int i = 0; i < nr_players; i++)
			for (int j = 0; j < nr_suits; j++) {
#ifdef DEBUG
				printf("player: %d suit: %d demoninations: ", i, j);
#endif
				game_suit& gs = game[i][j];
				sort(gs.denominations_, gs.denominations_ + gs.nr_denominations_);
#ifdef DEBUG
				if (gs.nr_denominations_)
					for (int k = 0; k < gs.nr_denominations_; k++)
						printf("%d%c", gs.denominations_[k], ((k < gs.nr_denominations_ - 1) ? ' ' : '\n'));
				else
					putchar('\n');
#endif
			}
		int leader = 0;
		for (int i = 0; i < nr_tricks; i++) {
			get_leader_card(leader, trump);
#ifdef DEBUG
			printf("trick %d\n  player: %d suit: %d demonination: %d\n", i + 1,
				leader, player_cards[leader].suit_, player_cards[leader].denomination_);
#endif
			int suit = player_cards[leader].suit_;
			for (int j = 0; j < nr_players; j++)
				if (j != leader) {
					get_follower_card(j, suit, trump);
#ifdef DEBUG
					printf("  player: %d suit: %d demonination: %d\n",
						j, player_cards[j].suit_, player_cards[j].denomination_);
#endif
				}
			int winner = get_winner(suit, trump);
			for (int j = 0; j < nr_players; j++)
				if (player_cards[j].suit_ == s_Hearts)
					hearts[winner] += player_cards[j].denomination_;
			leader = winner;
#ifdef DEBUG
		print_hearts();
#endif
		}
		print_hearts();
	}
	return 0;
}

