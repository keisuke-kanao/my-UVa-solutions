
/*
	UVa 11034 - Ferry Loading IV

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11034_Ferry_Loading_IV.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--) {
		int l, m;
		cin >> l >> m;
		l *= 100;
		vector< vector<int> > cars(2);
		while (m--) {
			int cl;
			string s;
			cin >> cl >> s;
			if (s[0] == 'l')
				cars[0].push_back(cl);
			else
				cars[1].push_back(cl);
		}
		vector< pair<size_t, size_t> > car_sizes(2);
		car_sizes[0].first = car_sizes[1].first = 0;
		car_sizes[0].second = cars[0].size(); car_sizes[1].second = cars[1].size();
		int n = 0;
		for ( ; ; n++) {
			int cn = n % 2, nn = (n + 1) % 2;
			if (car_sizes[cn].first < car_sizes[cn].second) {
				for (int cl = cars[cn][car_sizes[cn].first++];
					car_sizes[cn].first < car_sizes[cn].second && (cl += cars[cn][car_sizes[cn].first]) <= l;
					car_sizes[cn].first++)
					;
			}
			else if (car_sizes[nn].first < car_sizes[nn].second)
				;
			else
				break;
		}
		cout << n << endl;
	}
	return 0;
}

