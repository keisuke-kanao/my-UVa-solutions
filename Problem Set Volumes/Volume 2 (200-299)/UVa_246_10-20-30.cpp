
/*
	UVa 246 - 10-20-30

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_246_10-20-30.cpp

	An accepted solution.
*/

#include <iostream>
#include <deque>
#include <set>
#include <cstring>
using namespace std;

const int nr_cards = 52, nr_piles = 7;

struct state {
	char cards_[nr_cards + nr_piles + 1 + 1];
	bool operator<(const state& s) const {return strcmp(cards_, s.cards_) < 0;}
};

void play(deque<int>& pile, deque<int>& cards)
{
	pile.push_back(cards.front()); cards.pop_front();
	while (true) {
		size_t s = pile.size();
		if (s < 3)
			break;
		if (!((pile[0] + pile[1] + pile[s - 1]) % 10)) { // the first two and last one
			cards.push_back(pile[0]);
			cards.push_back(pile[1]);
			cards.push_back(pile[s - 1]);
			pile.pop_front();
			pile.pop_front();
			pile.pop_back();
		}
		else if (!((pile[0] + pile[s - 2] + pile[s - 1]) % 10)) { // the first one and the last two
			cards.push_back(pile[0]);
			cards.push_back(pile[s - 2]);
			cards.push_back(pile[s - 1]);
			pile.pop_front();
			pile.pop_back();
			pile.pop_back();
		}
		else if (!((pile[s - 3] + pile[s - 2] + pile[s - 1]) % 10)) { // the last three cards
			cards.push_back(pile[s - 3]);
			cards.push_back(pile[s - 2]);
			cards.push_back(pile[s - 1]);
			pile.pop_back();
			pile.pop_back();
			pile.pop_back();
		}
		else
			break;
	}
}

int insert_state(const deque<int> piles[], const deque<int>& cards, set<state>& states)
{
	if (cards.empty())
		return 1; // loose
	state s;
	int si = 0;
	bool win = true;
	for (int pi = 0; pi < nr_piles; pi++) {
		const deque<int>& p = piles[pi];
		if (!p.empty()) {
			win = false;
			for (size_t ci = 0, ce = p.size(); ci < ce; ci++, si++)
				s.cards_[si] = p[ci] + '0';
		}
		s.cards_[si++] = '0'; // terminator
	}
	if (win)
		return 2; // win
	for (size_t ci = 0, ce = cards.size(); ci < ce; ci++, si++)
		s.cards_[si] = cards[ci] + '0';
	s.cards_[si++] = '0'; // terminator
	s.cards_[si] = '\0';
	pair<set<state>::iterator, bool> result = states.insert(s);
	return (result.second) ? -1 : 0 /* draw */;
}

int main()
{
	while (true) {
		int c;
		cin >> c;
		if (!c)
			break;
		deque<int> cards;
		deque<int> piles[nr_piles];
		piles[0].push_back(c);
		int i;
		for (i = 1; i < nr_piles; i++) {
			cin >> c;
			piles[i].push_back(c);
		}
		for ( ; i < nr_cards; i++) {
			cin >> c;
			cards.push_back(c);
		}
		int nr_dealt = nr_piles, pi = 0, npi, result;
		set<state> states;
		insert_state(piles, cards, states);
		while (true) {
			nr_dealt++;
			play(piles[pi], cards);
			if ((result = insert_state(piles, cards, states)) != -1)
				break;
			for (pi = (pi + 1) % nr_piles; piles[pi].empty(); pi = (pi + 1) % nr_piles)
				; // locate the next pile where the next card will be played
		}
		switch (result) {
		case 0:
			cout << "Draw: "; break;
		case 1:
			cout << "Loss: "; break;
		case 2:
			cout << "Win : "; break;
		}
		cout << nr_dealt << endl;
	}
	return 0;
}

