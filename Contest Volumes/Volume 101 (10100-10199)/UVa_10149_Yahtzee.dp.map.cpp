
/*
	2.8.8 Yahtzee
	PC/UVa IDs: 110208/10149, Popularity: C, Success rate: average Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10149_Yahtzee.dp.map.cpp

	An accepted solution.
*/

#include <iostream>
#ifdef DEBUG
#include <iomanip>
#endif
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

enum categories {
	ct_not_applied = -1,
	ct_ones, ct_twos, ct_threes, ct_fours, ct_fives, ct_sixes,
	ct_chance, ct_three_of_a_kind, ct_four_of_a_kind,
	ct_five_of_a_kind, ct_short_straight, ct_long_straight, ct_full_house
};

const int nr_dies = 5; // number of dies
const int nr_rounds = 13; // number of rounds
const int nr_categories = ct_full_house - ct_ones + 1; // number of categories
const int min_sum_for_bonus = 63; // min. sum of first six categories for bonus
const int bonus_point = 35; // bonus point

int category_chance(const vector<int>& dies) // sum of all dies
{
	return accumulate(dies.begin(), dies.end(), 0);
}

int category_three_of_a_kind(const vector<int>& dies) // sum of all dies, provided at least three have same value
{
	// note that dies is sorted in ascending order
	for (int i = 0; i < nr_dies - 2; i++)
		if (dies[i] == dies[i + 1] && dies[i + 1] == dies[i + 2])
			return category_chance(dies);
	return 0;
}

int category_four_of_a_kind(const vector<int>& dies) // sum of all dies, provided at least four have same value
{
	// note that dies is sorted in ascending order
	int j = (dies[0] == dies[1]) ? nr_dies - 2 : nr_dies - 1;
	for (int i = 1; i < j; i++)
		if (dies[i] != dies[i + 1])
			return 0;
	return category_chance(dies);
}

int category_five_of_a_kind(const vector<int>& dies) // 50 points, provided all five dies have same value
{
	// note that dies is sorted in ascending order
	return (dies[0] == dies[4]) ? 50 : 0;
}

int category_short_straight(const vector<int>& dies) // 25 points, provided four of the dies form a sequence
{
	int j = (dies[0] + 1 == dies[1]) ? nr_dies - 2 : nr_dies - 1;
	for (int i = 1; i < j; i++)
		if (dies[i] + 1 != dies[i + 1])
			return 0;
	return 25;
}

int category_long_straight(const vector<int>& dies) // 35 points, provided all dies form a sequence
{
	for (int i = 0; i < nr_dies - 1; i++)
		if (dies[i] + 1 != dies[i + 1])
			return 0;
	return 35;
}

int category_full_house(const vector<int>& dies) // 40 points, provided three of the dies are equal and the other two dies are also equal
{
	if (dies[0] != dies[1]) // the first two must be equal
		return 0;
	if (dies[1] == dies[2]) // the first three are equal
		return (dies[3] == dies[4]) ? 40 : 0; // the last two must be equal
	else
		return (dies[2] == dies[3] && dies[3] == dies[4]) ? 40 : 0; // the last three must be equal
}

int category_numbers(const vector<int>& dies, int n)
{
	return n * count(dies.begin(), dies.end(), n);
}

int category_ones(const vector<int>& dies) // sum of all ones thrown
{
	return category_numbers(dies, 1);
}

int category_twos(const vector<int>& dies) // sum of all twos thrown
{
	return category_numbers(dies, 2);
}

int category_threes(const vector<int>& dies) // sum of all threes thrown
{
	return category_numbers(dies, 3);
}

int category_fours(const vector<int>& dies) // sum of all fours thrown
{
	return category_numbers(dies, 4);
}

int category_fives(const vector<int>& dies) // sum of all fives thrown
{
	return category_numbers(dies, 5);
}

int category_sixes(const vector<int>& dies) // sum of all sixes thrown
{
	return category_numbers(dies, 6);
}

