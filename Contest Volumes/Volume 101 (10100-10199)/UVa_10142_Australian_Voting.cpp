
/*
	1.6.8 Australian Voting
	PC/UVa IDs: 110108/10142, Popularity: B, Success rate: low Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10142_Australian_Voting.cpp
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int candidates_max = 20;
const int ballots_max = 1000;

int main(int /* argc */, char** /* argv */)
{
	string line;
	istringstream iss;
	// read the number of cases
	getline(cin, line);
	iss.str(line);
	int nr_cases; // number of cases
	iss >> nr_cases;
	iss.clear();
	if (nr_cases)
		getline(cin, line); // skip a blank line

	while (nr_cases) {
		// read the number of candidates
		int nr_candidates; // number of candidates
		getline(cin, line);
		iss.str(line);
		iss >> nr_candidates;
		iss.clear();

		// read the candidates
		string candidates[candidates_max];
		int effective_candidates[candidates_max]; // 1 if effective, 0 if just eliminated, -1 if has been eliminated before
		int votes[candidates_max]; // votes for candidates
		for (int i = 0; i < nr_candidates; i++) {
			getline(cin, candidates[i]);
			effective_candidates[i] = 1; // mark as effective
			votes[i] = 0;
		}

		// read the ballots
		int nr_ballots;
		int ballot_indices[ballots_max]; // index in each ballot array
		int ballots[ballots_max][candidates_max];
		for (nr_ballots = 0; ; nr_ballots++) {
			if (!getline(cin, line) || line.empty()) // a blank line
				break;
			iss.str(line);
			ballot_indices[nr_ballots] = 0;
			for (int i = 0; i < nr_candidates; i++)
				iss >> ballots[nr_ballots][i];
			iss.clear();
		}
		if (!nr_ballots) {
			for (int i = 0; i < nr_candidates; i++)
				cout << candidates[i] << endl;
			if (--nr_cases)
				cout << endl; // separate the output of two consecutive cases by a blank line
			continue;
		}

		// count the first choice of each ballot
		for (int i = 0; i < nr_ballots; i++)
			votes[ballots[i][ballot_indices[i]] - 1]++;

		while (true) {
			int min_vote = nr_ballots + 1, max_vote = 0, max_voted_candidate;
			for (int i = 0; i < nr_candidates; i++)
				if (effective_candidates[i] > 0) {
					min_vote = min(min_vote, votes[i]);
					if (votes[i] > max_vote) {
						max_vote = votes[i];
						max_voted_candidate = i;
					}
				}
			if (max_vote * 2 > nr_ballots) { // a candidate is selected
				cout << candidates[max_voted_candidate] << endl;
				break;
			}
			else if (min_vote == max_vote) { // all the remaing candidates are tied
				for (int i = 0; i < nr_candidates; i++)
				if (effective_candidates[i] > 0)
					cout << candidates[i] << endl;
				break;
			}
			for (int i = 0; i < nr_candidates; i++)
				if (effective_candidates[i] > 0 && votes[i] == min_vote) // for a candidate who got the mininum votes
					effective_candidates[i] = 0; // mark that the candidate was just eliminated
			for (int i = 0; i < nr_ballots; i++)
				if (!effective_candidates[ballots[i][ballot_indices[i]] - 1])
					// for a ballot which votes a candidate who was just eliminated
					while (ballot_indices[i] < nr_candidates) { // recount the ballot in favor of a non-eliminated candidate
						if (effective_candidates[ballots[i][++ballot_indices[i]] - 1] > 0) {
							votes[ballots[i][ballot_indices[i]] - 1]++;
							break;
						}
					}
			for (int i = 0; i < nr_candidates; i++)
				if (!effective_candidates[i]) // for a candidate who has been just elminated
					effective_candidates[i] = -1; // mark that the candidate has been eliminated before
		}
		if (--nr_cases)
			cout << endl; // separate the output of two consecutive cases by a blank line
	}
	return 0;
}

