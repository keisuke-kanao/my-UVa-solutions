
/*
	UVa 11790 - Murcia's Skyline

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11790_Murcias_Skyline.cpp
*/

#include <iostream>
#include <vector>
using namespace std;

struct building {
	int width_, height_;
};

int lis(const vector<building>& buildings)
{
	size_t n = buildings.size();
	vector<int> l(n);
	int length = buildings[0].width_;
	l[0] = length;
	for (size_t i = 1; i < n; i++) {
		l[i] = buildings[i].width_;
		for (size_t j = 0; j < i; j++)
			if (buildings[j].height_ < buildings[i].height_) {
				if (l[i] < l[j] + buildings[i].width_)
					l[i] = l[j] + buildings[i].width_;
			}
		if (length < l[i])
			length = l[i];
	}
	return length;
}

int lds(const vector<building>& buildings)
{
	size_t n = buildings.size();
	vector<int> l(n);
	int length = buildings[0].width_;
	l[0] = length;
	for (size_t i = 1; i < n; i++) {
		l[i] = buildings[i].width_;
		for (size_t j = 0; j < i; j++)
			if (buildings[j].height_ > buildings[i].height_) {
				if (l[i] < l[j] + buildings[i].width_)
					l[i] = l[j] + buildings[i].width_;
			}
		if (length < l[i])
			length = l[i];
	}
	return length;
}

int main()
{
	int tc;
	cin >> tc;
	for (int tcn = 1; tcn <= tc; tcn++) {
		int n;
		cin >> n;
		vector<building> buildings(n);
		for (int i = 0; i < n; i++)
			cin >> buildings[i].height_;
		for (int i = 0; i < n; i++)
			cin >> buildings[i].width_;
		int inc = lis(buildings), dec = lds(buildings);
		cout << "Case " << tcn << ". ";
		if (inc >= dec)
			cout << "Increasing (" << inc << "). Decreasing (" << dec << ").\n";
		else
			cout << "Decreasing (" << dec << "). Increasing (" << inc << ").\n";
	}
	return 0;
}

