
/*
	UVa 661 - Blowing Fuses

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_661_Blowing_Fuses.cpp

	from ACM Western and Southwestern European Regionals 1998
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_SWERC/1998/index.html)
*/

#include <iostream>
using namespace std;

int main()
{
	for (int s = 1; ; s++) {
		int n, m, c;
		cin >> n >> m >> c;
		if (!n && !m && !c)
			break;
		const int nr_devices_max = 20;
		int consumptions[nr_devices_max + 1];
		bool status[nr_devices_max + 1];
		for (int i = 1; i <= n; i++) {
			cin >> consumptions[i];
			status[i] = false;
		}
		int p = 0, max_p = 0;
		for (int i = 0; i < m; i++) {
			int d;
			cin >> d;
			if (status[d])
				p -= consumptions[d];
			else {
				p += consumptions[d];
				if (p > max_p)
					max_p = p;
			}
			status[d] = !status[d];
		}
		cout << "Sequence " << s << endl;
		if (max_p > c)
			cout << "Fuse was blown.\n\n";
		else {
			cout << "Fuse was not blown.\n";
			cout << "Maximal power consumption was " << max_p << " amperes.\n\n";
		}
	}
	return 0;
}

