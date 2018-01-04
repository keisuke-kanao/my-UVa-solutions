
/*
	UVa 450 - Little Black Book

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_450_Little_Black_Book.cpp
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

const int nr_fields = 7;

struct record {
	int idepartment_;
	int ifields_[nr_fields];
	string info_;
};

bool compare_record(const record* i, const record* j)
{
	return strcmp(i->info_.c_str() + i->ifields_[2], j->info_.c_str() + j->ifields_[2]) < 0;
}

int main()
{
	int nr_departments;
	cin >> nr_departments;
	string s;
	getline(cin, s);
	vector<string> departments(nr_departments);
	vector<record*> records;
	for (int i = 0; i < nr_departments; i++) {
		getline(cin, departments[i]);
		while (true) {
			record* r = new record();
			if (!getline(cin, r->info_) || r->info_.empty()) {
				delete r;
				break;
			}
			r->idepartment_ = i;
			r->ifields_[0] = 0;
			for (int j = 1, p = 0; j < nr_fields; j++) {
				p = r->info_.find(',', p);
				r->info_[p] = '\0';
				r->ifields_[j] = ++p;
			}
			records.push_back(r);
		}
	}
	sort(records.begin(), records.end(), compare_record);
	for (vector<record*>::const_iterator ri = records.begin(), re = records.end(); ri != re; ++ri) {
		record* r = *ri;
		const char* info = r->info_.c_str();
		cout << "----------------------------------------\n";
		cout << info + r->ifields_[0] << ' ' << info + r->ifields_[1] << ' ' << info + r->ifields_[2] << endl;
		cout << info + r->ifields_[3] << endl;
		cout << "Department: " << departments[r->idepartment_] << endl;
		cout << "Home Phone: " << info + r->ifields_[4] << endl;
		cout << "Work Phone: " << info + r->ifields_[5] << endl;
		cout << "Campus Box: " << info + r->ifields_[6] << endl;
	}
	return 0;
}

