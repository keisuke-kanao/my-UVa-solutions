
/*
	UVa 10930 - A-Sequence

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10930_A-Sequence.cpp
*/

#include <iostream>
#include <cstring>
using namespace std;

const int n_max = 1000;
bool numbers[2][n_max + 1];

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int d;
		if (!(cin >> d))
			break;
		cout << "Case #" << case_nr << ':';
		bool a_sequence = true;
		int n, pn, s_min, s_max;
		memset(numbers, 0, sizeof(numbers));
		for (int i = 0; i < d; i++) {
			cin >> n;
			cout << ' ' << n;
			bool *pnrs = numbers[(i + 1) % 2], *cnrs = numbers[i % 2];
			if (i) {
				if (n <= pn)
					a_sequence = false;
				if (a_sequence) {
					if (pnrs[n])
						a_sequence = false;
					else {
						int s = -1;
						for (int j = s_min; j <= s_max; j++)
							if (pnrs[j]) {
								cnrs[j] = true;
								 if (n + j <= n_max)
									cnrs[s = n + j] = true;
							}
						if (s > s_max)
							s_max = s;
						cnrs[n] = true;
					}
					memset(pnrs, 0, sizeof(*pnrs));
				}
			}
			else {
				s_min = s_max = n;
				cnrs[n] = true;
			}
			pn = n;
		}
		cout << ((a_sequence) ? "\nThis is an A-sequence.\n" : "\nThis is not an A-sequence.\n");
	}
	return 0;
}

