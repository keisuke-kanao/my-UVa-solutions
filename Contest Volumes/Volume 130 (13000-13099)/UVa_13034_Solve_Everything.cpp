
/*
	UVa 13034 - Solve Everything :-)

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_13034_Solve_Everything.cpp
*/

#include <cstdio>

int main()
{
	int S;
	scanf("%d", &S);
	for (int s = 1; s <= S; s++) {
		const int nr_problems = 13;
		bool yes = true;
		for (int i = nr_problems; i; i--) {
			int j;
			scanf("%d", &j);
			if (j <= 0)
				yes = false;
		}
		printf("Set #%d: %s\n", s, ((yes) ? "Yes" : "No"));
	}
	return 0;
}

