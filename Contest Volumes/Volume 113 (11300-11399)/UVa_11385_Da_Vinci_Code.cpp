
/*
	UVa 11385 - Da Vinci Code

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11385_Da_Vinci_Code.cpp
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>

int compare_fib(const void* i, const void* j)
{
	return *reinterpret_cast<const unsigned int*>(i) - *reinterpret_cast<const unsigned int*>(j);
}

int main()
{
	const int nr_fibs_max = 46;
	unsigned int fibs[nr_fibs_max];
	fibs[0] = 1; fibs[1] = 2;
	for (int i = 2; i < nr_fibs_max; i++)
		fibs[i] = fibs[i - 1] + fibs[i - 2];
#ifdef DEBUG
	printf("%u\n", fibs[nr_fibs_max - 1]);
#endif

	int t;
	scanf("%d", &t);
	unsigned int fs[nr_fibs_max];
	const int nr_chars_max = 100;
	char cs[nr_chars_max + 1], s[nr_chars_max + 1], ds[nr_fibs_max + 1];
	while (t--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%u", &fs[i]);
		getchar();
		gets(cs);
		int sl = 0;
		for (const char* p = cs; *p; p++)
			if (isupper(*p))
				s[sl++] = *p;
		s[sl] = '\0';
#ifdef DEBUG
		puts(s);
#endif
		int max_ifs = -1;
		memset(ds, ' ', sizeof(ds));
		for (int i = 0; i < n; i++) {
			unsigned int* pfs =
				reinterpret_cast<unsigned int*>(bsearch (&fs[i], fibs, nr_fibs_max, sizeof(unsigned int), compare_fib));
			if (pfs) {
				int ifs = pfs - fibs;
				if (i < sl) {
					ds[ifs] = s[i];
					if (ifs > max_ifs)
					max_ifs = ifs;
				}
			}
		}
		ds[max_ifs + 1] = '\0';
		puts(ds);
	}
	return 0;
}

