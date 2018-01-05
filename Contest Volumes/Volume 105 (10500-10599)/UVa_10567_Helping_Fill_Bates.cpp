
/*
	UVa 10567 - Helping Fill Bates

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10567_Helping_Fill_Bates.cpp

	This is an accepted solution.
*/

#include<algorithm>
#include<vector>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_chars = 128, S_chars_max = 1000000, SS_chars_max = 101;
int S_chars, SS_chars;
char S[S_chars_max + 1], SS[SS_chars_max + 1];

vector<int> indices[nr_chars]; // indices[i] is the array of indices in S of charactor i, in ascending order

int main()
{
	scanf("%s", S);
	S_chars = strlen(S);
	for (int i = 0; i < S_chars; i++)
		indices[S[i]].push_back(i);
	int Q;
	scanf("%d", &Q);
	while (Q--) {
		scanf("%s", SS);
		SS_chars = strlen(SS);
		int si = -1, ei;
		for (int i = -1, j = 0; j < SS_chars; j++) {
			const vector<int>& ids = indices[SS[j]];
			vector<int>::const_iterator ii = upper_bound(ids.begin(), ids.end(), i);
			if (ii != ids.end()) {
				if (si == -1)
					si = *ii;
				if (j == SS_chars - 1) {
					ei = *ii;
					break;
				}
				i = *ii;
			}
			else {
				si = -1;
				break;
			}
		}
		if (si >= 0)
			printf("Matched %d %d\n", si, ei);
		else
			puts("Not matched");
	}
	return 0;
}

