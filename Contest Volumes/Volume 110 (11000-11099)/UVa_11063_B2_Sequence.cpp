
/*
	UVa 11063 - B2-Sequence

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11063_B2_Sequence.cpp
*/

#include <iostream>
#include <set>
using namespace std;

int main()
{
	const int n_max = 100;
	int sequence[n_max];
	int n;
	for (int case_nr = 1; cin >> n; case_nr++) {
		bool b2_sequence = true;
		for (int i = 0; i < n; i++) {
			cin >> sequence[i];
			if (i && sequence[i] <= sequence[i - 1] || !i && sequence[i] < 1)
				b2_sequence = false;
		}
		if (b2_sequence) {
			set<int> sums;
			for (int i = 0; b2_sequence && i < n; i++)
				for (int j = i; b2_sequence && j < n; j++) {
					pair<set<int>::iterator, bool> result = sums.insert(sequence[i] + sequence[j]);
					if (!result.second)
						b2_sequence = false;
				}
		}
		cout << "Case #" << case_nr;
		if (b2_sequence)
			cout << ": It is a B2-Sequence.\n\n";
 		else
			cout << ": It is not a B2-Sequence.\n\n";
	}
	return 0;
}

