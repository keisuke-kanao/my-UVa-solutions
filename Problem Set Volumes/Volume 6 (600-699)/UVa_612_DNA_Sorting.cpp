
/*
	UVa 612 - DNA Sorting

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_612_DNA_Sorting.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int n_max = 50, m_max = 100;

struct dna_string {
	char s_[n_max + 1];
	int sortedness_;

	bool operator<(const dna_string& s) const {return sortedness_ < s.sortedness_;}
};

dna_string dna_strings[m_max];

int main()
{
	int M;
	cin >> M;
	while (M--) {
		int n, m;
		cin >> n >> m;
		for (int i = 0; i < m; i++) {
			dna_string& ds = dna_strings[i];
			cin >> ds.s_;
			ds.sortedness_ = 0;
			for (int j = 0; j < n - 1; j++)
				for (int k = j + 1; k < n; k++)
					if (ds.s_[j] > ds.s_[k])
						ds.sortedness_++;
		}
		stable_sort(dna_strings, dna_strings + m);
		for (int i = 0; i < m; i++)
			cout << dna_strings[i].s_ << endl;
		if (M)
			cout << endl;
	}
	return 0;
}

