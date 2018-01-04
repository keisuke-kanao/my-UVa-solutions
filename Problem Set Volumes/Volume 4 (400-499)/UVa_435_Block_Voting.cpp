
/*
	UVa 435 - Block Voting

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_435_Block_Voting.cpp
*/

#include <iostream>
using namespace std;

const int n_max = 20; // max. number of parties
int votes[n_max];
int partial_votes[n_max];
	// partial_votes[i] is the sum of votes from i to n, where n is the number of perties

void block_voting(int n /* number of parties */, int m /* majority of votes */,
	int i /* index to votes[] */, int ei /* excluded index to votes[] */,
	int v /* sum of votes so far */, int& pi /* power index */)
{
	if (i == n)
		return;
	else if (i == ei)
		block_voting(n, m, i + 1, ei, v, pi);
	else {
		int s = v + partial_votes[i];
		if (i < ei && s < m || i > ei && s + votes[ei] < m) // pruning
			return;
		else {
			block_voting(n, m, i + 1, ei, v, pi); // votes[i] is not included to a coaliton
			if (votes[i] < m) {
				s = v + votes[i];
				if (s < m && s + votes[ei] >= m)
					pi++;
				block_voting(n, m, i + 1, ei, s, pi); // votes[i] is included to a coaliton
			}
		}
	}
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int p;
		cin >> p;
		int s = 0;
		for (int i = 0; i < p; i++) {
			cin >> votes[i];
			s += votes[i];
		}
		int majority = s / 2 + 1;
		s = 0;
		for (int i = p - 1; i >= 0; i--) {
			s += votes[i];
			partial_votes[i] = s;
		}
		for (int i = 0; i < p; i++) {
			int power_index = (votes[i] >= majority) ? 1 : 0;
			block_voting(p, majority, 0, i, 0, power_index);
			cout << "party " << i + 1 << " has power index " << power_index << endl;
		}
		cout << endl;
	}
	return 0;
}

