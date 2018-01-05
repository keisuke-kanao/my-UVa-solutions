
/*
	UVa 10226 - Hardwood Species

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10226_Hardwood_Species.cpp

	from Waterloo local contest - 26 January, 2002 Problem C
		(http://acm.student.cs.uwaterloo.ca/~acm00/020126/data/)

	An accepted solution.
*/

#include <map>
#include <cstdio>
#include <cstring>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int nr_chars_max = 30;

struct tree {
   char name_[nr_chars_max + 1];

	bool operator<(const tree& t) const {return strcmp(name_, t.name_) < 0;}
	bool operator==(const tree& t) const {return !strcmp(name_, t.name_);}
};

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	int n;
	scanf("%d", &n);
	getchar();
	getchar();
	while (n--) {
		int nr_trees = 0;
		map<tree, int> trees;
		tree t;
		while (gets(t.name_) && t.name_[0] != '\0') {
			trees[t]++;
			nr_trees++;
		}
		double dn = static_cast<double>(nr_trees);
		for (map<tree, int>::const_iterator i = trees.begin(), e = trees.end(); i != e; i++)
			printf("%s %0.4lf\n",i->first.name_, static_cast<double>(i->second) * 100.0 / dn);
		if (n)
			putchar('\n');
   }
#ifdef __ELAPSED_TIME__
	fprintf(stderr, "elapsed time = %lf sec.\n", static_cast<double>(clock() - start) / CLOCKS_PER_SEC);
#endif
	return 0;
}

