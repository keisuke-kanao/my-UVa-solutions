
/*
	UVa 1260 - Sales

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1260_Sales.cpp
*/

#include <cstdio>

const int n_max = 1000;

int sales[n_max];

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &sales[i]);
		int c = 0;
		for (int i = 1; i < n; i++)
			for (int j = 0; j < i; j++)
				if (sales[j] <= sales[i])
					c++;
		printf("%d\n", c);
	}
	return 0;
}