void caluculate_applicable_scores(const vector<int>& dies, vector<int>& scores)
{
	typedef int (*category_function)(const vector<int>&);
	const category_function category_functions[] = {
		category_ones, category_twos, category_threes, category_fours, category_fives, category_sixes,
		category_chance, category_three_of_a_kind, category_four_of_a_kind, category_five_of_a_kind,
		category_short_straight, category_long_straight, category_full_house
	};
	for (int i = ct_ones; i <= ct_full_house; i++) {
		int score = category_functions[i](dies);
		if (score)
			scores[i] = score;
	}
}

inline int get_score_index(int category)
{

	return 1 << (category + 16);
}

inline int get_score_index(int category, int score) // score index for the first six categories
{
/*
	if (score > min_sum_for_bonus)
		score = min_sum_for_bonus;
*/
	return 1 << (category + 16) | score;
}

inline int get_category_bitmap(int index)
{
	return index >> 16;
}

inline int get_score_for_bonus(int index)
{
	return index & 0xffff;
}

int get_applied_score(unsigned long long score, int category, const vector< vector<int> >& applicable_scores)
{
	int round = static_cast<int>((score >> (category * 4)) & 0xf);
	return (round == 0xf) ? 0 /* not applied */ : applicable_scores[round][category];
}

inline int get_total_of_score(unsigned long long score)
{
	return static_cast<int>((score >> 52) & 0xfff);
}

unsigned long long set_score(int round, int category, const vector< vector<int> >& applicable_scores)
{
	unsigned long long score = 0x000fffffffffffffULL;
	score &= ~(static_cast<unsigned long long>(0xf) << (category * 4));
	score |= static_cast<unsigned long long>(round) << (category * 4);
	score |= static_cast<unsigned long long>(applicable_scores[round][category]) << 52;
	return score;
}

unsigned long long change_score(unsigned long long score, int round, int category, int s)
{
	score &= ~(static_cast<unsigned long long>(0xf) << (category * 4));
	score |= static_cast<unsigned long long>(round) << (category * 4);
	score &= 0x000fffffffffffffULL;
	score |= static_cast<unsigned long long>(s) << 52;
	return score;
}

void add_to_scores(int index, unsigned long long score, map<int, unsigned long long>& scores)
{
	map<int, unsigned long long>::iterator i = scores.find(index);
	if (i != scores.end()) {
		if (get_total_of_score(i->second) < get_total_of_score(score))
			i->second = score;
	}
	else
		scores.insert(make_pair(index, score));
}

bool read_rounds_of_dies(vector< vector<int> >& applicable_scores)
{
	for (int i = 0; i < nr_rounds; i++) { // read the values of thirteen rounds
		vector<int> dies(nr_dies); // values of the five dies thrown, sorted in ascending order
		for (int j = 0; j < nr_dies; j++) { // read the values of the five dies
			if (!(cin >> dies[j]))
				return false; // end of input
		}
		sort(dies.begin(), dies.end());
		caluculate_applicable_scores(dies, applicable_scores[i]);
	}
	return true;
}

#ifdef DEBUG
void print_scores(const map<int, unsigned long long>& scores)
{
	map<int, unsigned long long>::const_iterator iend = scores.end();
	for (map<int, unsigned long long>::const_iterator i = scores.begin(); i != iend; ++i)
		cerr << hex << setw(4) << setfill('0') << get_category_bitmap(i->first) << '-' <<
			dec << setw(4) << setfill(' ') << get_score_for_bonus(i->first) << ": " <<
			get_total_of_score(i->second) << endl;
	cerr << endl;
}
#endif

