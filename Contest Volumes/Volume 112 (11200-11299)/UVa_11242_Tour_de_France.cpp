
/*
	UVa 11242 - Tour de France

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11242_Tour_de_France.cpp
*/

#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>
using namespace std;

const int nr_clusters_max = 10;
int front_clusters[nr_clusters_max], rear_clusters[nr_clusters_max];
pair<int, int> drive_ratios[nr_clusters_max * nr_clusters_max];

bool compare_drive_ratio(const pair<int, int>&i, const pair<int, int>& j)
{
	return i.first * j.second < j.first * i.second;
}

int main()
{
	int f, r;
	while (true) {
		cin >> f;
		if (!f)
			break;
		cin >> r;
		for (int i = 0; i < f; i++)
			cin >> front_clusters[i];
		for (int i = 0; i < r; i++)
			cin >> rear_clusters[i];
		for (int i = 0; i < f; i++)
			for (int j = 0; j < r; j++)
				drive_ratios[i * r + j] = make_pair(front_clusters[i], rear_clusters[j]);
		int n = f * r;
		sort(drive_ratios, drive_ratios + n, compare_drive_ratio);
#ifdef DEBUG
		for (int i = 0; i < n; i++)
	 		cout << static_cast<double>(drive_ratios[i].first) / static_cast<double>(drive_ratios[i].second) << ' ';
		cout << endl;
#endif/
		double max_spread = 0.0;
		for (int i = 0; i < n - 1; i++)
			max_spread = max(max_spread, static_cast<double>(drive_ratios[i + 1].first * drive_ratios[i].second) /
				static_cast<double>(drive_ratios[i].first * drive_ratios[i + 1].second));
		cout << fixed << setprecision(2) << max_spread << endl;
	}
	return 0;
}

