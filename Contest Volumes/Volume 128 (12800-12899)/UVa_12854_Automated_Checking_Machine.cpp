
/*
	UVa 12854 - Automated Checking Machine

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12854_Automated_Checking_Machine.cpp
*/

#include <cstdio>

int main()
{
	const int nr_points = 5;
	int X[nr_points];
	while (scanf("%d", &X[0]) != EOF) {
		for (int i = 1; i < nr_points; i++)
			scanf("%d", &X[i]);
		int compatible = 1;
		for (int i = 0; i < nr_points; i++) {
			int Y;
			scanf("%d", &Y);
			compatible &= X[i] ^ Y;
		}
		puts((compatible) ? "Y": "N");
	}
	return 0;
}

