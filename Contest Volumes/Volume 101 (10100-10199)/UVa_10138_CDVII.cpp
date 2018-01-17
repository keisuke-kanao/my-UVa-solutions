/*
	4.6.6 CDVII
	PC/UVa IDs: 110406/10138, Popularity: C, Success rate: low Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10138_CDVII.cpp
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct record {
	int enter_exit; // -1 for unknown, 0 for enter, 1 for exit
	int minutes; // minutes from the start of the first day (01:00:00)
	int location; // km from one end of the highway

	record() : enter_exit(-1), minutes(-1), location(-1) {}
	record(int _enter_exit, int _minutes, int _location)
		: enter_exit(_enter_exit), minutes(_minutes), location(_location) {}
	bool operator <(const record& r) const {return minutes < r.minutes;}
};


const int number_of_hours = 24;

inline int get_minutes(int day, int hour, int minute)
{
	return day * 24 * 60 + hour * 60 + minute;
}

int calculate_bill(const vector<int>& fares, vector<record>& records)
{
	int bill = 0; // in cents
	sort(records.begin(), records.end()); // sort the records in ascending order of minutes
	// iterate the records and calculate the fares for the pair of records (i.e., one for "enter" and the other for "exit")
	for (vector<record>::iterator i = records.begin(); i != records.end(); i++)
		if (i->enter_exit == 0) { // "enter"
			vector<record>::iterator j = i;
			j++;
			if (j != records.end() && j->enter_exit == 1) { // "exit"
				int fare = fares[(i->minutes / 60) % number_of_hours] * (j->location - i->location);
				if (fare < 0)
					fare = -fare;
				bill += fare + 100; // one daller per trip
			}
		}
	if (bill)
		bill += 200; // two dollar account charge
	return bill;
}

int main(int /* argc */, char** /* argv */)
{
	string line;
	istringstream iss;

	// read the number of test cases
	if (!getline(cin, line))
		return 0;
	iss.str(line);
	int cases;
	iss >> cases;
	iss.clear();
	if (cases && !getline(cin, line)) // skip a blank line
		return 0;
	while (cases--) {
		// read a fare structure
		vector<int> fares(number_of_hours);
		getline(cin, line);
		iss.str(line);
		for (int i = 0; i < number_of_hours; i++)
			iss >> fares[i];
		iss.clear();
		map<string, vector<record> > license_records; // key is a license number, value is its records
		while (getline(cin, line) && !line.empty()) { // read records
			iss.str(line);
			string license_number, enter_exit;
			char c;
			int month, day, hour, minute, location;
			iss >> license_number >> month >> c >> day >> c >> hour >> c >> minute >> enter_exit >> location;
			iss.clear();
			record r(((enter_exit == "enter") ? 0 : 1), get_minutes(day, hour, minute), location);
			map<string, vector<record> >::iterator i = license_records.find(license_number);
			if (i == license_records.end()) { // a new license found
				pair<map<string, vector<record> >::iterator, bool> result =
					license_records.insert(make_pair(license_number, vector<record>()));
				result.first->second.push_back(r);
			}
			else
				i->second.push_back(r);
		}
		for (map<string, vector<record> >::iterator i = license_records.begin(); i != license_records.end(); i++) {
			// internally, the elements in the map are sorted from lower to higher key value
			vector<record>& records = i->second;
			int bill = calculate_bill(fares, records);
			if (bill)
				cout << i->first << " $" << bill / 100 << '.' << setw(2) << setfill('0') << bill % 100 << endl;
		}
		if (cases)
			cout << endl; // print a blink line to separate the two consecutive cases
	}
	return 0;
}

