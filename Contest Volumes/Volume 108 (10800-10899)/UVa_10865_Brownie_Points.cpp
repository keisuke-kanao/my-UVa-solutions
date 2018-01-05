
/*
	UVa 10865 - Brownie Points

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10865_Brownie_Points.cpp
*/

#include <utility>
#include <cstdio>
using namespace std;

const int n_max = 200000;
pair<int, int> points[n_max];

int main()
{
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			scanf("%d %d", &points[i].first, &points[i].second);
		int cx = points[n / 2].first, cy = points[n / 2].second;
		int nr_stan = 0, nr_ollie = 0;
		for (int i = 0; i < n; i++) {
			pair<int, int>& p = points[i];
			if (p.first == cx || p.second == cy)
				;
			else if (p.first > cx && p.second > cy || p.first < cx && p.second < cy)
				nr_stan++;
			else
				nr_ollie++;
		}
		printf("%d %d\n", nr_stan, nr_ollie);
	}
	return 0;
}

