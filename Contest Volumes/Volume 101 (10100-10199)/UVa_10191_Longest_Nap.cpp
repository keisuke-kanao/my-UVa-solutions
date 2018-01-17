/*
	4.6.4 Longest Nap
	PC/UVa IDs: 110404/10191, Popularity: B, Success rate: average Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10191_Longest_Nap.cpp
*/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair<int, int> schedule; // first is starting time, and second is endiing time

inline int get_time(int hour, int minute)
{
	return hour * 60 + minute;
}

inline int get_hour(int time)
{
	return time / 60;
}

inline int get_minute(int time)
{
	return time % 60;
}

bool compare_schedule(const schedule& i, const schedule& j)
{
	return i.first < j.first;
}

bool compare_nap(const schedule& i, const schedule& j)
{
	return (i.second - i.first) > (j.second - j.first);
}

int main(int /* argc */, char ** /* argv */)
{
	string line;
	istringstream iss;
	for (int day = 1; getline(cin, line); day++) { // read the number of scheduled appointments
		iss.str(line);
		int appointments;
		iss >> appointments;
		iss.clear();
		vector<schedule> schedules;
		schedules.push_back(schedule(get_time(10, 0), get_time(10, 0)));
		while (appointments--) {
			// read the starting time and the ending time of a schedule
			getline(cin, line);
			iss.str(line);
			int hour, minute, starting_time, ending_time;
			char c;
			iss >> hour >> c >> minute;
			starting_time = get_time(hour, minute);
			iss >> hour >> c >> minute; // read the ending time
			ending_time = get_time(hour, minute);
			iss.clear(); // discard the appointment string
			schedules.push_back(schedule(starting_time, ending_time)); // append a schedule
		}
		// sort the vector of schedules by their starting times
		sort(schedules.begin() + 1, schedules.end(), compare_schedule);
		schedules.push_back(schedule(get_time(18, 0), get_time(18, 0)));
		// generate the nap schedules from the time gap between the two consecutive schedules
		vector<schedule> naps;
		for (vector<schedule>::const_iterator j = schedules.begin(); j != schedules.end(); ) {
			vector<schedule>::const_iterator i = j++;
			if (j != schedules.end() && j->first > i->second) // there is a time gap between the two consecutive schedules
				naps.push_back(schedule(i->second, j->first)); // append a nap
		}
		// stable sort the vector of naps by their descending nap times
		stable_sort(naps.begin(), naps.end(), compare_nap);
		schedule& nap = naps.front();
		cout << "Day #" << day << ": the longest nap starts at " << get_hour(nap.first) << ':' << 
			setw(2) << setfill('0') << get_minute(nap.first) << " and will last for ";
		int time = nap.second - nap.first;
		if (time >= 60)
			cout << get_hour(time) << " hours and ";
		cout << get_minute(time) << " minutes.\n";
	}
	return 0;
}

