
/*
	UVa 10364 - Square

	To build using Visual Studio 2010:
		cl -EHsc -O2 UVa_10364_Square.cpp

	from Waterloo ACM Programming Contest September 21, 2002 Problem C
		(http://acm.student.cs.uwaterloo.ca/~acm00/020921/data/)
*/

#include <iostream>
#include <algorithm>
using namespace std;

const int ns_max = 20;
struct stick {
	bool used_;
	int length_;
	bool operator<(const stick& s) const {return length_ > s.length_;}
} sticks[ns_max];

bool form_square(int n /* number of sticks */, int i /* index to sticks[] */, int nrs /* number of remaining sides */,
	int sl /* side length */, int rsl /* remaining side length */)
{
	if (!rsl) {
		if (!--nrs)
			return true;
		else
			return form_square(n, 0, nrs, sl, sl);
	}
	else {
		for (int j = i; j < n; j++)
			if (sticks[j].length_ <= rsl && !sticks[j].used_) {
				sticks[j].used_ = true;
				if (form_square(n, j + 1, nrs, sl, rsl - sticks[j].length_))
					return true;
				sticks[j].used_ = false;
			}
		return false;
	}
}

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		int s = 0;
		for (int i = 0; i < n; i++) {
			sticks[i].used_ = false;
			cin >> sticks[i].length_;
			s += sticks[i].length_;
		}
		int sl = s / 4;
		bool yes = true;
		if (sl * 4 != s)
			yes = false;
		else {
			for (int i = 0; i < n; i++)
				if (sticks[i].length_ > sl) {
					yes = false; break;
				}
			if (yes) {
				sort(sticks, sticks + n); // sort in descending order of lengths
				yes = form_square(n, 0, 4, sl, sl);
			}
		}
		cout << ((yes) ? "yes\n" : "no\n");
	}
	return 0;
}

