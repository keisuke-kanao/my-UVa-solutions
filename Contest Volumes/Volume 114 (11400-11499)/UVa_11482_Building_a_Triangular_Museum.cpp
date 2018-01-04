
/*
	UVa 11482 - Building a Triangular Museum

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11482_Building_a_Triangular_Museum.cpp
*/

#include <cstdio>

const int M_max = 100, N_max = 100;
char buff[M_max * 2 * N_max + 1];

int main()
{
	for (int x = 1; ; x++) {
		int M, N;
		scanf("%d %d", &M, &N);
		if (!M)
			break;
		printf("Triangular Museum %d\n", x);
		for (int n = 1, indent = M * N - 1; n <= N; n++)
			for (int m = 0, s = 0, t = 2 * (M - 1); m < M; m++, indent--, s += 2, t -= 2) {
				char* p = buff;
				for (int i = 0; i < indent; i++)
					*p++ = ' ';
				for (int i = 0; i < n; i++) {
					*p++ = '/';
					char c = (m < M - 1) ? ' ' : '_';
					for (int j = 0; j < s; j++)
						*p++ = c;
					*p++ = '\\';
					if (i < n - 1)
						for (int j = 0; j < t; j++)
							*p++ = ' ';
				}
				*p = '\0';
				puts(buff);
			}
		putchar('\n');
	}
	return 0;
}

