
/*
	UVa 11107 - Life Forms

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11107_Life_Forms.cpp
*/

/*
Longest Common Substring between > 1/2 of the strings
*/

/*
How can I find the longest common substring of three or more strings using a suffix array?

Concatenate the three strings together and separate them with a separator that's guaranteed to not show in any of the strings. 
Now construct the suffix array and the lcp array for that new string. 

Now let's define some variables i, j, total, array of flags of size 3 all initialized with zeros. 

Now lets start examining the sorted suffices one by one in order, 
  if total value is less than 3 and we see a suffix that belongs to one of the three strings 
    increment its flag by 1 and increment the variable total by 1 (if the previous flag is zero) as well and increment j, 

when the variable total value hits three we have seen at least three suffices that belong to the three different strings, 
now you have a window between i and j, 
the minimum value of the lcp array in this window is the longest common substring that those suffices share in common, 
in this case you increment the variable i not j and decrement the flag of the string that i was pointing at by one, 
if the flag drops to zero decrement total by one as well. 

Take the maximum value over all events of the second type (when total reached 3), 
that's your answer. This solution can be generalized to X strings not only three.
*/

#include <algorithm>
#include <map>
#include <cstdio>
#include <cstring>
using namespace std;

typedef pair<int, int> ii;

#define MAX_N 101010                         // second approach: O(n log n)
char T[MAX_N];                   // the input string, up to 100K characters
int n;                                        // the length of input string
int RA[MAX_N], tempRA[MAX_N];        // rank array and temporary rank array
int SA[MAX_N], tempSA[MAX_N];    // suffix array and temporary suffix array
int c[MAX_N];                                    // for counting/radix sort

char P[MAX_N];                  // the pattern string (for string matching)
int m;                                      // the length of pattern string

int Phi[MAX_N];                      // for computing longest common prefix
int PLCP[MAX_N];
int LCP[MAX_N];  // LCP[i] stores the LCP between previous suffix T+SA[i-1]
                                              // and current suffix T+SA[i]

bool cmp(int a, int b) { return strcmp(T + a, T + b) < 0; }      // compare

void constructSA_slow() {               // cannot go beyond 1000 characters
  for (int i = 0; i < n; i++) SA[i] = i; // initial SA: {0, 1, 2, ..., n-1}
  sort(SA, SA + n, cmp); // sort: O(n log n) * compare: O(n) = O(n^2 log n)
}

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

void computeLCP_slow() {
  LCP[0] = 0;                                              // default value
  for (int i = 1; i < n; i++) {                // compute LCP by definition
    int L = 0;                                       // always reset L to 0
    while (T[SA[i] + L] == T[SA[i-1] + L]) L++;      // same L-th char, L++
    LCP[i] = L;
} }

void computeLCP() {
  int i, L;
  Phi[SA[0]] = -1;                                         // default value
  for (i = 1; i < n; i++)                            // compute Phi in O(n)
    Phi[SA[i]] = SA[i-1];    // remember which suffix is behind this suffix
  for (i = L = 0; i < n; i++) {             // compute Permuted LCP in O(n)
    if (Phi[i] == -1) { PLCP[i] = 0; continue; }            // special case
    while (T[i + L] != '.' && T[i + L] == T[Phi[i] + L]) L++;       // L increased max n times
    PLCP[i] = L;
    L = max(L-1, 0);                             // L decreased max n times
  }
  for (i = 0; i < n; i++)                            // compute LCP in O(n)
    LCP[i] = PLCP[SA[i]];   // put the permuted LCP to the correct position
}

ii stringMatching() {                      // string matching in O(m log n)
  int lo = 0, hi = n-1, mid = lo;              // valid matching = [0..n-1]
  while (lo < hi) {                                     // find lower bound
    mid = (lo + hi) / 2;                              // this is round down
    int res = strncmp(T + SA[mid], P, m);  // try to find P in suffix 'mid'
    if (res >= 0) hi = mid;        // prune upper half (notice the >= sign)
    else          lo = mid + 1;           // prune lower half including mid
  }                                      // observe `=' in "res >= 0" above
  if (strncmp(T + SA[lo], P, m) != 0) return ii(-1, -1);    // if not found
  ii ans; ans.first = lo;
  lo = 0; hi = n - 1; mid = lo;
  while (lo < hi) {            // if lower bound is found, find upper bound
    mid = (lo + hi) / 2;
    int res = strncmp(T + SA[mid], P, m);
    if (res > 0) hi = mid;                              // prune upper half
    else         lo = mid + 1;            // prune lower half including mid
  }                           // (notice the selected branch when res == 0)
  if (strncmp(T + SA[hi], P, m) != 0) hi--;                 // special case
  ans.second = hi;
  return ans;
} // return lower/upperbound as first/second item of the pair, respectively

