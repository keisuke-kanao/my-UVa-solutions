
/*
	UVa 1592 - Database

	To build using Visual Studio 2015:
		cl -EHsc -O2 UVa_1592_Database.cpp
*/

#include <map>
#include <cstdio>
#include <cstring>
using namespace std;

const int n_max = 10000, m_max = 10, nr_chars_max = 81;
char records[n_max][nr_chars_max + 1];
size_t values[n_max][m_max];

struct svalue {
	const char* s_;

	svalue(const char* s) : s_(s) {}

	bool operator<(const svalue& sv) const {return strcmp(s_, sv.s_) < 0;}
	bool operator==(const svalue& sv) const {return !strcmp(s_, sv.s_);}
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
			map<svalue, size_t> svalues;
			for (int i = 0; i < n; i++) {
#ifdef ONLINE_JUDGE
				fgets(records[i], nr_chars_max + 1, stdin);
#else
				gets_s(records[i], nr_chars_max + 1);
#endif
				char *p = records[i], *q = records[i];
				for (int j = 0; j < m; j++) {
					while (*p && *p != ',')
						p++;
					*p++ ='\0';
					pair<map<svalue, size_t>::iterator, bool> r = svalues.insert(make_pair(svalue(q), svalues.size()));
					values[i][j] = r.first->second;
					q = p;
				}
			}
			for (int j = 0; j < m - 1 && pnf; j++)
				for (int k = j + 1; k < m && pnf; k++) {
					map<pair<size_t, size_t>, int> value_pairs;
					for (int i = 0; i < n && pnf; i++) {
						pair<map<pair<size_t, size_t>, int>::iterator, bool> r = value_pairs.insert(make_pair(make_pair(values[i][j], values[i][k]), i));
						if (!r.second) {
							pnf = false;
							r1 = r.first->second + 1, r2 = i + 1;
							c1 = j + 1, c2 = k + 1;
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

