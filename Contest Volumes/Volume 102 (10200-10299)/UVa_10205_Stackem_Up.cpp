
/*
	2.8.5 Stack'em Up
	PC/UVa IDs: 110205/10205, Popularity: B, Success rate: average Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10205_Stackem_Up.cpp
*/

#include <iostream>
#include <sstream>
#include <queue>
using namespace std;

const int number_of_cards = 52;
const int number_of_shuffles_max = 100;

void apply_shuffle(int shuffle[], int cards[])
{
	// Within each set of a shuffle, i in position j means that the shuffle moves the i-th card in the deck to position j.
	queue<int> cq;
	for (int i = 1; i <= number_of_cards; i++)
		cq.push(cards[shuffle[i]]); // insert the i-th card
	for (int i = 1; i <= number_of_cards; i++) {
		cards[i] = cq.front();
		cq.pop();
	}
}

string convert_card_to_string(int card)
{
	const char *values[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
	const char *suits[] = {" of Clubs", " of Diamonds", " of Hearts", " of Spades"};
	string s = values[card % 13];
	return s + suits[(card - 1) / 13];
}

int main(int /* argc */, char** /* argv */)
{
	int cards[number_of_cards + 1]; // cards[0] is not used
	int shuffles[number_of_shuffles_max][number_of_cards + 1]; // shuffles[][0] are not used
	string line;
	istringstream iss;

	// read an integer indicating the number of test cases
	getline(cin, line);
	iss.str(line);
	int nr_cases;
	iss >> nr_cases;
	iss.clear();
	if (nr_cases)
		getline(cin, line); // skip a blank line
	while (nr_cases--) {
		// read an integer indicating the number of shuffles
		getline(cin, line);
		iss.str(line);
		int nr_shuffles;
		iss >> nr_shuffles;
		iss.clear();
		for (int i = 0; i < nr_shuffles; i++)
			for (int j = 1; j <= number_of_cards; j++) { // read 52 integers
				cin >> shuffles[i][j];
// cout << shuffles[i][j] << ' ';
			}
// cout << endl;
		if (nr_shuffles)
			getline(cin, line); // read and discard the newline at the end of last set
		// initialize the cards
		for (int i = 1; i <= number_of_cards; i++)
			cards[i] = i;
		while (true) {
			// read the shuffle number until we hit a blank line
			if (!getline(cin, line) || line.empty()) // end of intput or a blank line
				break;
			iss.str(line);
			int nr_shuffle;
			iss >> nr_shuffle;
// cout << nr_shuffle << endl;
			iss.clear();
			if (nr_shuffles)
				apply_shuffle(shuffles[nr_shuffle - 1], cards); // apply the shuffle
		}
		for (int i = 1; i <= number_of_cards; i++) // print out the result
			cout << convert_card_to_string(cards[i]) << endl;
		if (nr_cases)
			cout << endl;
	}
}

