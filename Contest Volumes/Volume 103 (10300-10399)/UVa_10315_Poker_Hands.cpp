
/*
	2.8.2 Poker Hands
	PC/UVa IDs: 110202/10315, Popularity: C, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10315_Poker_Hands.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

const int number_of_cards = 5; // number of cards per hand
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

istringstream& read_cards(istringstream& iss, int cards[])
{
	for (int i = 0; i < number_of_cards; i++) {
		char value, suit;
		iss >> value >> suit;
		cards[i] = convert_card_to_number(value, suit);
	}
	return iss;
}

bool is_pair(int cards[],
	int iranks[] /* array of cards used to rank the same hands */, int& niranks /* number of cards in iranks[] */)
{
/*
	Pair. Two of the five cards in the hand have the same value. Hands which both contain
	a pair are ranked by the value of the cards forming the pair. If these values are
	the same, the hands are ranked by the values of the cards not forming the pair,
	in decreasing order.
*/
	for (int i = 0; i < number_of_cards - 1; i++)
		if (card_number(cards[i]) == card_number(cards[i + 1])) { // a pair is found
			iranks[0] = cards[i];
			for (int j = 0, k = 1; j < number_of_cards; j++) {
				if (j == i || j == i + 1)
					continue;
				iranks[k++] = cards[j]; // the rest are ranked by their value
			}
			niranks = 4;
			return true;
		}
	return false;
}

bool is_two_pairs(int cards[], int iranks[], int& niranks)
{
/*
	Two Pairs. The hand contains two different pairs. Hands which both contain two pairs
	are ranked by the value of their highest pair. Hands with the same highest pair
	are ranked by the value of their other pair. If these values are the same the hands
	are ranked by the value of the remaining card.
*/
	for (int i = 0; i < number_of_cards - 1; i++)
		if (card_number(cards[i]) == card_number(cards[i + 1])) {
			for (int j = i + 2; j < number_of_cards - 1; j++)
				if (card_number(cards[j]) == card_number(cards[j + 1])) {
					iranks[0] = cards[i]; iranks[1] = cards[j];
					for (int k = 0; k < number_of_cards; k++)
						if (k != i && k != i + 1 && k != j && k != j + 1) {
							iranks[2] = cards[k];
							break;
						}
					niranks = 3;
					return true;
				}
		}
	return false;
}

bool is_three_of_a_kind(int cards[], int iranks[], int& niranks)
{
/*
	Three of a Kind. Three of the cards in the hand have the same value. Hands which
	both contain three of a kind are ranked by the value of the three cards.
*/
	for (int i = 0; i < number_of_cards - 2; i++)
		if (card_number(cards[i]) == card_number(cards[i + 1]) && card_number(cards[i + 1]) == card_number(cards[i + 2])) {
			iranks[0] = cards[i]; niranks = 1;
			return true;
		}
	return false;
}

bool is_straight(int cards[], int iranks[], int& niranks)
{
/*
	Straight. Hand contains five cards with consecutive values. Hands which both contain
	a straight are ranked by their highest card.
*/
	for (int i = 0; i < number_of_cards - 1; i++)
		if (card_number(cards[i]) != card_number(cards[i + 1]) + 1)
			return false;
	iranks[0] = cards[0]; niranks = 1;
	return true;
}

bool is_flush(int cards[], int iranks[], int& niranks)
{
/*
	Flush. Hand contains five cards of the same suit. Hands which are both flushes are
	ranked using the rules for High Card.
*/
	for (int i = 0; i < number_of_cards - 1; i++)
		if (card_suit(cards[i]) != card_suit(cards[i + 1]))
			return false;
	for (int i = 0; i < number_of_cards; i++)
		iranks[i] = cards[i];
	niranks = number_of_cards;
	return true;
}

bool is_full_house(int cards[], int iranks[], int& niranks)
{
/*
	Full House. Three cards of the same value, with the remaining two cards forming a
	pair. Ranked by the value of the three cards.
*/
	if (card_number(cards[0]) != card_number(cards[1]))
		return false;
	if (card_number(cards[1]) == card_number(cards[2])) { // the first three cards have the same values
		if (card_number(cards[3]) == card_number(cards[4])) {
			iranks[0] = cards[0]; niranks = 1;
			return true;
		}
		else
			return false;
	}
	else { // the first two cards have the same values
		if (card_number(cards[2]) == card_number(cards[3]) && card_number(cards[3]) == card_number(cards[4])) {
			iranks[0] = cards[2]; niranks = 1;
			return true;
		}
		else
			return false;
	}
}

