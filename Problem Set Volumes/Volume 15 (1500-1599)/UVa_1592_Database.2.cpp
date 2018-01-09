
/*
	UVa 1592 - Database

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_1592_Database.cpp

	Another accepted solution.
*/

#include <vector>
#include <map>
#include <cstdio>
#include <cstring>
using namespace std;

const int n_max = 10000, m_max = 10, nr_chars_max = 81;
char records[n_max][nr_chars_max + 1];

struct key {
	const char *p_, *q_;

	key(const char* p, const char *q) : p_(p), q_(q) {}

	bool operator<(const key& k) const {
		int r = strcmp(p_, k.p_);
		if (r < 0)
			return true;
		else if (r > 0)
			return false;
		else
			return strcmp(q_, k.q_) < 0;
	}
	bool operator==(const key& k) const {return !strcmp(p_, k.p_) && !strcmp(q_, k.q_);}
};

int main()
{
	int n, m;
	while (scanf("%d %d", &n, &m) != EOF) {
		while (getchar() != '\n')
			;
		bool pnf = true;
		int r1, r2, c1, c2;
		if (m == 1) {
			for (int i = 0; i < n; i++)
#ifdef ONLINE_JUDGE
				fgets(records[i], nr_chars_max + 1, stdin);
#else
				gets_s(records[i], nr_chars_max + 1);
#endif
		}
		else {
			vector< vector< map<key, int> > > maps(m, vector< map<key, int> >(m));
			for (int i = 0; i < n; i++) {
#ifdef ONLINE_JUDGE
				fgets(records[i], nr_chars_max + 1, stdin);
#else
				gets_s(records[i], nr_chars_max + 1);
#endif
				if (pnf) {
					char *p = records[i], *ps[m_max];
					for (int j = 0; ; ) {
						ps[j++] = p;
						if (j == m)
							break;
						while (*p != ',')
							p++;
						*p++ = '\0';
					}
					for (int j = 0; j < m - 1 && pnf; j++)
						for (int k = j + 1; k < m && pnf; k++) {
							pair<map<key, int>::iterator, bool> result = maps[j][k].insert(make_pair(key(ps[j], ps[k]), i));
							if (!result.second) {
								pnf = false;
								r1 = result.first->second + 1, r2 = i + 1;
								c1 = j + 1, c2 = k + 1;
							}
						}
				}
			}
		}
		if (pnf)
			puts("YES");
		else
			printf("NO\n%d %d\n%d %d\n", r1, r2, c1, c2);
	}
	return 0;
}

