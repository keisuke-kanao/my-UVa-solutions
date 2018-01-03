
/*
	UVa 719 - Glass Beads

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_719_Glass_Beads.cpp
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

/*
This problem can be solved by concatenating the string with itself, build the Suffix Array, then find the first
suffix in Suffix Array sorted order that has length greater or equal to n.
*/

const int nr_chars_max = 10000;

typedef pair<int, int> ii;

#define MAX_N 100010                         // second approach: O(n log n)
char T[MAX_N];                   // the input string, up to 100K characters
int n;                                        // the length of input string
int RA[MAX_N], tempRA[MAX_N];        // rank array and temporary rank array
int SA[MAX_N], tempSA[MAX_N];    // suffix array and temporary suffix array
int c[MAX_N];                                    // for counting/radix sort

bool cmp(int a, int b) { return strcmp(T + a, T + b) < 0; }      // compare

void countingSort(int k) {                                          // O(n)
  int i, sum, maxi = max(300, n);   // up to 255 ASCII chars or length of n
  memset(c, 0, sizeof c);                          // clear frequency table
  for (i = 0; i < n; i++)       // count the frequency of each integer rank
    c[i + k < n ? RA[i + k] : 0]++;
  for (i = sum = 0; i < maxi; i++) {
    int t = c[i]; c[i] = sum; sum += t;
  }
  for (i = 0; i < n; i++)          // shuffle the suffix array if necessary
    tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
  for (i = 0; i < n; i++)                     // update the suffix array SA
    SA[i] = tempSA[i];
}

void constructSA() {         // this version can go up to 100000 characters
  int i, k, r;
  for (i = 0; i < n; i++) RA[i] = T[i];                 // initial rankings
  for (i = 0; i < n; i++) SA[i] = i;     // initial SA: {0, 1, 2, ..., n-1}
  for (k = 1; k < n; k <<= 1) {       // repeat sorting process log n times
    countingSort(k);  // actually radix sort: sort based on the second item
    countingSort(0);          // then (stable) sort based on the first item
    tempRA[SA[0]] = r = 0;             // re-ranking; start from rank r = 0
    for (i = 1; i < n; i++)                    // compare adjacent suffixes
      tempRA[SA[i]] = // if same pair => same rank r; otherwise, increase r
      (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
    for (i = 0; i < n; i++)                     // update the rank array RA
      RA[i] = tempRA[i];
    if (RA[SA[n-1]] == n-1) break;               // nice optimization trick
} }

int main()
{
	int N;
	scanf("%d", &N);
	while (N--) {
		scanf("%s", T);
		n = strlen(T);
		int m = n;
		strncpy(T + n, T, n);
		n *= 2;
		T[n++] = '{'; // should be greater than 'z'
		T[n + 1] = '\0';
		constructSA();                                              // O(n log n)
#ifdef DEBUG
		printf("\nThe Suffix Array of string T = '%s' is shown below (O(n log n) version):\n", T);
		puts("i     SA[i] Suffix");
		for (int i = 0; i < n; i++)
			printf("%5d %5d %s\n", i, SA[i], T + SA[i]);
#endif
		int i;
		for (i = 0; i < n; i++)
			if (SA[i] < m)
				break;
		printf("%d\n", SA[i] + 1);
	}
	return 0;
}

