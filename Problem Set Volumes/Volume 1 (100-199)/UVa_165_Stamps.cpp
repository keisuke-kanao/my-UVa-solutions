
/*
	UVa 165 - Stamps

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_165_Stamps.cpp

	from ACM South Pacific Regionals 1991 Problem B
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_VV_SouthPac/1991/index.html)
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

void attain_stamp(int h, int k, const vector<int>& stamps,
	int si /* index to stamps */,  int nr_attained, int attained_sum, vector<bool>& attainables)
{
	if (nr_attained == h || si == k) {
		if (attained_sum)
			attainables[attained_sum - 1] = true;
	}
	else {
		for (int i = 0; i <= h - nr_attained; i++)
			attain_stamp(h, k, stamps, si + 1,
				nr_attained + i, attained_sum + stamps[si] * i, attainables);
	}
}

bool attain_stamp(int h, int k, vector<int>& stamps,
	int si /* index to stamps */, int& max_attainable, vector<int>& max_stamps)
{
	if (si == k) {
		vector<bool> attainables(stamps[k - 1] * h, false); // attainables[i] is true if (i - 1) is attainable
		attain_stamp(h, k, stamps, 0,  0, 0, attainables);
		int i;
		for (i = 0; i < stamps[k - 1] * h; i++)
			if (!attainables[i])
				break;
		if (i < stamps[k - 1])
			return false;
		else {
#ifdef DEBUG
			for (int j = 0; j < k; j++)
				cout << setfill(' ') << setw(3) << stamps[j];
			cout << " ->" << setfill(' ') << setw(3) << i << endl;
#endif
			if (i > max_attainable) {
				max_attainable = i;
				for (int j = 0; j < k; j++)
					max_stamps[j] = stamps[j];
			}
			return true;
		}
	}
	else {
		int s = stamps[si - 1] + 1;
		for (stamps[si] = s; ; stamps[si]++)
			if (!attain_stamp(h, k, stamps, si + 1, max_attainable, max_stamps))
				break;
		if (stamps[si] == s)
			return false;
		else {
			stamps[si] = s;
			return true;
		}
	}
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = -1;
#endif
	while (true) {
		int h, k;
		cin >> h >> k;
#ifdef __ELAPSED_TIME__
		if (start == -1)
			start = clock();
#endif
		if (!h && !k)
			break;
		vector<int> stamps(k), max_stamps(k);
		for (int i = 0; i < k; i++)
			stamps[i] = max_stamps[i] = i + 1;
		int max_attainable = h;
		attain_stamp(h, k, stamps, 1, max_attainable, max_stamps);
		for (int i = 0; i < k; i++)
			cout << setfill(' ') << setw(3) << max_stamps[i];
		cout << " ->" << setfill(' ') << setw(3) << max_attainable << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

