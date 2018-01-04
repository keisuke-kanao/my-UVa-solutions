
/*
	UVa 144 - Student Grants

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_144_Student_Grants.cpp
*/

#include <iostream>
#include <iomanip>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

int main()
{
	const int grant = 40;
	while (true) {
		int n, k;
		cin >> n >> k;
		if (!n && !k)
			break;
		queue< pair<int, int> > students;
			// first is the student number, second is the amount of dallars paid
		for (int i = 1; i <= n; i++)
			students.push(make_pair(i, 0));
		queue<int> paid_students;
		int dispensed = 1; // amount of dallars to be dispensed
		int store = dispensed++; // amount of dallars in the store
		if (dispensed > k)
			dispensed = 1;
		while (!students.empty()) {
			pair<int, int> s = students.front();
			students.pop();
			if (students.empty()) { // the last student
				paid_students.push(s.first);
				break;
			}
			int paid = min(store, grant - s.second);
			s.second += paid; store -= paid;
			if (s.second == grant)
				paid_students.push(s.first);
			else
				students.push(s);
			if (!store) {
				store = dispensed++;
				if (dispensed > k)
					dispensed = 1;
			}
		}
		cout << setfill(' ');
		while (!paid_students.empty()) {
			cout << setw(3) << paid_students.front();
			paid_students.pop();
		}
		cout << endl;
	}
	return 0;
}

