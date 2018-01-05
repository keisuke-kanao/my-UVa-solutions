
/*
	UVa 11056 - Formula 1

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11056_Formula_1.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#ifdef ONLINE_JUDGE
#define _stricmp strcasecmp
#endif

const int nr_name_chars_max = 31, nr_pilots_max = 100;

struct pilot {
	char name_[nr_name_chars_max + 1];
	int lap_;

	bool operator<(const pilot& p) const;
} pilots[nr_pilots_max];

bool pilot::operator<(const pilot& p) const
{
	if (lap_ < p.lap_)
		return true;
	else if (lap_ > p.lap_)
		return false;
	else
		return _stricmp(name_, p.name_) < 0;
}

int main()
{
	int n;
	while (scanf("%d", &n) != EOF) {
		for (int i = 0; i < n; i++) {
			int m, s, ms;
			scanf("%s %*s %d %*s %d %*s %d %*s", pilots[i].name_, &m, &s, &ms);
			pilots[i].lap_ = m * 60000 + s * 1000 + ms;
#ifdef DEBUG
			printf("%s %d\n", pilots[i].name_, pilots[i].lap_);
#endif
		}
		sort(pilots, pilots + n);
		for (int i = 0, r = 1; i < n; r++) {
			printf("Row %d\n", r);
			puts(pilots[i++].name_);
			if (i < n)
				puts(pilots[i++].name_);
		}
		putchar('\n');
	}
	return 0;
}

