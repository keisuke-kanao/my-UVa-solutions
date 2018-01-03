
/*
	UVa 760 - DNA Sequencing

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_760_DNA_Sequencing.cpp
*/

/*
function LCSubstr(S[1..m], T[1..n])
    L := array(1..m, 1..n)
    z := 0
    ret := {}
    for i := 1..m
        for j := 1..n
            if S[i] == T[j]
                if i == 1 or j == 1
                    L[i,j] := 1
                else
                    L[i,j] := L[i-1,j-1] + 1
                if L[i,j] > z
                    z := L[i,j]
                    ret := {S[i-z+1..i]}
                else
                if L[i,j] == z
                    ret := ret Åæ {S[i-z+1..i]}
            else 
                L[i,j] := 0
    return ret
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

const int nr_chars_max = 300;

int lengths[nr_chars_max][nr_chars_max], indices[nr_chars_max];
char lcss[nr_chars_max][nr_chars_max + 1];

int compare_string(const void* i,const void* j)
{
	return strcmp(reinterpret_cast<const char*>(i), reinterpret_cast<const char*>(j));
}

int main()
{
	char s[nr_chars_max + 1], t[nr_chars_max + 1];
	while (true) {
		gets(s);
		gets(t);
		int m = strlen(s), n = strlen(t), longest = 0, nr_lcss;
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++) {
				if (s[i] == t[j]) {
					if (i == 0 || j == 0)
						lengths[i][j] = 1;
					else
						lengths[i][j] = lengths[i - 1][j - 1] + 1;
					if (lengths[i][j] > longest) {
						longest = lengths[i][j];
						nr_lcss = 1;
						indices[0] = i;
					}
					else {
						if (lengths[i][j] == longest)
							indices[nr_lcss++] = i;
					}
				}
				else
					lengths[i][j] = 0;
			}
		if (longest) {
			for (int i = 0; i < nr_lcss; i++) {
				strncpy(lcss[i], s + indices[i] - longest + 1, longest);
				lcss[i][longest] = '\0';
			}
			qsort(lcss, nr_lcss, nr_chars_max + 1, compare_string);
			for (int i = 0, j = 0; i < nr_lcss; i++) {
				if (i) {
					if (strcmp(lcss[j], lcss[i])) {
						j = i;
						puts(lcss[i]);
					}
				}
				else
					puts(lcss[i]);
			}
		}
		else
			puts("No common sequence.");
		if (!gets(s))
			break;
		putchar('\n');
	}
	return 0;
}

