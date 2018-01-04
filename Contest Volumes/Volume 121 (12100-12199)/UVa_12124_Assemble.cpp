
/*
	UVa 12124 - Assemble

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12124_Assemble.cpp
*/

#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <cstdio>
using namespace std;

const int n_max = 1000, nr_chars_max = 20;

#ifdef DEBUG
void print_qualities(const map<int, int>& qualities)
{
	printf("%d\n  ", qualities.size());
	for (map<int, int>::const_iterator i = qualities.begin(); i != qualities.end(); ++i)
		printf("%d:%d ", i->first, i->second);
	putchar('\n');
}
#endif

int main()
{
	int t;
	scanf("%d", &t);
	while (t--) {
		int n, b;
		scanf("%d %d", &n, &b);
		int nr_types = 0;
		map<string, int> types;
		vector< map<int, int> > components;
		while (n--) {
			char type[nr_chars_max + 1];
			int price, quality;
			scanf("%s %*s %d %d", type, &price, &quality);
			pair<map<string, int>::iterator, bool> sr = types.insert(make_pair(string(type), nr_types));
			if (sr.second) {
				nr_types++;
				components.push_back(map<int, int>());
			}
			pair<map<int, int>::iterator, bool> cr = components[sr.first->second].insert(make_pair(quality, price));
			if (!cr.second && cr.first->second > price)
				cr.first->second = price;
		};
		vector< map<int, int> > qualities(nr_types);
		for (map<int, int>::const_iterator k = components[0].begin(); k != components[0].end(); ++k) {
			int q = k->first, p = k->second;
			if (p <= b)
				qualities[0].insert(make_pair(q, p));
		}
#ifdef DEBUG
		print_qualities(qualities[0]);
#endif
		for (int i = 1; i < nr_types; i++) {
			for (map<int, int>::const_iterator j = qualities[i - 1].begin(); j != qualities[i - 1].end(); ++j) {
				int quality = j->first, price = j->second;
				for (map<int, int>::const_iterator k = components[i].begin(); k != components[i].end(); ++k) {
					int q = min(quality, k->first), p = price + k->second;
					if (p <= b) {
						pair<map<int, int>::iterator, bool> qr = qualities[i].insert(make_pair(q, p));
						if (!qr.second && qr.first->second > p)
							qr.first->second = p;
					}
				}
			}
#ifdef DEBUG
			print_qualities(qualities[i]);
#endif
		}
		printf("%d\n", qualities[nr_types - 1].rbegin()->first);
	}
	return 0;
}

