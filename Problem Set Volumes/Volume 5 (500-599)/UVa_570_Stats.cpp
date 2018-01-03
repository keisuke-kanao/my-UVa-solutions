
/*
	UVa 570 - Stats

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_570_Stats.cpp

	from 1997 ACM South Central USA Programming Contest, Problem #6
		(http://www.cs.nthu.edu.tw/~progcont/ACM/ProblemSetArchive/B_US_SouthCen/1997/Stats.html)
*/

#include <cstdio>
#include <cstring>

const int nr_player_digits = 5;

struct stat {
	int g_; // number of games played
	int h_, k_, e_, b_, d_;
} stats[nr_player_digits + 1][nr_player_digits + 1];

int main()
{
	int n, p, g = 0;
	double h, k, e, b, d;
	char key[2];
	while (scanf("%s", key) != EOF) {
		switch (key[0]) {
		case 'C':
			scanf("%d", &n);
			while (n--) {
				scanf("%d", &p);
				stats[p / 10][p % 10].g_++;
			}
			g++;
			break;
		case 'H':
			scanf("%d", &p);
			stats[p / 10][p % 10].h_++;
			break;
		case 'K':
			scanf("%d", &p);
			stats[p / 10][p % 10].k_++;
			break;
		case 'E':
			scanf("%d", &p);
			stats[p / 10][p % 10].e_++;
			break;
		case 'B':
			scanf("%d", &p);
			stats[p / 10][p % 10].b_++;
			break;
		case 'D':
			scanf("%d", &p);
			stats[p / 10][p % 10].d_++;
			break;
		case 'R':
			puts("Player  Hit Pct    KPG      BPG      DPG");
			puts("-----------------------------------------");
			h = k = e = b = d = 0;
			for (int i = 0; i <= nr_player_digits; i++)
				for (int j = 0; j <= nr_player_digits; j++)
					if (stats[i][j].g_) {
						const stat& s = stats[i][j];
						printf("%02d      %+5.3lf  %7.3lf  %7.3lf  %7.3lf\n",
							i * 10 + j,
							((s.k_ || s.e_ || s.h_) ?
								(static_cast<double>(s.k_) - s.e_) / (static_cast<double>(s.k_) + s.e_ + s.h_) : 0.0),
							static_cast<double>(s.k_) / s.g_,
							static_cast<double>(s.b_) / s.g_,
							static_cast<double>(s.d_) / s.g_
						);
						h += s.h_, k += s.k_, e += s.e_, b += s.b_, d += s.d_;
					}
			printf("team    %+5.3lf  %7.3lf  %7.3lf  %7.3lf\n\n",
				(k - e) / (k + e + h), k / g, b / g, d / g);
			g = 0;
			memset(stats, 0, sizeof(stats));
			break;
		}
	}
	return 0;
}

