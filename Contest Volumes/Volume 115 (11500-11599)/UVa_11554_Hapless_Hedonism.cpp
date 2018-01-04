
/*
	UVa 11554 - Hapless Hedonism

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11554_Hapless_Hedonism.cpp

	This problem is similer to 11401 - Triangle Counting.
*/

#include <cstdio>

const int n_max = 1000000;
long long nr_triangles[n_max + 1];

int main()
{
	nr_triangles[3] = 0; nr_triangles[4] = 1; nr_triangles[5] = 3;
	for (int n = 6; n <= n_max; n++) {
		long long k = (n - 2) / 2;
		nr_triangles[n] = nr_triangles[n - 1] + k * k;
		if (n & 1)
			nr_triangles[n] += k;
    }
#ifdef DEBUG
	printf("%lld\n", nr_triangles[n_max]);
#endif
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		printf("%lld\n", nr_triangles[n]);
	}
	return 0;
}

