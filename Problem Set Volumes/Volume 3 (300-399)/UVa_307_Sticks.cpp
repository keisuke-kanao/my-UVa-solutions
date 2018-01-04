
/*
	UVa 307 - Sticks

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_307_Sticks.cpp
*/

#include <algorithm>
#include <functional>
#include <vector>
#include <cstdio>
#include <cmath>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

// greedy backtrack

#ifdef __ANOTHER__
bool restore_sticks(int nr_sticks, int si, int nr_used, int restored, int length,
	const vector<int>& sticks, vector<bool>& used)
{
	if (restored == length) {
		if (nr_used == nr_sticks)
			return true;
		restored = 0;
    }
	if (!restored) {
		for (si = 0; used[si]; si++)
			;
        used[si] = true;
		if (restore_sticks(nr_sticks, si + 1, nr_used + 1, sticks[si], length, sticks, used))
			return true;
		used[si] = false;
	}
    else {
		for (int i = si; i < nr_sticks; i++) {
			if (used[i] || i && sticks[i] == sticks[i - 1] && !used[i - 1])
				continue;
			if (restored + sticks[i] <= length) {
				used[i] = true;
				if (restore_sticks(nr_sticks, i + 1, nr_used + 1, restored + sticks[i], length, sticks, used))
					return true;
				used[i] = false;
				if (restored + sticks[i] == length)
					return false;
			}
		}
	}
	return false;
}
#else
bool restore_sticks(int nr_sticks, int si, int total, int length, int restored,
	const vector<int>& sticks, const vector<int>& remainings, vector<bool>& used)
{
	if (!total)
		return true;
	if (restored == length) {
		restored = 0;
		for (si = 0; used[si]; si++)
			;
		used[si] = true;
		if (restore_sticks(nr_sticks, si + 1, total - sticks[si], length, sticks[si], sticks, remainings, used))
			return true;
		used[si] = false;
		return false;
	}
	for (int i = si; i < nr_sticks; i++) {
		if (used[i] || i && sticks[i] == sticks[i - 1] && !used[i - 1])
			continue;
		if (restored + sticks[i] <= length && restored + remainings[i] >= length) {
			used[i] = true;
			if (restore_sticks(nr_sticks, i + 1, total - sticks[i], length, restored + sticks[i], sticks, remainings, used))
				return true;
			used[i] = false;
			if (restored + sticks[i] == length)
				return false;
		}
	}
	return false;
}
#endif

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (true) {
		int nr_sticks;
		scanf("%d", &nr_sticks);
		if (!nr_sticks)
			break;
		vector<int> sticks(nr_sticks);
		int total = 0, max_stick = 0;
		for (int i = 0; i < nr_sticks; i++) {
			scanf("%d", &sticks[i]);
			max_stick = max(max_stick, sticks[i]);
			total += sticks[i];
		}
		sort(sticks.begin(), sticks.end(), greater<int>());
		vector<int> remainings(nr_sticks);
		remainings[nr_sticks - 1] = sticks[nr_sticks - 1];
		for (int i = nr_sticks - 2; i >= 0; i--)
			remainings[i] = remainings[i + 1] + sticks[i];
#ifdef DEBUG
		printf("%d: ", total);
		for (int i = 0; i < nr_sticks; i++)
			printf(" %d", sticks[i]);
		putchar('\n');
#endif
		int min_length = total, max_length = static_cast<int>(ceil(sqrt(static_cast<double>(total))));
		for (int length = 2; length <= max_length; length++)
			if (!(total % length) && length >= max_stick) {
				vector<bool> used(nr_sticks, false);
#ifdef DEBUG
				printf("%d...\n", length);
#endif
#ifdef __ANOTHER__
				if (restore_sticks(nr_sticks, 0, 0, 0, length, sticks, used)) {
#else
				if (restore_sticks(nr_sticks, 0, total, length, 0, sticks, remainings, used)) {
#endif
					min_length = length;
					break;
				}
			}
		if (min_length == total) {
			for (int length = max_length - 1; length >= 2; length--)
			if (!(total % length) && total / length >= max_stick) {
#ifdef DEBUG
				printf("%d...\n", total / length);
#endif
				vector<bool> used(nr_sticks, false);
#ifdef __ANOTHER__
				if (restore_sticks(nr_sticks, 0, 0, 0, total / length, sticks, used)) {
#else
				if (restore_sticks(nr_sticks, 0, total, total / length, 0, sticks, remainings, used)) {
#endif
					min_length = total / length;
					break;
				}
			}
		}
		printf("%d\n", min_length);
	}
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

