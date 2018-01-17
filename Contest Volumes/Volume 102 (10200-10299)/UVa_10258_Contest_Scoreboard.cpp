
/*
	2.8.7 Contest Scoreboard
	PC/UVa IDs: 110207/10258, Popularity: B, Success rate: average Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10258_Contest_Scoreboard.cpp
*/

#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

const int contestants_max = 100;
const int problems_max = 9;

int compare_score(const void* elem1, const void* elem2)
{
	const int* i = reinterpret_cast<const int*>(elem1);
	const int* j = reinterpret_cast<const int*>(elem2);
	if (i[3] == j[3]) {
		if (i[1] == j[1]) { // number of problems solved
			if (i[2] == j[2]) // penalty
				return i[0] - j[0]; // contestant number
			else
				return i[2] - j[2]; // for penalty, the less the better
		}
		else
			return j[1] - i[1]; // for the number of problems solved, the more the better
	}
	else
		return j[3] - i[3];
}

int main(int /* argc */, char** /* argv */)
{
	string line;
	istringstream iss;

	// read the number of case
	getline(cin, line);
	iss.str(line);
	int cases;
	iss >> cases;
	iss.clear();
	if (cases)
		getline(cin, line); // skip a blank line
	while (cases--) {
		int submissions[contestants_max][problems_max];
/*
		if submissions[i][j] > 0, i-th contesntant has made at least one correct submission for j-th problem.
		else if  submissions[i][j] < 0, i-th contestant has made at least one incorrect submission.
		else, i-th contestant has never made any submissions.
*/
		int entries[contestants_max][problems_max];
/*
		if entries[i][j] > 0, entries[i][j] is the penalty time for j-th problem solved by i-th contestant
		else if entries[i][] < 0, it is the number of incorrect submissions
		else, j-th problem has not been submitted
*/
		for (int i = 0; i < contestants_max; i++)
			for (int j = 0; j < problems_max; j++)
				submissions[i][j] = entries[i][j] = 0;
		while (true) {
			// read the judging queue until we hit a blank line
			if (!getline(cin, line) || line.empty())
				break;
			iss.str(line);
			int contestant, problem, time;
			char l;
			iss >> contestant >> problem >> time >> l;
			iss.clear();
			switch (l) {
			case 'C': // 'C'orrect
				if (submissions[contestant - 1][problem - 1] <= 0) { // the first correct submission
					submissions[contestant - 1][problem - 1] = 1;
					entries[contestant - 1][problem - 1] = time - entries[contestant - 1][problem - 1] * 20;
				}
				break;
			case 'I': // 'I'ncorrect
				if (submissions[contestant - 1][problem - 1] <= 0) { // the contestant hasn't made a correct submission yet
					submissions[contestant - 1][problem - 1] = -1;
					entries[contestant - 1][problem - 1]--;
				}
				break;
			default: // clarification 'R'equest , 'U'njudged, and 'E'rroneous submission do not affect scoring
				if (submissions[contestant - 1][problem - 1] <= 0) // the contestant hasn't made a correct submission yet
					submissions[contestant - 1][problem - 1] = -1;
				break;
			}
		}
		// calculate the scores
/*
		entires[][] is reused such that:
			entries[i][0] is the contestant number (> 0)
			entries[i][1] is the number of problems solved by the contestant
			entreis[i][2] is the total penalty
			entries[i][3] is not zero for the constestants who made submissions
*/
		for (int i = 0; i < contestants_max; i++) {
			bool submitted = false;
			int problems = 0, penalty = 0;
			for (int j = 0; j < problems_max; j++) {
				if (submissions[i][j]) {
					submitted = true;
					if (submissions[i][j] > 0) {
						problems++;
						penalty += entries[i][j];
					}
				}
			}
			entries[i][0] = i + 1;
			entries[i][1] = problems;
			entries[i][2] = penalty;
			entries[i][3] = submitted;
		}
		qsort(entries, contestants_max, sizeof(int) * problems_max, compare_score); // sort the scores
		for (int i = 0; i < contestants_max && entries[i][3]; i++) // only display those contestants who have made a submission
			cout << entries[i][0] << ' ' << entries[i][1] << ' ' << entries[i][2] << endl;
		if (cases)
			cout << endl;
	}
	return 0;
}

