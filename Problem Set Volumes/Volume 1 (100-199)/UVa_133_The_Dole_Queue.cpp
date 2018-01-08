
/*
	UVa 133 - The Dole Queue

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_133_The_Dole_Queue.cpp
*/

#include <iostream>
#include <iomanip>
#include <list>
using namespace std;

list<int>::iterator move_counterclockwise(list<int>::iterator i, list<int>::iterator ibegin, list<int>::iterator iend, int k)
{
	while (k--) {
		if (i == iend)
			i = ibegin;
		if (++i == iend)
			i = ibegin;
	}
	return i;
}

list<int>::iterator move_clockwise(list<int>::iterator i, list<int>::iterator ibegin, list<int>::iterator iend, int m)
{
	while (m--) {
		if (i == ibegin)
			i = iend;
		--i;
	}
	return i;
}

int main()
{
	while (true) {
		int n, k, m;
		cin >> n >> k >> m;
		if (!n && !k && !m)
			break;
		list<int> applicants(n);
		// assign numbers to applicants
		int j = 1;
		for (list<int>::iterator i = applicants.begin(), e = applicants.end(); i != e; ++i)
			*i = j++;
		--k; --m;
		list<int>::iterator iccw = applicants.begin();
		list<int>::iterator icw = applicants.end();
		--icw;
		while (true) {
			list<int>::iterator ibegin = applicants.begin(), iend = applicants.end();
			iccw = move_counterclockwise(iccw, ibegin, iend, k);
			icw = move_clockwise(icw, ibegin, iend, m);
			cout <<  setfill(' ') << setw(3) << *iccw;
			if (iccw != icw) {
				cout <<  setfill(' ') << setw(3) << *icw;
				if ((iccw = applicants.erase(iccw)) == applicants.end())
					iccw = applicants.begin();
				list<int>::iterator i = icw;
				if (icw == applicants.begin())
					icw = applicants.end();
				--icw;
				if (i == iccw) {
					if (++iccw == applicants.end())
						iccw = applicants.begin();
				}
				applicants.erase(i);
			}
			else {
				if (icw == applicants.begin())
					icw = applicants.end();
				--icw;
				if ((iccw = applicants.erase(iccw)) == applicants.end())
					iccw = applicants.begin();

			}
			if (applicants.empty()) {
				cout << endl;
				break;
			}
			else
				cout << ',';
		}
	}
	return 0;
}

