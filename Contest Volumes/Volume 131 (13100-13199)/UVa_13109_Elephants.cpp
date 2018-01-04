
/*
	UVa 13109 - Elephants

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_13109_Elephants.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int M_max = 100000;
int elephants[M_max];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int M, W;
		scanf ("%d %d", &M, &W);
		int i, s;
		for (i = 0; i < M; i++)
			scanf("%d", &elephants[i]);
		sort(elephants, elephants + M);
		for (i = 0, s = 0; i < M; i++)
			if ((s += elephants[i]) > W)
				break;
		printf("%d\n", i);
	}
	return 0;
}

