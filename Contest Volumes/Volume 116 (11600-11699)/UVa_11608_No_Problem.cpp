
/*
	UVa 11608 - No Problem

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_11608_No_Problem.cpp
*/

#include <iostream>
using namespace std;

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int nr_ready;
		cin >> nr_ready;
		if (nr_ready < 0)
			break;
		const int nr_months = 12;
		int nr_created[nr_months], nr_required[nr_months];
		for (int i = 0; i < nr_months; i++)
			cin >> nr_created[i];
		for (int i = 0; i < nr_months; i++)
			cin >> nr_required[i];
		cout << "Case " << case_nr << ":\n";
		for (int i = 0; i < nr_months; i++) {
			if (nr_ready >= nr_required[i]) {
				cout << "No problem! :D\n";
				nr_ready -= nr_required[i];
			}
			else
				cout << "No problem. :(\n";
			nr_ready += nr_created[i];
		}
	}
	return 0;
}

