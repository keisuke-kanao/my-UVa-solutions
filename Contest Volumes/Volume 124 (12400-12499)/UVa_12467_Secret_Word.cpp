
/*
	UVa 12467 - Secret Word

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12467_Secret_Word.cpp
*/

#include <cstdio>
#include <cstring>

const int nr_chars_max = 1000000;
char S[nr_chars_max + 1];
int lps[nr_chars_max];
  // length of the maximum matching proper prefix which is also a suffix of S[0..i]

int main()
{
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%s", S);
		int n = strlen(S);
		// apply KMP (Knuth-Morris-Pratt) algorithm 
		// where patten is an input string and text is the reverse of the input string
		// calculate lps[]
		lps[0] = 0; // lps[0] is always 0
		for (int i = 1, length = 0 /* length of the previous longest prefix suffix */; i < n; ) {
			if (S[i] == S[length])
				lps[i++] = ++length;
	        else {
    			if (length)
					length = lps[length - 1];
        	    else
            	    lps[i++] = 0;
			}
		}
		int max_length = 0, max_i;
		for (int i = n - 1, j = 0; i >= 0; ) {
			if (i >= 0 && S[j] == S[i])
				j++, i--;
			if (j > max_length)
				max_length = j, max_i = i + 1;
	        if (j == n)
				j = lps[j - 1];
 			// mismatch after j matches
			else if (i >= 0 && S[j] != S[i]) {
				// do not match lps[0..lps[j - 1]] characters, they will match anyway
				if (j)
					j = lps[j - 1];
				else
					i--;
			}
		}
#ifdef DEBUG
		printf("%d %d\n", max_i, max_length);
#endif
		S[max_i + max_length] = '\0';
		puts(&S[max_i]);
	}
	return 0;
}

