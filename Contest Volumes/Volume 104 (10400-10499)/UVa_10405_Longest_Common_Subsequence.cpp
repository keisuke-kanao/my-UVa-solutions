
/*
	UVa 10405 - Longest Common Subsequence

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10405_Longest_Common_Subsequence.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

/*
function LCSLength(X[1..m], Y[1..n])
    C = array(0..m, 0..n)
    for i := 0..m
       C[i,0] = 0
    for j := 0..n
       C[0,j] = 0
    for i := 1..m
        for j := 1..n
            if X[i] = Y[j]
                C[i,j] := C[i-1,j-1] + 1
            else:
                C[i,j] := max(C[i,j-1], C[i-1,j])
    return C[m,n]
*/

const int nr_chars_max = 1024;
char first_s[nr_chars_max], second_s[nr_chars_max];
int lcs_c[2][nr_chars_max];

int lcs(int first_s_length, int second_s_length)
{
	memset(lcs_c[0], 0, sizeof(int) * (second_s_length + 1));
	memset(lcs_c[1], 0, sizeof(int) * (second_s_length + 1));
	for (int i = 1; i <= first_s_length; i++) {
		int ci = i % 2, pi = (i - 1) % 2;
		for (int j = 1; j <= second_s_length; j++) {
			if (first_s[i - 1] == second_s[j - 1])
				lcs_c[ci][j] = lcs_c[pi][j - 1] + 1;
			else
				lcs_c[ci][j] = max(lcs_c[ci][j - 1], lcs_c[pi][j]);
		}
	}
	return lcs_c[first_s_length % 2][second_s_length];
}

int main()
{
	while (gets(first_s)) {
		gets(second_s);
		printf("%d\n", lcs(strlen(first_s), strlen(second_s)));
	}
	return 0;
}

