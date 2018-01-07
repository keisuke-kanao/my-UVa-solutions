
/*
	UVa 400 - Unix ls

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_400_Unix_ls.cpp

	from ACM South Central Regional Programming Contest 1995 Problem A
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_SouthCen/1995/index.html)

	This is an accepted solution.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
	const int max_length = 60;
	int nr_names;
	while (cin >> nr_names) {
		vector<string> names(nr_names);
		int max_name_length = 0;
		for (int i = 0; i < nr_names; i++) {
			cin >> names[i];
			max_name_length = max(max_name_length, static_cast<int>(names[i].length()));
		}
		sort(names.begin(), names.end());
		int nr_columns = 1;
		for (int l = max_name_length * 2 + 2; l <= max_length; l += max_name_length + 2)
			nr_columns++;
		int nr_rows = (nr_names + nr_columns - 1) / nr_columns;
		cout << "------------------------------------------------------------\n";
		for (int i = 0; i < nr_rows; i++) {
			for (int j = 0; j < nr_columns; j++) {
				int ni = i + nr_rows * j;
				if (ni < nr_names) {
					cout << names[ni];
					int l = max_name_length - names[ni].length();
					if (j < nr_columns - 1)
						l += 2;
					for (int k = 0; k < l; k++)
						cout << ' ';
				}
				else
					break;
			}
			cout << endl;
		}
	}
	return 0;
}

