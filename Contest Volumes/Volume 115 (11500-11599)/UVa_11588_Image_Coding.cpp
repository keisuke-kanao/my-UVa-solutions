
/*
	UVa 11588 - Image Coding

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11588_Image_Coding.cpp
*/

#include <iostream>
#include <algorithm>
#include <functional>
#include <cstring>
using namespace std;

int main()
{
	const int nr_letters = 'Z' - 'A' + 1;
	int regions[nr_letters];
	int x;
	cin >> x;
	for (int case_nr = 1; case_nr <= x; case_nr++) {
		int r, c, m, n;
		cin >> r >> c >> m >> n;
		memset(regions, 0, sizeof(regions));
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++) {
				char rg;
				cin >> rg;
				regions[rg - 'A']++;
			}
		sort(regions, regions + nr_letters, greater<int>());
		int i = 0, nr = regions[i++];
		for ( ; i < nr_letters && regions[i] == regions[0]; i++)
			nr += regions[i];
		int nr_bytes = m * nr;
		for (nr = regions[i++]; i < nr_letters && regions[i]; i++)
			nr += regions[i];
		nr_bytes += n * nr;
		cout << "Case " << case_nr << ": " << nr_bytes << endl;
	}
	return 0;
}

