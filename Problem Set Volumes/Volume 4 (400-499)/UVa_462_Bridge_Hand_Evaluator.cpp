
/*
	UVa 462 - Bridge Hand Evaluator

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_462_Bridge_Hand_Evaluator.cpp
*/

#include <cstdio>

enum {spade, heart, diamond, club};
const int nr_suits = club + 1, nr_ranks = 13;

struct suit {
	int nr_;
	bool ace_, jack_, queen_, king_;
} suits[nr_suits];

void initialize_suits()
{
	for (int i = 0; i < nr_suits; i++) {
		suits[i].nr_ = 0;
		suits[i].ace_ = suits[i].jack_ = suits[i].queen_ = suits[i].king_ = false;
	}
}

bool read_cards()
{
	char card[2 + 1];
	int si;
	for (int i = 0; i < nr_ranks; i++) {
		if (scanf("%s", card) == EOF)
			return false;
		switch (card[1]) {
		case 'S':
			si = spade; break;
		case 'H':
			si = heart; break;
		case 'D':
			si = diamond; break;
		default:
			si = club; break;
		}
		suits[si].nr_++;
		switch (card[0]) {
		case 'A':
			suits[si].ace_ = true; break;
		case 'J':
			suits[si].jack_ = true; break;
		case 'Q':
			suits[si].queen_ = true; break;
		case 'K':
			suits[si].king_ = true; break;
		default:
			break;
		}
	}
	return true;
}

int calculate_points_1_4()
{
	int points = 0;
	for (int si = 0; si < nr_suits; si++) {
		const suit& s = suits[si];
		if (s.ace_)
			points += 4;
		if (s.king_)
			points += (s.nr_ < 2) ? 2 : 3;
		if (s.queen_)
			points += (s.nr_ < 3) ? 1 : 2;
		if (s.jack_ && s.nr_ > 3)
			points++;
	}
	return points;
}

int calculate_points_5_7()
{
	int points = 0;
	for (int si = 0; si < nr_suits; si++) {
		const suit& s = suits[si];
		if (s.nr_ == 2)
			points++;
		else if (s.nr_ < 2)
			points += 2;
	}
	return points;
}

bool is_no_trump(int points)
{
	if (points < 16)
		return false;
	for (int si = 0; si < nr_suits; si++) {
		const suit& s = suits[si];
		if (s.ace_ || s.king_ && s.nr_ > 1 || s.queen_ && s.nr_ > 2) // suit is stopped
			;
		else
			return false;
	}
	return true;
}

char bid()
{
	const char ss[] = "SHDC";
	int max_si, max_nr = 0;
	for (int si = 0; si < nr_suits; si++)
		if (suits[si].nr_ > max_nr) {
			max_si = si;
			max_nr = suits[si].nr_;
		}
	return ss[max_si];
}

int main()
{
	while (true) {
		initialize_suits();
		if (!read_cards())
			break;
		int points = calculate_points_1_4();
		if (is_no_trump(points))
			puts("BID NO-TRUMP");
		else {
			points += calculate_points_5_7();
			if (points < 14)
				puts("PASS");
			else
				printf("BID %c\n", bid());
		}
	}
	return 0;
}

