
/*
	UVa 11799 - Horror Dash

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11799_Horror_Dash.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	int t;
	cin >> t;
	for (int c = 1; c <= t; c++) {
		int n;
		cin >> n;
		int min_speed = 0;
		for (int i = 0; i < n; i++) {
			int s;
			cin >> s;
			if (s > min_speed)
				min_speed = s;
		}
		cout << "Case " << c << ": " << min_speed << endl;
	}
	return 0;
}

