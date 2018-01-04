
/*
	UVa 12798 - Handball

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12798_Handball.cpp
*/

#include <cstdio>

int main()
{
	int N, M;
	while (scanf("%d %d", &N, &M) != EOF) {
		int n = 0;
		for (int i = 0; i < N; i++) {
			bool scored = true;
			for (int j = 0; j < M; j++) {
				int X;
				scanf("%d", &X);
				if (scored && !X)
					scored = false;
			}
			if (scored)
				n++;
		}
		printf("%d\n", n);
	}
	return 0;
}

