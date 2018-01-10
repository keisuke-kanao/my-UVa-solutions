
/*
	UVa 11218 - KTV

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11218_KTV.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	for (int c = 1; ; c++) {
		int n;
		cin >> n;
		if (!n)
			break;
		vector<int> combinations(n, 0);
			// combinations[i] is the i-th combination in which bits corresponding to three people are set
		vector<int> scores(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 3; j++) {
				int k;
				cin >> k;
				combinations[i] |= 1 << (k - 1);
			}
			cin >> scores[i];
		}
		int max_score = -1;
		for (int i = 0; i < n; i++) {
			int cm = combinations[i], s = scores[i];
			for (int j = i + 1; j < n; j++) {
				if (cm & combinations[j])
					continue;
				cm |= combinations[j];
				s += scores[j];
				for (int k = j + 1; k < n; k++) {
					if (cm & combinations[k])
						continue;
					max_score = max(max_score, s + scores[k]);
				}
				cm &= ~combinations[j];
				s -= scores[j];
			}
		}
		cout << "Case " << c << ": " << max_score << endl;
	}
	return 0;
}

