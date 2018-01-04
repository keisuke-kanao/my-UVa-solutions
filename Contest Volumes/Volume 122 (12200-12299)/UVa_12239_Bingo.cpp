
/*
	UVa 12239 - Bingo!

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12239_Bingo.cpp
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

const int N_max = 90;
int balls[N_max + 1];
bool called[N_max + 1];

int main()
{
	while (true) {
		int N, B;
		scanf("%d %d", &N, &B);
		if (!N && !B)
			break;
		memset(called, 0, sizeof(called));
		for (int i = 0; i < B; i++)
			scanf("%d", &balls[i]);
		int nr_called = 0;
		for (int i = 0; i < B - 1; i++) {
			for (int j = i + 1; j < B; j++) {
				int k = abs(balls[i] - balls[j]);
				if (k > 0 && k <= N && !called[k]) {
					called[k] = true;
					if (++nr_called == N)
						break;
				}
			}
			if (nr_called == N)
				break;
		}
		puts((nr_called == N) ? "Y" : "N");
	}
	return 0;
}

/*
#include <cstdio>
#include <cstdlib>
#include <set>
using namespace std;

int main()
{
	const int B_max = 90;
	int N, B, balls[B_max + 1];
	while (true) {
		scanf("%d %d", &N, & B);
		if (!N && !B)
			break;
		set<int> called;
		for (int i = 0; i < B; i++)
			scanf("%d", &balls[i]);
		for (int i = 0; i < B; i++)
			for (int j = i; j < B; j++) {
				int d = abs(balls[i] - balls[j]);
				if (d <= N)
					called.insert(d);
			}
		puts((called.size() == N + 1) ? "Y" : "N");
	}
	return 0;
}
*/

