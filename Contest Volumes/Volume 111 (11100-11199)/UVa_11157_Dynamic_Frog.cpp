
/*
	UVa 11157 - Dynamic Frog

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11157_Dynamic_Frog.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;

/*
The problem can be solved by a simple greedy algorithm. 
If the current rock is i, then check the rock i+1. 
  If rock i+1 is big, then land on it. 
  If rock i+1 is small, then land on rock i+2. 
Start at the left bank and repeat the process until reaching the right bank. 
Then return back to the left bank using the remaining rocks.
*/

const int N_max = 100;

struct stone {
	char type_;
	int m_;
} stones[N_max + 2] = {{'B', 0}};

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N, D;
		scanf("%d %d", &N, &D);
		stones[N + 1].type_ = 'B';
		stones[N + 1].m_ = D;
		for (int n = 1; n <= N; n++) {
			char s[16];
			scanf("%s", s);
			stones[n].type_ = s[0], stones[n].m_ = atoi(s + 2);
		}
#ifdef DEBUG
		for (int n = 0; n <= N + 1; n++)
			printf("%c-%d%c", stones[n].type_, stones[n].m_, ((n <= N) ? ' ' : '\n'));
#endif
		int max_d = 0;
		if (N) {
#ifdef DEBUG
			puts("left to right");
#endif
			for (int i = 0; i <= N; ) {
				if (stones[i + 1].type_ == 'B') {
					max_d = max(max_d, stones[i + 1].m_ - stones[i].m_);
#ifdef DEBUG
					printf("%d - %d: %d %d\n", i, i + 1, stones[i + 1].m_ - stones[i].m_, max_d);
#endif
					i++;
				}
				else {
					max_d = max(max_d, stones[i + 2].m_ - stones[i].m_);
#ifdef DEBUG
					printf("%d - %d: %d %d\n", i, i + 2, stones[i + 2].m_ - stones[i].m_, max_d);
#endif
					i += 2;
					if (stones[i].type_ == 'S')
						stones[i].type_ = 0; // will not exist on the way back to the left bank
				}
			}
#ifdef DEBUG
			puts("right to left");
#endif
			for (int i = N + 1; i > 0; ) {
				int j = i - 1;
				for ( ; j > 0 && !stones[j].type_; j--)
					;
				max_d = max(max_d, stones[i].m_ - stones[j].m_);
#ifdef DEBUG
				printf("%d - %d: %d %d\n", i, j, stones[i].m_ - stones[j].m_, max_d);
#endif
				i = j;
			}
		}
		else
			max_d = D;
		printf("Case %d: %d\n", t, max_d);
	}
	return 0;
}

