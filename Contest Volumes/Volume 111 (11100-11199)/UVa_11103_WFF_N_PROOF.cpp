
/*
	UVa 11103 - WFF 'N PROOF

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11103_WFF_N_PROOF.cpp

	from Waterloo ACM Programming Contest September 24, 2006, Problem D
		(http://acm.student.cs.uwaterloo.ca/~acm00/060924/data/)
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cctype>
using namespace std;

const int nr_chars_max = 100;
char symbols[nr_chars_max + 1];
int indices[nr_chars_max];

bool compare_symbol(int i, int j)
{
	char ci = symbols[i], cj = symbols[j];
	if (isupper(ci) && isupper(cj)) {
		if (ci == 'N' && cj == 'N')
			return i < j;
		else if (ci == 'N')
			return true;
		else if (cj == 'N')
			return false;
		else
			return i < j;
	}
	else if (islower(ci) && islower(cj))
		return i < j;
	else
		return ci < cj;
}

int main()
{
	while (true) {
		scanf("%s", symbols);
		if (!strcmp(symbols, "0"))
			break;
		int nr_symbols = strlen(symbols), nr_Ns = 0, nr_KACEs = 0, nr_variables = 0;
		for (int i = 0; i < nr_symbols; i++) {
			indices[i] = i;
			switch (symbols[i]) {
			case 'N':
				nr_Ns++; break;
			case 'K': case 'A': case 'C': case 'E':
				nr_KACEs++; break;
			case 'p': case 'q': case 'r': case 's': case 't':
				nr_variables++; break;
			}
		}
		sort(indices, indices + nr_symbols, compare_symbol);
#ifdef DEBUG
		for (int i = 0; i < nr_symbols; i++)
			putchar(symbols[indices[i]]);
		putchar('\n');
#endif
		int nr_wff_KACEs = nr_KACEs, nr_wff_variables = nr_variables;
		if (nr_wff_variables) {
			if (nr_wff_KACEs > nr_wff_variables - 1)
				nr_wff_KACEs = nr_wff_variables - 1;
			else
				nr_wff_variables = nr_wff_KACEs + 1;
			for (int i = 0; i < nr_Ns; i++)
				putchar('N');
			for (int i = nr_Ns, j = nr_wff_KACEs; j; i++, j--)
				putchar(symbols[indices[i]]);
			for (int i = nr_Ns + nr_KACEs, j = nr_wff_variables; j; i++, j--)
				putchar(symbols[indices[i]]);
			putchar('\n');
		}
		else
			puts("no WFF possible");
	}
	return 0;
}

