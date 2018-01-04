
/*
	UVa 12592 - Slogan Learning of Princess

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12592_Slogan_Learning_of_Princess.cpp
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

const int n_max = 20, nr_chars_max = 100;

struct slogan {
	char first_[nr_chars_max + 1];
	char second_[nr_chars_max + 1];
} slogans[n_max];

int compare_slogan(const void* i, const void* j)
{
	return strcmp(reinterpret_cast<const slogan*>(i)->first_, reinterpret_cast<const slogan*>(j)->first_);
}

int main()
{
	int n;
	scanf("%d\n", &n);
	for (int i = 0; i < n; i++) {
		gets(slogans[i].first_);
		gets(slogans[i].second_);
	}
	qsort(slogans, n, sizeof(slogan), compare_slogan);
	int q;
	scanf("%d\n", &q);
	while (q--) {
		slogan s;
		gets(s.first_);
		slogan* ps = reinterpret_cast<slogan*>(bsearch(&s, slogans, n, sizeof(slogan), compare_slogan));
		puts(ps->second_);
	}
	return 0;
}

