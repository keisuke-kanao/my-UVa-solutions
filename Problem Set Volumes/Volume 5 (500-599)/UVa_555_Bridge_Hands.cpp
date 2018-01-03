
/*
	UVa 555 - Bridge Hands

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_555_Bridge_Hands.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int nr_cards = 52, nr_players = 4;

struct card {
	char suit_;
	char rank_;

	bool operator<(const card& c) const;
} cards[nr_players][nr_cards / nr_players];
	// cards[0] are for N, cards[1] are for E, cards[2] are for S, cards[3] are for W
int nr_cards_delivered[nr_players]; // number of cards delivered so far 

int get_suit(char suit)
{
	switch (suit) {
	case 'C':
		return 0;
	case 'D':
		return 1;
	case 'S':
		return 2;
	default:
		return 3;
	}
}

int get_rank(char rank)
{
	switch (rank) {
	case 'T':
		return 8;
	case 'J':
		return 9;
	case 'Q':
		return 10;
	case 'K':
		return 11;
	case 'A':
		return 12;
	default:
		return rank - '2';
	}
}

bool card::operator<(const card& c) const
{
	int s = get_suit(suit_), cs = get_suit(c.suit_);
	if (s < cs)
		return true;
	else if (s > cs)
		return false;
	else
		return get_rank(rank_) < get_rank(c.rank_);
}

void print_cards(card cards[])
{
	for (int i = 0; i < nr_cards / nr_players; i++)
		cout << ' ' << cards[i].suit_ << cards[i].rank_;
	cout << endl;
}

int main()
{
	while (true) {
		char p;
		cin >> p;
		if (p == '#')
			break;
		int pi;
		switch (p) {
		case 'N':
			pi = 1; break;
		case 'E':
			pi = 2; break;
		case 'S':
			pi = 3; break;
		case 'W':
			pi = 0; break;
		}
		for (int i = 0; i < nr_players; i++)
			nr_cards_delivered[i] = 0;
		for (int i = 0; i < nr_cards; i++, pi = (pi + 1) % nr_players) {
			cin >> cards[pi][nr_cards_delivered[pi]].suit_ >> cards[pi][nr_cards_delivered[pi]].rank_;
			nr_cards_delivered[pi]++;
		}
		for (int i = 0; i < nr_players; i++)
			sort(cards[i], cards[i] + nr_cards / nr_players);
		cout << "S:";
		print_cards(cards[2]);
		cout << "W:";
		print_cards(cards[3]);
		cout << "N:";
		print_cards(cards[0]);
		cout << "E:";
		print_cards(cards[1]);
	}
	return 0;
}