bool is_four_of_a_kind(int cards[], int iranks[], int& niranks)
{
/*
	Four of a Kind. Four cards with the same value. Ranked by the value of the four
	cards.
*/
	int j = (card_number(cards[0]) == card_number(cards[1])) ? number_of_cards  - 2 : number_of_cards  - 1;
	for (int i = 1; i < j; i++)
		if (card_number(cards[i]) != card_number(cards[i + 1]))
			return false;
	iranks[0] = (j == number_of_cards  - 2) ? cards[0] : cards[1]; niranks = 1;
	return true;
}

bool is_straight_flash(int cards[], int iranks[], int& niranks)
{
/*
	Straight Flush. Five cards of the same suit with consecutive values. Ranked by the
	highest card in the hand.
*/
	// five cards of the same suit with consecutive values
	for (int i = 0; i < number_of_cards - 1; i++)
		if (card_number(cards[i]) != card_number(cards[i + 1]) + 1 || card_suit(cards[i]) != card_suit(cards[i + 1]))
			return false;
	iranks[0] = cards[0]; niranks = 1;
	return true;
}

enum hand_ranks { // hand ranks in descending order
	straight_flash, four_of_a_kind, full_house, flush, straight, three_of_a_kind, two_pairs, pair, high_card
};

int get_hand_rank(int cards[], int iranks[], int& niranks)
{
	typedef bool (*HAND_RANK_FUNCTION)(int cards[], int iranks[], int& niranks);
	const HAND_RANK_FUNCTION hand_rank_functions[] = {
		is_straight_flash, is_four_of_a_kind, is_full_house, is_flush,
		is_straight, is_three_of_a_kind, is_two_pairs, is_pair
	};
	int rank;
	for (rank = straight_flash; rank < high_card; rank++)
		if (hand_rank_functions[rank](cards, iranks, niranks)) // the functions are called in the descending order of their ranks
			return rank;
/*
	High Card. Hands which do not fit any higher category are ranked by the value of
	their highest card. If the highest cards have the same value, the hands are ranked
	by the next highest, and so on.
*/
	for (int i = 0; i < number_of_cards; i++)
		iranks[i] = cards[i];
	niranks = number_of_cards;
	return rank;
}

int compare_hand_ranks(int b_iranks[], int w_iranks[], int niranks) // compare card nummbers in cases when two hands are the same rank
{
	for (int i = 0; i < niranks; i++) {
		if (card_number(b_iranks[i]) > card_number(w_iranks[i]))
			return 1;
		else if (card_number(b_iranks[i]) < card_number(w_iranks[i]))
			return -1;
	}
	return 0;
}

bool compare_card_number(int i, int j)
{
	return (i % 100) > (j % 100); // compare the numbers with their tenths digit and ones digit in descending order
}

#ifdef DEBUG

const char* hand_rank_strings[] = {
	"straight flash", "four of a kind", "full house", "flush",
	"straight", "three of a kind", "two pairs", "pair", "high card"
};

string convert_to_string(int card)
{
	string s;
	s = card_values[card_number(card)];
	return s + card_suits[card_suit(card)];
}

ostream& write_cards(ostream& out, int cards[])
{
	for (int i = 0; i < number_of_cards; i++)
		out << convert_to_string(cards[i]) << ' ';
	return out;
}

#endif

int main(int /* argc */, char** /* argv */)
{
	string line;
	while (getline(cin, line)) {
		istringstream iss(line);
		int b_cards[number_of_cards], w_cards[number_of_cards];
		read_cards(iss, b_cards);
		read_cards(iss, w_cards);
		// the cards of each hand are sorted by the decreasing order of their tenths ans ones digits
		sort(b_cards, b_cards + number_of_cards, compare_card_number);
		sort(w_cards, w_cards + number_of_cards, compare_card_number);
		int b_iranks[number_of_cards], b_niranks;
		int b_rank = get_hand_rank(b_cards, b_iranks, b_niranks);
		int w_iranks[number_of_cards], w_niranks;
		int w_rank = get_hand_rank(w_cards, w_iranks, w_niranks);
#ifdef DEBUG
		write_cards(cout, b_cards);
		cout << ": " << hand_rank_strings[b_rank] << ", ";
		write_cards(cout, w_cards);
		cout << ": " << hand_rank_strings[w_rank] << endl;
#endif
		int winner;
		if (b_rank < w_rank)
			winner = 1;
		else if (b_rank > w_rank)
			winner = -1;
		else
			winner = compare_hand_ranks(b_iranks, w_iranks, b_niranks);
		switch (winner) {
		case 1:
			cout << "Black wins.\n";
			break;
		case 0:
			cout << "Tie.\n";
			break;
		case -1:
			cout << "White wins.\n";
			break;
		}
	}
	return 0;
}

