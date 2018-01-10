
/*
	UVa 131 - The Psychic Poker Player

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_131_The_Psychic_Poker_Player.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cstring>
using namespace std;

const int nr_cards = 5; // number of cards per hand
const char card_values[] = "23456789TJQKA";
const char card_suits[] = "CDHS";

int convert_card_to_number(char value, char suit)
{
	int number = 0;
	// a value is converted to the tenths and ones digits between 0 and 12
	for (int i = 0; i < sizeof(card_values) / sizeof(char) - 1; i++)
		if (card_values[i] == value)
			number = i;
	// a suit is converted to the hundreds digit between 0 ant 3
	for (int i = 0; i < sizeof(card_suits) / sizeof(char) - 1; i++)
		if (card_suits[i] == suit)
			number += i * 100;
	return number;
}

inline int card_number(int card)
{
	return card % 100;
}

inline int card_suit(int card)
{
	return card / 100;
}

void read_cards(istringstream& iss, int cards[])
{
	for (int i = 0; i < nr_cards; i++) {
		char value, suit;
		iss >> value >> suit;
		cards[i] = convert_card_to_number(value, suit);
	}
}

void print_cards(const int cards[])
{
	for (int i = 0; i < nr_cards; i++)
		cout << ' ' << card_values[card_number(cards[i])] << card_suits[card_suit(cards[i])];
}


bool is_pair(const int cards[])
{
/*
	Pair. Two of the five cards in the hand have the same value. Hands which both contain
	a pair are ranked by the value of the cards forming the pair. If these values are
	the same, the hands are ranked by the values of the cards not forming the pair,
	in decreasing order.
*/
	for (int i = 0; i < nr_cards - 1; i++)
		if (card_number(cards[i]) == card_number(cards[i + 1])) // a pair is found
			return true;
	return false;
}

bool is_two_pairs(const int cards[])
{
/*
	Two Pairs. The hand contains two different pairs. Hands which both contain two pairs
	are ranked by the value of their highest pair. Hands with the same highest pair
	are ranked by the value of their other pair. If these values are the same the hands
	are ranked by the value of the remaining card.
*/
	for (int i = 0; i < nr_cards - 1; i++)
		if (card_number(cards[i]) == card_number(cards[i + 1])) {
			for (int j = i + 2; j < nr_cards - 1; j++)
				if (card_number(cards[j]) == card_number(cards[j + 1])) {
					return true;
				}
		}
	return false;
}

bool is_three_of_a_kind(const int cards[])
{
/*
	Three of a Kind. Three of the cards in the hand have the same value. Hands which
	both contain three of a kind are ranked by the value of the three cards.
*/
	for (int i = 0; i < nr_cards - 2; i++)
		if (card_number(cards[i]) == card_number(cards[i + 1]) && card_number(cards[i + 1]) == card_number(cards[i + 2]))
			return true;
	return false;
}

bool is_straight(const int cards[])
{
/*
	Straight. Hand contains five cards with consecutive values. Hands which both contain
	a straight are ranked by their highest card.
*/
	for (int i = 0; i < nr_cards - 1; i++)
		if (card_number(cards[i]) != card_number(cards[i + 1]) + 1) {
			if (card_number(cards[0]) == 12) { // special case of '5 4 3 2 A'
				for (int j = 0; j < nr_cards - 1; j++)
					if (card_number(cards[j + 1]) != 3 - j)
						return false;
				return true;
			}
			else
				return false;
		}
	return true;
}

bool is_flush(const int cards[])
{
/*
	Flush. Hand contains five cards of the same suit. Hands which are both flushes are
	ranked using the rules for High Card.
*/
	for (int i = 0; i < nr_cards - 1; i++)
		if (card_suit(cards[i]) != card_suit(cards[i + 1]))
			return false;
	return true;
}

bool is_full_house(const int cards[])
{
/*
	Full House. Three cards of the same value, with the remaining two cards forming a
	pair. Ranked by the value of the three cards.
*/
	if (card_number(cards[0]) != card_number(cards[1]))
		return false;
	if (card_number(cards[1]) == card_number(cards[2])) { // the first three cards have the same values
		if (card_number(cards[3]) == card_number(cards[4]))
			return true;
		else
			return false;
	}
	else { // the first two cards have the same values
		if (card_number(cards[2]) == card_number(cards[3]) && card_number(cards[3]) == card_number(cards[4]))
			return true;
		else
			return false;
	}
}

bool is_four_of_a_kind(const int cards[])
{
/*
	Four of a Kind. Four cards with the same value. Ranked by the value of the four
	cards.
*/
	int j = (card_number(cards[0]) == card_number(cards[1])) ? nr_cards  - 2 : nr_cards  - 1;
	for (int i = 1; i < j; i++)
		if (card_number(cards[i]) != card_number(cards[i + 1]))
			return false;
	return true;
}

