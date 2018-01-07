
/*
	UVa 340 - Master-Mind Hints

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_340_Master-Mind_Hints.cpp

	from 1995 ACM Regional, Problem C - Master-Mind Hints
		(http://www.karrels.org/Ed/ACM/reg95/code.html)
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

bool compare_code_value(const pair<int, int>& i, const pair<int, int>& j)
{
	return i.first < j.first;
}

int search_strong_matches(int code_length, const vector<int>& code, const vector<int>& guess, vector<bool>& strong_matches)
{
	int nr_strong_matches = 0;
	for (int i = 0; i < code_length; i++)
		if (code[i] == guess[i]) {
			nr_strong_matches++;
			strong_matches[i] = true;
		}
	return nr_strong_matches;
}

int search_weak_matches(int code_length,
	const vector< pair<int, int> >& sorted_code, const vector< pair<int, int> >& sorted_guess,
	const vector<bool>& strong_matches)
{
	int nr_weak_matches = 0;
	for (int i = 0, j = 0; i < code_length && j < code_length; i++) {
		const pair<int, int>& sc = sorted_code[i];
		if (strong_matches[sc.second]) // already strongly matched
			continue;
		for ( ; j < code_length; j++) {
			const pair<int, int>& sg = sorted_guess[j];
			if (strong_matches[sg.second])
				continue;
			if (sg.first < sc.first)
				continue;
			else {
				if (sg.first == sc.first) {
					nr_weak_matches++;
					j++;
				}
				break;
			}
		}
	}
	return nr_weak_matches;
}

int main()
{
	for (int g = 1; ; g++) {
		int code_length;
		cin >> code_length;
		if (!code_length)
			break;
		vector<int> code(code_length); // secret code
		vector< pair<int, int> > sorted_code(code_length);
		// code[i].first is an integer value, code[i].second is its original position
		for (int i = 0; i < code_length; i++) { // read secret codes
			cin >> code[i];
			sorted_code[i] = make_pair(code[i], i);
		}
		// sort the secret code in ascending order of its values
		stable_sort(sorted_code.begin(), sorted_code.end(), compare_code_value);
		cout << "Game " << g << ":\n";
		while (true) {
			vector<int> guess(code_length);
			vector< pair<int, int> > sorted_guess(code_length);
			for (int i = 0; i < code_length; i++) {
				cin >> guess[i];
				sorted_guess[i] = make_pair(guess[i], i);
			}
			if (!guess[0]) // end of guess
				break;
			vector<bool> strong_matches(code_length, false);
				// strong_matches[i] is true if a strong match for code[i] has been found
			int nr_strong_matches = search_strong_matches(code_length, code, guess, strong_matches);
			int nr_weak_matches = 0;
			if (nr_strong_matches != code_length) {
				// sort the guess in ascending order of its values
				stable_sort(sorted_guess.begin(), sorted_guess.end(), compare_code_value);
				nr_weak_matches = search_weak_matches(code_length, sorted_code, sorted_guess, strong_matches);
			}
			cout << "    (" << nr_strong_matches << ',' << nr_weak_matches << ")\n";
		}
	}
	return 0;
}

