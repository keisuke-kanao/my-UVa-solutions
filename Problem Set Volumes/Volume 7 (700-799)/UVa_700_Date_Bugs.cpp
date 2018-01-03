
/*
	UVa 700 - Date Bugs

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_700_Date_Bugs.cpp

	from ACM Mid-Central European Regional Contest 1999
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_MCRC/1999/index.html)
*/

#include <iostream>
#include <vector>
using namespace std;

struct computer {
	int y_, a_, b_;
};

bool date_bugs(int n, int ci, const vector<computer>& computers, int& year)
{
	if (ci == n)
		return true;
	const computer& cm = computers[ci];
	if (!ci) {
		if (date_bugs(n, 1, computers, year = cm.y_))
			return true;
		else {
			for (int y = cm.y_ - cm.a_ + cm.b_; y < 10000; y += cm.b_ - cm.a_)
				if (date_bugs(n, 1, computers, year = y))
					return y;
		}
	}
	else {
		if (year < cm.a_)
			return false;
		else if (year < cm.b_) {
			if (year == cm.y_)
				return date_bugs(n, ci + 1, computers, year);
		}
		else {
			if ((year - cm.b_) % (cm.b_ - cm.a_) + cm.a_ == cm.y_)
				return date_bugs(n, ci + 1, computers, year);
		}
	}
	return false;
}

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int n;
		cin >> n;
		if (!n)
			break;
		vector<computer> computers(n);
		for (int i = 0; i < n; i++)
			cin >> computers[i].y_ >> computers[i].a_ >> computers[i].b_;
		int year;
		bool result = date_bugs(n, 0, computers, year);
		cout << "Case #" << case_nr << ":\n";
		if (result)
			cout << "The actual year is " << year << ".\n";
		else
			cout << "Unknown bugs detected.\n";
		cout << endl;
	}
	return 0;
}

