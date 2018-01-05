
/*
	UVa 10570 - Meeting with Aliens

	To build using Visucal Studio 2010:
		cl -EHsc -O2 UVa_10570_Meeting_with_Aliens.cpp

	See "Minimum number of swaps required to sort an array"
		(http://www.geeksforgeeks.org/minimum-number-swaps-required-sort-array/).
*/

#include <algorithm>
#include <functional>
#include <utility>
#include <limits>
#include <cstdio>
#include <cstring>
using namespace std;

const int infinite = numeric_limits<int>::max();
const int N_max = 500;
int N, aliens[N_max];
pair<int, int> vps[N_max];
	// vps[i].first is the value, vps[i].second is the position at which vps[i].first should be
bool visited[N_max];

int count_swaps(int sp, bool ascending_order)
{
	for (int i = 0; i < N; i++)
		vps[i].first = aliens[(sp + i) % N], vps[i].second = i;
	// sort vps by values to get the right position of the value
	if (ascending_order)
		sort(vps, vps + N /* , less< pair<int, int> >() */);
	else
		sort(vps, vps + N, greater< pair<int, int> >());
	memset(visited, 0, sizeof(bool) * N);
	int nr_swaps = 0;
	for (int i = 0; i < N; i++) {
		// already swapped and corrected or already present at correct position
		if (visited[i] || vps[i].second == i)
			continue;
		// find out the number of items in this cycle and add in nr_swaps
		int nr = 0;
		int j = i;
		while (!visited[j]) {
			visited[j] = true;
			// move to next node
			j = vps[j].second;
			nr++;
		}
		nr_swaps += nr - 1;
    }
	return nr_swaps;
}

int main()
{
	while (true) {
		scanf("%d", &N);
		if (!N)
			break;
		for (int i = 0; i < N; i++)
			scanf("%d", &aliens[i]);
		int min_nr_swaps = infinite;
		for (int i = 0; i < N; i++)
			if (!(min_nr_swaps = min(min_nr_swaps, count_swaps(i, true))) ||
				!(min_nr_swaps = min(min_nr_swaps, count_swaps(i, false))))
				break;
		printf("%d\n", min_nr_swaps);
	}
	return 0;
}

