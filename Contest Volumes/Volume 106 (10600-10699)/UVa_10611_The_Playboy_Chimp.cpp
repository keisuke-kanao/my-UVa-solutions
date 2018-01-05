
/*
	UVa 10611 - The Playboy Chimp

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10611_The_Playboy_Chimp.cpp
*/

#include <algorithm>
#include <iterator>
#include <cstdio>
using namespace std;

const int n_max = 50000;
int heights[n_max];

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &heights[i]);
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		int h;
		scanf("%d", &h);
		int li = distance(heights, lower_bound(heights, heights + n, h));
		if (li < n) {
			while (li >= 0 && heights[li] >= h)
				li--;
		}
		else
			li = n - 1;
		if (li >= 0)
			printf("%d ", heights[li]);
		else
			printf("X ");
		int hi = distance(heights, upper_bound(heights, heights + n, h));
		if (hi < n)
			printf("%d\n", heights[hi]);
		else
			printf("X\n");
	}
	return 0;
}

