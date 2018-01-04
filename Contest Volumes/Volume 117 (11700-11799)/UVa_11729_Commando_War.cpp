
/*
	UVa 11729 - Commando War

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_11729_Commando_War.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int n_max = 1000;

struct soldier {
	int b_, j_;
	bool operator<(const soldier& s) const {return j_ > s.j_;}
} soldiers[n_max];

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int n;
		cin >> n;
		if (!n)
			break;
		for (int i = 0; i < n; i++)
			cin >> soldiers[i].b_ >> soldiers[i].j_;
		sort(soldiers, soldiers + n); // sort in descending order of soldier's job time
		int t = 0, min_t = 0;
		for (int i = 0; i < n; i++) {
			t += soldiers[i].b_;
			min_t = max(min_t, t + soldiers[i].j_);
		}
		cout << "Case " << case_nr << ": " << min_t << endl;
	}
	return 0;
}

