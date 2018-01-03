
/*
	UVa 1215 - String Cutting

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1215_String_Cutting.cpp
*/

#include <algorithm>
#include <vector>
#include <iterator>
#include <cstdio>
#include <cstring>
using namespace std;

const int n_max =  10000, k_max = 1000, nr_letters = 'z' - 'a' + 1;
char s[n_max];
int cuts[k_max];
bool l_letters[nr_letters], h_letters[nr_letters];

int main()
{
	int nr_sets;
	scanf("%d", &nr_sets);
	while (nr_sets--) {
		int k;
		scanf("%d", &k);
		for (int i = 0; i < k; i++)
			scanf("%d", &cuts[i]);
		scanf("%s", s);
		int length = 0;
		for (char* p = s; *p; p++, length++)
			*p -= 'a';
		vector<int> positions;
		positions.push_back(0);
		positions.push_back(length);
		int cost = 0;
		for (int i = 0; i < k; i++) {
			int m = cuts[i];
			vector<int>::iterator pi = lower_bound(positions.begin(), positions.end(), m);
			int l = *prev(pi), h = *pi;
			memset(l_letters, 0, sizeof(l_letters));
			for (int j = l; j < m; j++)
				l_letters[s[j]] = true;
			memset(h_letters, 0, sizeof(h_letters));
			for (int j = m; j < h; j++)
				h_letters[s[j]] = true;
			for (int i = 0; i < nr_letters; i++)
				if (l_letters[i] ^ h_letters[i])
					cost++;
			positions.insert(pi, m);
		}
		printf("%d\n", cost);
	}
	return 0;
}

