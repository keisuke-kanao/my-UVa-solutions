
/*
	UVa 10730 - Antiarithmetic?

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10730_Antiarithmetic.cpp

	from 25 September, 2004 - Waterloo local contest, Problem D
		(http://acm.student.cs.uwaterloo.ca/~acm00/040925/data/)
*/

#include <cstdio>

const int n_max = 10000;
int numbers[n_max], positions[n_max];

int main()
{
	while (true) {
		int n;
		scanf("%d:", &n);
		if (!n)
			break;
		for (int i = 0; i < n; i++) {
			scanf("%d", &numbers[i]);
			positions[numbers[i]] = i;
		}
		bool yes = true;
		for (int i = 0; i < n - 2; i++) {
			for (int j = i + 1; j < n - 1; j++) {
				int k = 2 * numbers[j] - numbers[i];
				if (k >= 0 && k < n && positions[k] > j) {
#ifdef DEBUG
					printf("%d %d %d\n", i, j, positions[k]);
#endif
					yes = false; break;
				}
			}
			if (!yes)
				break;
		}
		puts((yes) ? "yes" : "no");
	}
	return 0;
}

/*
Sample input

3: 0 2 1 
5: 2 0 1 3 4
6: 2 4 3 5 0 1
0

Output for sample input

yes
no
yes

*/

