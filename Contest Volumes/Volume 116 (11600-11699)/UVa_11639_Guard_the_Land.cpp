
/*
	UVa 11639 - Guard the Land

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11639_Guard_the_Land.cpp
*/

#include <iostream>
#include <algorithm>
using namespace std;

struct rectangle {
	int x1_, y1_, x2_, y2_;

	int region() {return (x2_ - x1_) * (y2_ - y1_);}
};

int main()
{
	int N;
	cin >> N;
	for (int n = 1; n <= N; n++) {
		rectangle r1, r2;
		cin >> r1.x1_ >> r1.y1_ >> r1.x2_ >> r1.y2_;
		cin >> r2.x1_ >> r2.y1_ >> r2.x2_ >> r2.y2_;

		int rr1 = r1.region(), rr2 = r2.region(), rsr = 0;
		if (r1.x2_ < r2.x1_ || r1.y2_ < r2.y1_ || r2.x2_ < r1.x1_ || r2.y2_ < r1.y1_)
			;
		else {
			int xs[4], ys[4];
			xs[0] = r1.x1_; xs[1] = r1.x2_; ys[0] = r1.y1_; ys[1] = r1.y2_;
			xs[2] = r2.x1_; xs[3] = r2.x2_; ys[2] = r2.y1_; ys[3] = r2.y2_;
			sort(xs, xs + 4);
			sort(ys, ys + 4);
			rectangle sr;
			sr.x1_ = xs[1]; sr.y1_ = ys[1]; sr.x2_ = xs[2]; sr.y2_ = ys[2];
			rsr = sr.region();
		}
		int rwr = rr1 + rr2 - 2 * rsr;
		cout << "Night " << n << ": " << rsr << ' ' << rwr << ' ' << 100 * 100 - (rsr + rwr) << endl;
	}
	return 0;
}

