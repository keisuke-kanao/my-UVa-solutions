
/*
	UVa 637 - Booklet Printing

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_637_Booklet_Printing.cpp
*/

#include <iostream>
using namespace std;

const int nr_pages_max = 100;

struct sheet {
	int front_left_, front_right_, back_left_, back_right_;
} sheets[nr_pages_max / 4];

int main()
{
	while (true) {
		int nr_pages;
		cin >> nr_pages;
		if (!nr_pages)
			break;
		int nr_sheets = (nr_pages + 3) / 4;
		int i, j;
		for (i = 0, j = 1; i < nr_sheets; i++) {
			if (j <= nr_pages)
				sheets[i].front_right_ = j++;
			else
				sheets[i].front_right_ = -1;
			if (j <= nr_pages)
				sheets[i].back_left_ = j++;
			else
				sheets[i].back_left_ = -1;
		}
		for (int i = nr_sheets - 1; i >= 0; i--) {
			if (j <= nr_pages)
				sheets[i].back_right_ = j++;
			else
				sheets[i].back_right_ = -1;
			if (j <= nr_pages)
				sheets[i].front_left_ = j++;
			else
				sheets[i].front_left_ = -1;
		}
		cout << "Printing order for " << nr_pages << " pages:\n";
		for (int i = 0; i < nr_sheets; i++) {
			if (sheets[i].front_right_ != -1 || sheets[i].front_left_ != -1) {
				cout << "Sheet " << i + 1 << ", front: ";
				if (sheets[i].front_left_ != -1)
					cout << sheets[i].front_left_ << ", ";
				else
					cout << "Blank, ";
				if (sheets[i].front_right_ != -1)
					cout << sheets[i].front_right_ << endl;
				else
					cout << "Blank\n";
			}
			if (sheets[i].back_right_ != -1 || sheets[i].back_left_ != -1) {
				cout << "Sheet " << i + 1 << ", back : ";
				if (sheets[i].back_left_ != -1)
					cout << sheets[i].back_left_ << ", ";
				else
					cout << "Blank, ";
				if (sheets[i].back_right_ != -1)
					cout << sheets[i].back_right_ << endl;
				else
					cout << "Blank\n";
			}
		}
	}
	return 0;
}