ii LRS() {                 // returns a pair (the LRS length and its index)
  int i, idx = 0, maxLCP = -1;
  for (i = 1; i < n; i++)                         // O(n), start from i = 1
    if (LCP[i] > maxLCP)
      maxLCP = LCP[i], idx = i;
  return ii(maxLCP, idx);
}

const int nr_life_forms_max = 100, nr_chars_max = 1000;
int nr_life_forms, lengths[nr_life_forms_max], counters[nr_life_forms_max];
int Owners[MAX_N];

int owner(int idx)
{
	for (int i = 0, length = lengths[i] + 1; ; i++, length += lengths[i] + 1) {
		if (idx < length - 1)
			return i;
		else if (idx == length - 1)
			return -1;
	}
}

/*
int owner(int idx) { return (idx < n-m-1) ? 1 : 2; }
*/

ii LCS() {                 // returns a pair (the LCS length and its index)
  int i, idx = 0, maxLCP = -1;
  for (i = 1; i < n; i++)                         // O(n), start from i = 1
    if (owner(SA[i]) != owner(SA[i-1]) && LCP[i] > maxLCP)
      maxLCP = LCP[i], idx = i;
  return ii(maxLCP, idx);
}

int main()
{
	bool printed = false;
	while (true) {
		scanf("%d", &nr_life_forms);
		if (!nr_life_forms)
			break;
		if (printed)
			putchar('\n');
		else
			printed = true;
		if (nr_life_forms == 1) {
			scanf("%s", T);
			puts(T);
			continue;
		}
		n = 0;
		for (int i = 0; i < nr_life_forms; i++) {
			scanf("%s", T + n);
			lengths[i] = strlen(T + n);
			n += lengths[i];
			T[n++] = '.';
		}
		T[n] = '\0';
		constructSA(); // O(n log n)
		computeLCP(); // O(n)
		for (int i = 0; i < n; i++)
			Owners[i] = owner(SA[i]);
#ifdef DEBUG
		printf("\nThe LCP information of '%s':\n", T);
		printf("i     SA[i] LCP[i] Owner Suffix\n");
		for (int k = 0; k < n; k++)
			printf("%4d  %4d  %4d   %4d  %s\n", k, SA[k], LCP[k], Owners[k], T + SA[k]);
#endif
		int lcs_length = 0;
		memset(counters, 0, sizeof(counters));
		for (int i = nr_life_forms, j = nr_life_forms, total = 0; j < n; ) {
			if (total <= nr_life_forms / 2) {
				if (!counters[Owners[j++]]++)
					++total;
			}
			if (total > nr_life_forms / 2) {
				lcs_length = max(lcs_length, LCP[min_element(LCP + i + 1, LCP + j) - LCP]);
#ifdef DEBUG
				printf("LCS [%d, %d): %d\n", i, j, lcs_length);
#endif
				if (!--counters[Owners[i++]])
					--total;
			}
		}
		if (!lcs_length) {
			puts("?");
			continue;
		}
		int psa = -1;
		memset(counters, 0, sizeof(counters));
		for (int i = nr_life_forms, j = nr_life_forms, total = 0; j < n; ) {
			if (total <= nr_life_forms / 2) {
				if (!counters[Owners[j++]]++)
					++total;
			}
			if (total > nr_life_forms / 2) {
				int k = min_element(LCP + i + 1, LCP + j) - LCP;
				if (LCP[k] == lcs_length && (psa == -1 || strncmp(T + psa, T + SA[k], lcs_length))) {
					psa = SA[k];
					char c = T[psa + lcs_length];
					T[psa + lcs_length] = '\0';
#ifdef DEBUG
					printf("LCS [%d, %d): %s\n", i, j, T + psa);
#else
					puts(T + psa);
#endif
					T[psa + lcs_length] = c;
				}
				if (!--counters[Owners[i++]])
					--total;
			}
		}
	}
	return 0;
}

