
/*
	UVa 11795 - Mega Man's Mission

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11795_Mega_Mans_Mission.cpp
*/

#include <queue>
#include <utility>
#include <cstdio>
using namespace std;

const int N_max = 16, Nb_max = 1 << N_max;

int weapons[N_max + 1];
long long nr_ways[Nb_max];

int s_to_b(const char* s)
{
	int b = *s - '0';
	for (s++; *s; s++) {
		b <<= 1;
		b += *s - '0';
	}
	return b;
}

int main()
{
	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++) {
		int N;
		scanf("%d", &N);
		for (int i = 0; i <= N; i++) {
			char s[N_max + 1];
			scanf("%s", s);
			weapons[i] = s_to_b(s);
		}
		int Nb = 1 << N;
		for (int i = 0; i < Nb; i++)
			nr_ways[i] = 0;
		queue< pair<int, int> > q;
		q.push(make_pair(0, weapons[0]));
		nr_ways[0] = 1;
		while (!q.empty()) {
			int destroyed = q.front().first, weapon = q.front().second;
			q.pop();
#ifdef DEBUG
			printf("%04x %04x\n", destroyed, weapon);
#endif
			for (int i = 1, b = 1 << (N - 1); i <= N; i++, b >>= 1)
				if (!(destroyed & b) && weapon & b) {
					int d = destroyed | b, w = weapon | weapons[i];
					if (!nr_ways[d])
						q.push(make_pair(d, w));
					nr_ways[d] += nr_ways[destroyed];
				}
		}
		printf("Case %d: %lld\n", t, nr_ways[Nb - 1]);
	}
	return 0;
}

