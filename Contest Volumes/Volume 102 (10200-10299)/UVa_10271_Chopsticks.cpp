
/*
	11.6.7 Chopsticks
	PC/UVa IDs: 111107/10271, Popularity: B, Success rate: average Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10271_Chopsticks.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

#ifndef LLONG_MAX
#define LLONG_MAX     9223372036854775807i64 /* maximum signed long long int value */
#endif

#ifdef __MEMORIZATION__
long long chopstick_pairs(int nr_pairs, int nr_chopsticks,
	const vector<int>& chopsticks, const vector<long long>& cs_distances, vector< vector<long long> >& cs_badness)
{
	long long& b = cs_badness[nr_pairs][nr_chopsticks];
	if (b != -1) // have already been calculated
		return b;
	else {
		if (!nr_pairs)
			b = 0;
		else if (nr_pairs * 3 > nr_chopsticks)
			b = LLONG_MAX;
		else
			b = min(chopstick_pairs(nr_pairs, nr_chopsticks - 1, chopsticks, cs_distances, cs_badness),
				chopstick_pairs(nr_pairs - 1, nr_chopsticks - 2, chopsticks, cs_distances, cs_badness) + cs_distances[nr_chopsticks]);
		return b;
	}
}
#else
long long chopstick_pairs(int nr_pairs, int nr_chopsticks,
	const vector<int>& chopsticks, const vector<long long>& cs_distances)
{
/*
	Let cs_badness[i][j] be the minimum badness for choosing j-pairs of chopsticks from chopsticks[1] ... chopsticks[i], 
	i >= 3 * j. Then,
		cs_badness[i][j] = min{cs_badness[i - 1][j], cs_badness[i - 2][j - 1] + cs_distances[i]
	The trick is chopsticks[] are arranged in descending order of their lengths.
	That way, when if we choose the latter value of the above eauation using cs_distances[i] 
	(the badness between chopsticks[i - 1] and chopsticsk[i]), there always exists extra ones before them.
*/
#if __DP__
	vector< vector<long long> > cs_badness(nr_chopsticks + 1, vector<long long>(nr_pairs + 1, LLONG_MAX));
		// uses at most 40 MB of memory (actually, 5001 * 1009 * sizeof(long long))
	for (int i = 0; i <= nr_chopsticks; i++)
		cs_badness[i][0] = 0;
	for (int i = 1; i <= nr_chopsticks; i++)
		for (int j = 1; j <= i / 3 && j <= nr_pairs; j++)
			cs_badness[i][j] = min(cs_badness[i - 1][j], cs_badness[i - 2][j - 1] + cs_distances[i]);
	return cs_badness[nr_chopsticks][nr_pairs];
#else
	vector< vector<long long> > cs_badness(3, vector<long long>(nr_pairs + 1, LLONG_MAX));
		// uses at most 24KB of memory (actually, 3 * 1009 * sizeof(long long))
	for (int i = 0; i < 3; i++)
		cs_badness[i][0] = 0;
	for (int i = 0; i < nr_chopsticks; i++)
		for (int j = 1; j <= (i + 1) / 3 && j <= nr_pairs; j++)
			cs_badness[i % 3][j] = min(cs_badness[(i - 1) % 3][j], cs_badness[(i - 2) % 3][j - 1] + cs_distances[i + 1]);
	return cs_badness[(nr_chopsticks - 1) % 3][nr_pairs];
#endif
}
#endif

int main(int /* argc */, char** /* argv */)
{
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		int nr_pairs, nr_chopsticks;
		cin >> nr_pairs >> nr_chopsticks;
		nr_pairs += 8;
		vector<int> chopsticks(nr_chopsticks + 1);
		for (int i = 0; i < nr_chopsticks; i++)
			cin >> chopsticks[nr_chopsticks - i]; // store in descending order of lengths
		vector<long long> cs_distances(nr_chopsticks + 1, 0);
		for (int i = 2; i <= nr_chopsticks; i++) { // calculate the badness for each adjacent pair of chopsticks
			long long d = chopsticks[i] - chopsticks[i - 1];
			cs_distances[i] = d * d;
		}
#ifdef __MEMORIZATION__
		vector< vector<long long> > cs_badness(nr_pairs + 1, vector<long long>(nr_chopsticks + 1, -1));
		cout << chopstick_pairs(nr_pairs, nr_chopsticks, chopsticks, cs_distances, cs_badness) << endl;
#else
		cout << chopstick_pairs(nr_pairs, nr_chopsticks, chopsticks, cs_distances) << endl;
#endif
	}
	return 0;
}

