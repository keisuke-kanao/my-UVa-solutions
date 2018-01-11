
/*
	UVa 624 - CD
	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_624_CD.dp.cpp
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

int print_tracks(int n, const vector<int>& tracks, const vector< pair<bool, int> >& c)
{
	int track = 0, sum = 0;
	if (n) {
		track = tracks[c[n].second];
		sum = print_tracks(n - track, tracks, c);
		cout << track << ' ';
	}
	return track + sum;
}

int main()
{
	int n; // tape length
	while (cin >> n) {
		vector< pair<bool, int> > c(n + 1, pair<bool, int>(false, -1));
			// c[i].first is true if the tape of lenght i is realzed by a subset of tracks
			// c[i].second is the index of tracks that realized the tape of length i
		c[0].first = true;
		int m; // number of tracks
		cin >> m;
		vector<int> tracks(m);
		for (int i = 0, sum = 0; i < m; i++) {
			cin >> tracks[i];
			int track = tracks[i];
			if (track > n)
				continue;
			sum += track;
			for (int j = min(sum, n); j >= track; j--)
				if (c[j - track].first && !c[j].first) {
					c[j].first = true; c[j].second = i;
				}
		}
		while (!c[n].first) // locate the max. tape length
			n--;
		int sum = print_tracks(n, tracks, c);
		cout << "sum:" << sum << endl;
	}
	return 0;
}

