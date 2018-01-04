
/*
	UVa 11917 - Do Your Own Homework

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11917_Do_Your_Own_Homework.cpp
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

const int n_max = 100, nr_chars_max = 31;

struct subject {
	char name_[nr_chars_max + 1];
	int days_;
} subjects[n_max];

int compare_subject(const void* i, const void* j)
{
	const char *s = reinterpret_cast<const subject*>(i)->name_, *t = reinterpret_cast<const subject*>(j)->name_;
	return strcmp(s, t);
}

int main()
{
	int t;
	scanf("%d", &t);
	for (int case_nr = 1; case_nr <= t; case_nr++) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%s %d", subjects[i].name_, &subjects[i].days_);
		subject sbj;
		scanf("%d %s", &sbj.days_, sbj.name_);
		qsort(subjects, n, sizeof(subject), compare_subject);
		subject* s = reinterpret_cast<subject*>(bsearch(&sbj, subjects, n, sizeof(subject), compare_subject));
		printf("Case %d: ", case_nr);
		if (s) {
			if (s->days_ <= sbj.days_)
				puts("Yesss");
			else if (s->days_ <= sbj.days_ + 5)
				puts("Late");
			else
				puts("Do your own homework!");
		}
		else
			puts("Do your own homework!");
	}
	return 0;
}

