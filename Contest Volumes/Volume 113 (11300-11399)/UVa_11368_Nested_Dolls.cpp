
/*
	UVa 11368 - Nested Dolls

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11368_Nested_Dolls.cpp
*/

#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

const int m_max = 20000, wh_max = 10000;

struct doll {
	bool lis_;
	int w_, h_;

	bool operator<(const doll& d) const {return (h_ != d.h_) ? h_ > d.h_ : w_ < d.w_;}
} dolls[m_max];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int m;
		scanf("%d", &m);
		for (int i = 0; i < m; i++)
			scanf("%d %d", &dolls[i].w_, &dolls[i].h_);
/*
Sort in non-increasing order of h. If two dolls have the same h, sort them in non-decreasing order of w.
Maintain a sorted array of available doll's w, initially empty.
Iterate through the dolls. 
Using a binary search, find the smallest available w greater than the current w and replace it with the current w. 
If none are available, increase the output count and add the current w to the end of the array. 

Each test case can be solved in O(m log m).
*/
		sort(dolls, dolls + m);
		vector<int> widths;
		widths.push_back(wh_max + 1);
		int nr = 0;
		for (int i = 0; i < m; i++) {
			int w = dolls[i].w_;
			size_t wi = lower_bound(widths.begin(), widths.end(), w + 1) - widths.begin();
			if (wi == widths.size() - 1) {
				nr++;
				widths.push_back(wh_max + 1);
			}
			widths[wi] = w;
		}
		printf("%d\n", nr);
	}
	return 0;
}

