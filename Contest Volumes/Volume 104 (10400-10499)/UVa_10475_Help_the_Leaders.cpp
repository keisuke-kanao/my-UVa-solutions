
/*
	UVa 10475 - Help the Leaders

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10475_Help_the_Leaders.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
using namespace std;

const int t_max = 16, nr_chars_max = 15;

struct topic {
	int length_;
	char s_[nr_chars_max + 1];
	topic() : length_(0) {}
	topic(const char* s)
		: length_(strlen(s))
	{
		transform(s, s + length_, s_, (int(*)(int))toupper);
		s_[length_] = '\0';
	}
} topics[t_max];

int compare_topic(const void* i, const void* j)
{
	const topic *ti = reinterpret_cast<const topic*>(i), *tj = reinterpret_cast<const topic*>(j);
	return (ti->length_ != tj->length_) ? tj->length_ - ti->length_ : strcmp(ti->s_, tj->s_);
}

bool prohibited_pairs[t_max][t_max];

void help_leader(int t, int s, int ti, int si, int group[])
{
	if (si == s) {
		for (int i = 0; i < s; i++)
			printf("%s%c", topics[group[i]].s_, (i < s - 1) ? ' ' : '\n');
	}
	else if (t - ti > s - si) {
		for (int i = ti + 1; i < t; i++) {
			int j;
			for (j = 0; j < si; j++)
				if (prohibited_pairs[i][group[j]])
					break;
			if (j == si) {
				group[si] = i;
				help_leader(t, s, i, si + 1, group);
			}
		}
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	for (int sn = 1; sn <= n; sn++) {
		int t, p, s;
		scanf("%d %d %d", &t, &p, &s);
		for (int i = 0; i < t; i++) {
			scanf("%s", topics[i].s_);
			topics[i] = topics[i].s_;
		}
		qsort(topics, t, sizeof(topic), compare_topic);
		for (int i = 0; i < t; i++)
			for (int j = 0; j < t; j++)
				prohibited_pairs[i][j] = false;
		for (int i = 0; i < p; i++) {
			topic ti, tj;
			scanf("%s %s", ti.s_, tj.s_);
			ti = ti.s_; tj = tj.s_;
			int pi = reinterpret_cast<topic*>(bsearch(&ti, topics, t, sizeof(topic), compare_topic)) - topics,
				pj = reinterpret_cast<topic*>(bsearch(&tj, topics, t, sizeof(topic), compare_topic)) - topics;
			prohibited_pairs[pi][pj] = prohibited_pairs[pj][pi] = true;
		}
		printf("Set %d:\n", sn);
		for (int i = 0; i < t - s + 1; i++) {
			int group[t_max]; // array of topic indices
			group[0] = i;
			help_leader(t, s, i, 1, group);
		}
		putchar('\n');
	}
	return 0;
}