void caluculate_scores(vector< vector<int> >& applicable_scores, vector< map<int, unsigned long long> >& scores)
{
	for (int i = 0; i < nr_rounds; i++) {
		map<int, unsigned long long>& current_scores = scores[i % 2];
		map<int, unsigned long long>& previous_scores = scores[(i + 1) % 2];
		current_scores = previous_scores;

		for (int j = 0; j < nr_categories; j++) {
			if (applicable_scores[i][j] == -1) // not applied to any categories
				continue;

			int pi, ci; // previous and current indices
			unsigned long long ps, cs; // prevous and current scores
			// insert or update a pair of category and its score on its own
			ci = (j < ct_chance) ? get_score_index(j, applicable_scores[i][j]) : get_score_index(j);
			cs = set_score(i, j, applicable_scores);
			add_to_scores(ci, cs, current_scores);

			// add the score to the existing pairs of categories and thier scores
			map<int, unsigned long long>::iterator k, kend = previous_scores.end();
			for (k = previous_scores.begin(); k != kend; ++k) {
				pi = k->first; ps = k->second;
				int ts = get_total_of_score(ps); // totoal of the previous score
				// score for category j of the previous score
				int as = (pi & get_score_index(j)) ? // category j is applied to any of the previous rounds
					get_applied_score(ps, j, applicable_scores) : 0;
				if (j > ct_sixes) {
					// replace category j with current round i and update the total score
					cs = change_score(ps, i, j, ts + applicable_scores[i][j] - as);
					add_to_scores(pi | get_score_index(j), cs, current_scores);
				}
				else {
					// modifying the socre for category j of the prevous score also entails updating 
					// the lower 16-bits of index.
					ci = get_score_index(j, get_score_for_bonus(pi) + applicable_scores[i][j] - as);
					ci |= get_category_bitmap(pi) << 16;
					cs = change_score(ps, i, j, ts + applicable_scores[i][j] - as);
					add_to_scores(ci, cs, current_scores);
				}
			}
		}
#ifdef DEBUG
		cerr << i + 1 << " rounds, " << current_scores.size() << " scores\n";
//		print_scores(current_scores);
#endif
	}
}

int get_max_score(map<int, unsigned long long>& scores, pair<int, unsigned long long>& s)
{
	int max_ts = -1;
	map<int, unsigned long long>::const_iterator iend = scores.end();
	for (map<int, unsigned long long>::const_iterator i = scores.begin(); i != iend; ++i) {
		int ts = get_total_of_score(i->second);
		if (get_score_for_bonus(i->first) >= min_sum_for_bonus)
			ts += bonus_point; // a bonus of 35 points if the sum of the first six categories is 63 or greater
		if (max_ts < ts) {
			max_ts = ts; s = *i;
		}
	}
	return max_ts;
}

void print_scores(const pair<int, unsigned long long>& s, const vector< vector<int> >& applicable_scores)
{
	int ts = get_total_of_score(s.second);
	unsigned long long ri = s.second;
	for (int i = 0; i < nr_categories; i++, ri >>= 4) { // print the score for each category
		int r = (ri & 0xf);
		cout << ((r != 0x0f) ? applicable_scores[r][i] : 0) << ' ';
	}
	// print the bonus score
	if (get_score_for_bonus(s.first) >= min_sum_for_bonus) {
		cout << "35 ";
		ts += bonus_point;
	}
	else
		cout << "0 ";
	cout << ts << endl;
}

int main(int /* argc */, char ** /* argv */)
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (true) {
		vector< vector<int> > applicable_scores(nr_rounds, vector<int>(nr_categories, -1));
			// applicable_scores[i][j] is the score when the j-th category is applied to the i-th round, 
			// or -1 if the j-th category cannot be applied.
		if (!read_rounds_of_dies(applicable_scores))
			break;
		vector< map<int, unsigned long long> > scores(2);
/*
	key is an index whose:
		higher 16-bits are bitmaps of applied categories, 
			in which i-th bit is set if the i-th categoriy from categories enumeration is applied.
		lower 16-bits are the sum of first six categories' (i.e., ones, twos, threes, fours, fives, and sixes) scores.
	value is the score:
		bit (4 * i) - bit (4 * i + 3) is the round index if the i-th category is applied to the round, 
			or 0xf if it is not applied.
		bit 52 - bit 63 is the total scores.
*/
		caluculate_scores(applicable_scores, scores);
		map<int, unsigned long long>& current_scores = scores[(nr_rounds - 1) % 2];
		pair<int, unsigned long long> s;
		get_max_score(current_scores, s);
		print_scores(s, applicable_scores);
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

