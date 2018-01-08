
/*
	UVa 127 - "Accordian" Patience

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_127_Accordian_Patience.cpp
*/

#include <iostream>
#include <stack>
#include <list>
#include <iterator>
using namespace std;

const int nr_cards = 52; // number of cards

typedef pair<char, char> card;
	// first field is rank, second field is suit

bool are_cards_matched(const stack<card>& i, const stack<card>& j)
{
	const card& ci = i.top(), cj = j.top();
	return ci.first == cj.first || ci.second == cj.second;
}

void pile_card(list< stack<card> >::iterator left, list< stack<card> >::iterator current)
// pile the top card of current on left
{
	left->push(current->top()); current->pop();
}

int accordian_patience(list< stack<card> >& cards)
{
	int nr_piles = nr_cards;
	list< stack<card> >::iterator three_left = cards.begin(), one_left, current = cards.begin(), e = cards.end();
	int nr_left = 0; // number of cards left to the current
	while (current != e) {
		if (nr_left >= 3 && // there are at least three cards left to the current
			are_cards_matched(*three_left, *current)) {
			// pile and move the current card three positions to the left
			pile_card(three_left, current);
			if (current->empty()) {
				cards.erase(current);
				nr_piles--;
			}
			one_left = current = three_left;
			nr_left -= 3;
			if (nr_left)
				--one_left;
				three_left = current;
			if (nr_left >= 3)
				advance(three_left, -3);
			else
				three_left = cards.begin();
		}
		else if (nr_left >= 1 &&  // there are at least three cards left to the current
			are_cards_matched(*one_left, *current)) {
			// pile and move the current card one position to the left
			pile_card(one_left, current);
			if (current->empty()) {
				cards.erase(current);
				nr_piles--;
			}
			current = one_left;
			if (--nr_left)
				--one_left;
			if (nr_left >= 3)
				--three_left;
		}
		else {
			if (++nr_left > 3)
				++three_left;
			one_left = current++;
		}
#ifdef DEBUG
		for (list< stack<card> >::const_iterator i = cards.begin(); i != e; ++i) {
			cerr << i->top().first << i->top().second << '(' << i->size() << ") ";
			if (i == current)
				break; 
		}
		cerr << endl;
#endif
	}
	return nr_piles;
}

int main()
{
	while (true) {
		char value, suit;
		cin >> value;
		if (value == '#')
			break;
		cin >> suit;
		list< stack<card> > cards(nr_cards);
		list< stack<card> >::iterator i = cards.begin();
		i->push(make_pair(value, suit));
		++i;
		for (list< stack<card> >::iterator e = cards.end(); i != e; ++i) {
			cin >> value >> suit;
			i->push(make_pair(value, suit));
		}
		int nr_piles = accordian_patience(cards);
		if (nr_piles > 1)
			cout << nr_piles << " piles remaining:";
		else
			cout << "1 pile remaining:";
		for (list< stack<card> >::const_iterator i = cards.begin(), e = cards.end(); i != e; ++i)
			cout << ' ' << i->size();
		cout << endl;
	}
	return 0;
}

