
/*
	UVa 11961 - DNA

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11961_DNA.cpp
*/

#include <iostream>
#include <set>
#include <cstring>
using namespace std;

const int N_max = 15, nr_nucleotides = 4;
const char nucleotides[nr_nucleotides] = {'A', 'C', 'G', 'T'};

struct Dna {
	char s_[N_max + 1];
	bool operator<(const Dna& d) const {return strcmp(s_, d.s_) < 0;}
};

int main()
{
	int T;
	cin >> T;
	while (T--) {
		int N, K;
		cin >> N >> K;
		Dna d;
		cin >> d.s_;
		set<Dna> current;
		current.insert(d);
		while (K--) {
			set<Dna> next;
			for (set<Dna>::const_iterator ci = current.begin(), ce = current.end(); ci != ce; ++ci) {
				Dna d = *ci;
				for (int i = 0; i < N; i++) {
					char nucleotide = d.s_[i];
					for (int j = 0; j < nr_nucleotides; j++)
						if (nucleotide != nucleotides[j]) {
							d.s_[i] = nucleotides[j];
							if (current.find(d) == ce)
								next.insert(d);
						}
					d.s_[i] = nucleotide;
				}
			}
			current.insert(next.begin(), next.end());
		}
		cout << current.size() << endl;
		for (set<Dna>::const_iterator ci = current.begin(), ce = current.end(); ci != ce; ++ci)
			cout << ci->s_ << endl;
	}
	return 0;
}

