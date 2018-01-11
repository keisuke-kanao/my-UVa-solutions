
/*
	UVa 10020 - Minimal coverage

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10020_Minimal_coverage.cpp

	An accepted solution.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <algorithm>
#include <limits>
using namespace std;

const size_t nr_segments_max = 100000;
pair<int, int> segments[nr_segments_max + 1];
	// segments[i].first is i-th segment's left end, and segments[i].second is its right end
int chosen_segments[nr_segments_max]; // indices of chosen segments from segments[]

bool compare_segment(const pair<int, int>& i, const pair<int, int>& j)
{
	if (i.first < j.first)
		return true;
	else if (i.first > j.first)
		return false;
	else
		return i.second > j.second;
}

int choose_segments(int m, int nr_segments)
{
	// sort the segments in ascending order of their left ends and for the ties in descending order of their right ends
	sort(segments, segments + nr_segments, compare_segment);
	// find the leftmost segment
	int si = 0, psi = -1;
	for ( ; si < nr_segments; si++) {
		if (segments[si].first > 0)
			break;
		else if (psi == -1 || segments[si].second > segments[psi].second)
			psi = si;
	}
	int ci = 0;
	chosen_segments[ci++] = psi;
	if (segments[psi].second >= m)
		return ci; // segment [0, m] is covered by only one segment
	for ( ; si < nr_segments; si++) {
		if (segments[psi].second < segments[si].first) // there is a segment that is not covered
			return 0;
		if (segments[psi].second >= segments[si].second) // segments[si] is completely covered by segments[psi]
			continue;
		if (segments[chosen_segments[ci - 1]].second < segments[si].first)
			ci++;
		chosen_segments[ci] = si;
		if (segments[si].second >= m)
			break;
		psi = si;
	}
	return ci + 1;
}

int main()
{
	int nr_cases;
	cin >> nr_cases;
	string s;
	getline(cin, s); // skip '\n'
	getline(cin, s); // skip a blank line
	while (nr_cases--) {
		getline(cin, s);
		istringstream iss(s);
		int m;
		iss >> m;
		iss.clear();
		int nr_segments = 0;
		int l_min = numeric_limits<int>::max(), r_max = numeric_limits<int>::min();
		while (true) {
			getline(cin, s);
			iss.str(s);
			pair<int, int> sg;
			iss >> segments[nr_segments].first >> segments[nr_segments].second;
			iss.clear();
			if (!segments[nr_segments].first && !segments[nr_segments].second)
				break;
			l_min = min(l_min, segments[nr_segments].first);
			r_max = max(r_max, segments[nr_segments].second);
			nr_segments++;
		}
		int nr_chosen_segments = (l_min > 0 || r_max < m) ? 0 : choose_segments(m, nr_segments);
		cout << nr_chosen_segments << endl;
		for (int i = 0; i < nr_chosen_segments; i++)
			cout << segments[chosen_segments[i]].first << ' ' << segments[chosen_segments[i]].second << endl;
		if (nr_cases) {
			cout << endl;
			getline(cin, s); // skip a line
		}
	}
	return 0;
}

