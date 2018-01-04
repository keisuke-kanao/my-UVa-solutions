
/*
	UVa 11847 - Cut the Silver Bar

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11847_Cut_the_Silver_Bar.cpp
*/

#include <cstdio>
#include <cstring>

const int n_max = 20000;
int nr_cuts[n_max + 1];

int get_nr_cuts(int n)
{
	return (nr_cuts[n] != -1) ? nr_cuts[n] : get_nr_cuts(n / 2) + 1;
}

int main()
{
	memset(nr_cuts, -1, sizeof(nr_cuts));
	nr_cuts[1] = 0;
	for (int i = 2; i <= n_max; i++)
		nr_cuts[i] = get_nr_cuts(i);
	while (true) {
		int n;
		scanf("%d", &n);
		if (!n)
			break;
		printf("%d\n", nr_cuts[n]);
	}
	return 0;
}

