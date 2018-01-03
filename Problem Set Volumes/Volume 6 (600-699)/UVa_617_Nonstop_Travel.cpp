
/*
	UVa 617 - Nonstop Travel

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_617_Nonstop_Travel.cpp

	from ACM North Central Regionals 1997, Problem 4
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1997/index.html)
*/

#include <iostream>
#include <cmath>
using namespace std;

const int mph_min = 30, mph_max = 60;
const int nr_speeds = mph_max - mph_min + 1;
struct speed {
	bool valid_;
	int mph_; // mile per hour
	double mps_; // mile per second
} speeds[nr_speeds];

const int n_max = 6;

struct traffic_signal {
	double L_, G_, Y_, R_;
} traffic_signals[n_max];

int main()
{
	for (int i = 0; i < nr_speeds; i++) {
		speeds[i].mph_ = mph_min + i;
		speeds[i].mps_ = static_cast<double>(speeds[i].mph_) / 3600.0;
	}
	for (int cn = 1; ; cn++) {
		int n;
		cin >> n;
		if (n == -1)
			break;
		for (int i = 0; i < n; i++)
			cin >> traffic_signals[i].L_ >> traffic_signals[i].G_ >> traffic_signals[i].Y_ >> traffic_signals[i].R_;
		for (int i = 0; i < nr_speeds; i++) {
			speeds[i].valid_ = false;
			int j;
			for (j = 0; j < n; j++) {
				const traffic_signal& ts = traffic_signals[j];
				double s = fmod(ts.L_ / speeds[i].mps_, ts.G_ + ts.Y_ + ts.R_);
				if (s > ts.G_ + ts.Y_ && s < ts.G_ + ts.Y_ + ts.R_)
					break;
			}
			if (j == n)
				speeds[i].valid_ = true;
		}
		cout << "Case " << cn << ':';
		bool printed = false;
		for (int i = 0, j = 0; i < nr_speeds;) {
			for ( ; j < nr_speeds && speeds[j].valid_; j++)
				;
			if (j > i) {
				if (printed)
					cout << ',';
				else
					printed = true;
				cout << ' ' << speeds[i].mph_;
				if (j - i > 1)
					cout << '-' << speeds[j - 1].mph_;
			}
			i = ++j;
		}
		if (printed)
			cout << endl;
		else
			cout << " No acceptable speeds.\n";
	}
	return 0;
}

