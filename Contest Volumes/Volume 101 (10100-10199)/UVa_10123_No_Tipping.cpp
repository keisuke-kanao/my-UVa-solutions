
/*
	UVa 10123 - No Tipping

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10123_No_Tipping.cpp
*/

#include <iostream>
#include <utility>
#include <cstring>
#ifdef DEBUG
#include <cassert>
#endif
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

const int n_max = 20;
bool searched[1 << n_max];

bool remove_packages(int pi, int n, pair<double, double> torque, const pair<double, double> ptorques[],
	int removed, bool searched[], int orders[])
{
	if (searched[removed]) // already searched
		return false;
	searched[removed] = true;
	if (torque.first < 0.0 || torque.second > 0.0)
		return false;
	else if (pi == n)
		return true;
	else {
		for (int i = 0, r = 1; i < n; i++, r <<= 1)
			if (!(removed & r)) {
				removed |= r;
				orders[pi] = i;
				if (remove_packages(pi + 1, n, make_pair(torque.first - ptorques[i].first, torque.second - ptorques[i].second),
					ptorques, removed, searched, orders))
					return true;
				removed &= ~r;
			}
		return false;
	}
}

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	for (int c = 1; ; c++) {
		int length, weight, n;
		cin >> length >> weight >> n;
		if (!length && !weight && !n)
			break;
		pair<double, double> torque(make_pair(1.5 * static_cast<double>(weight), -1.5 * static_cast<double>(weight)));
			// torque.first is the torque around the left fulcrum, torque.second is the torque around the right fulcrum
/*
	Torque is calculated by clockwise direction. the initial values are:
		torque.first = (-length + 1.5) * weight / 2.0 + (length + 1.5) * weight / 2.0 = 3.0 * weight / 2.0 = 1.5 * weight.
		torque.second = (-length - 1.5) * weight / 2.0 + (length - 1.5) * weight / 2.0 = -3.0 * weight / 2.0 = -1.5 * weight.
	torque.first should be equal to or grater than zero, while torque.second should be equal to or less than zeo.
*/
		pair<int, int> packages[n_max];
			// packages[i].first is the weight, packages[i].second is the weight, of i-th package
		pair<double, double> ptorques[n_max];
			// ptorques[i].first is the torque around the left fulcrum, ptorques[i].second is the torque around the right fulcrum,
			// of the i-th package
		for (int i = 0; i < n; i++) {
			cin >> packages[i].first >> packages[i].second;
			ptorques[i].first = (static_cast<double>(packages[i].first) + 1.5) * static_cast<double>(packages[i].second);
			ptorques[i].second = (static_cast<double>(packages[i].first) - 1.5) * static_cast<double>(packages[i].second);
			torque.first += ptorques[i].first;
			torque.second += ptorques[i].second;
		}
		memset(searched, 0, sizeof(searched));
		int orders[n_max];
		bool successful = remove_packages(0, n, torque, ptorques, 0, searched, orders);
		cout << "Case " << c << ":\n";
#ifdef DEBUG
		cout << '\t' << torque.first << ' ' << torque.second << endl;
#endif
		if (successful) {
			for (int i = 0; i < n; i++) {
				pair<int, int>& p = packages[orders[i]];
				cout << p.first << ' ' << p.second << endl;
#ifdef DEBUG
			torque.first -= ptorques[orders[i]].first; torque.second -= ptorques[orders[i]].second;
			assert(torque.first >= 0.0 && torque.second <= 0.0);
			cout << '\t' << torque.first << ' ' << torque.second << endl;
#endif
			}
		}
		else
			cout << "Impossible\n";
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

