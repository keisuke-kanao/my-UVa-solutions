
/*
	UVa 11567 - Moliu Number Generator

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11567_Moliu_Number_Generator.cpp
*/

#include <cstdio>

int main()
{
	unsigned int S;
	while (scanf("%u", &S) != EOF) {
		int nr_ops = 0;
		while (S > 1) {
			if (!(S & 1)) {
				S >>= 1;
				nr_ops++;
			}
			else {
				unsigned int d = (S - 1) >> 1;
				if (d > 1 && d & 1)
					S = (S + 1) >> 1;
				else
					S = d;
				nr_ops += 2;
			}
#ifdef DEBUG
			printf("%u %d\n", S, nr_ops);
#endif
		}
		if (S)
			nr_ops++;
		printf("%d\n", nr_ops);
	}
	return 0;
}