bool is_straight_flash(const int cards[])
{
/*
	Straight Flush. Five cards of the same suit with consecutive values. Ranked by the
	highest card in the hand.
*/
	// five cards of the same suit with consecutive values
	for (int i = 0; i < nr_cards - 1; i++)
		if (card_number(cards[i]) != card_number(cards[i + 1]) + 1 || card_suit(cards[i]) != card_suit(cards[i + 1])) {
			if (card_number(cards[0]) == 12) { // special case of '5 4 3 2 A'
				int suit = card_suit(cards[0]);
				for (int j = 0; j < nr_cards - 1; j++)
					if (card_number(cards[j + 1]) != 3 - j || card_suit(cards[j + 1]) != suit)
						return false;
				return true;
			}
			else
				return false;
		}
	return true;
}

bool compare_card_number(int i, int j)
{
	return (i % 100) > (j % 100); // compare the numbers with their tenths digit and ones digit in descending order
}

enum hand_ranks { // hand ranks in descending order
	straight_flash, four_of_a_kind, full_house, flush, straight, three_of_a_kind, two_pairs, pair, high_card
};

int get_hand_rank(int cards[])
{
	// sort the cards by decreasing order of their tenths ans ones digits
	sort(cards, cards + nr_cards, compare_card_number);
	typedef bool (*HAND_RANK_FUNCTION)(const int cards[]);
	const HAND_RANK_FUNCTION hand_rank_functions[] = {
		is_straight_flash, is_four_of_a_kind, is_full_house, is_flush,
		is_straight, is_three_of_a_kind, is_two_pairs, is_pair
	};
	int rank;
	for (rank = straight_flash; rank < high_card; rank++)
		if (hand_rank_functions[rank](cards)) // the functions are called in the descending order of their ranks
			return rank;
/*
	High Card. Hands which do not fit any higher category are ranked by the value of
	their highest card. If the highest cards have the same value, the hands are ranked
	by the next highest, and so on.
*/
	return rank;
}

const int c_5_1[][nr_cards] = { // 1-combination of 5 cards
	{0}, {1}, {2}, {3}, {4}
};
const int c_5_2[][nr_cards] = { // 2-combination of 5 cards
	{0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}
};
const int c_5_3[][nr_cards] = { // 3-combination of 5 cards
	{0, 1, 2}, {0, 1, 3}, {0, 1, 4}, {0, 2, 3}, {0, 2, 4}, {0, 3, 4}, {1, 2, 3}, {1, 2, 4}, {1, 3, 4}, {2, 3, 4}
};
const int c_5_4[][nr_cards] = { // 4-combination of 5 cards
	{0, 1, 2, 3}, {0, 1, 2, 4}, {0, 1, 3, 4}, {0, 2, 3, 4}, {1, 2, 3, 4}
};

struct card_combination {
	int length_; // number of combinations
	int nr_indices_; // number of indices in each combination
	const int (*indices_)[nr_cards]; // array of indices
};

const card_combination card_combinations[] = {
	{5, 1, c_5_1}, {10, 2, c_5_2}, {10, 3, c_5_3}, {5, 4, c_5_4}
};

const char* hand_rank_strings[] = {
	"straight-flush", "four-of-a-kind", "full-house", "flush",
	"straight", "three-of-a-kind", "two-pairs", "one-pair", "highest-card"
};

int main()
{
	string line;
	while (getline(cin, line)) {
		// read the initial hand and the top five cards on the deck
		istringstream iss(line);
		int initial_cards[nr_cards], deck_cards[nr_cards];
		read_cards(iss, initial_cards);
		read_cards(iss, deck_cards);
		int cards[nr_cards];
		memcpy(cards, initial_cards, sizeof(int) * nr_cards);
		int highest_rank = get_hand_rank(cards); // calculate the rank of initial hand
		// calculate the rank of hands in which some cards are chosen from the initial cards and 
		// the rest of them are taken from the deck
		for (int i = 0; i < sizeof(card_combinations) / sizeof(card_combination); i++) {
			const card_combination& cmb = card_combinations[i];
			for (int j = 0; j < cmb.length_; j++) {
				int k = 0;
				for ( ; k < cmb.nr_indices_; k++) // select cmb.nr_indices_ cards from initial_cards
					cards[k] = initial_cards[cmb.indices_[j][k]];
				for (int l = 0; k + l < nr_cards; l++) // get the rest of cards from deck_cards
					cards[k + l] = deck_cards[l];
				highest_rank = min(highest_rank, get_hand_rank(cards));
			}
		}
		memcpy(cards, deck_cards, sizeof(int) * nr_cards);
		highest_rank = min(highest_rank, get_hand_rank(cards)); // calculate the rank of deck hand
		cout << "Hand:";
		print_cards(initial_cards);
		cout << " Deck:";
		print_cards(deck_cards);
		cout << " Best hand: " << hand_rank_strings[highest_rank] << endl;
	}
	return 0;
}

