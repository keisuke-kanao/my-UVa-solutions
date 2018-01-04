
/*
	UVa 11401 - Triangle Counting

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11401_Triangle_Counting.cpp
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
	while (true) {
		int n;
		scanf("%d", &n);
		if (n < 3)
			break;
		printf("%lld\n", nr_triangles[n]);
	}
	return 0;
}

