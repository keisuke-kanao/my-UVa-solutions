
/*
	UVa 404 - Radar Scopes

	from ACM South Central Regional Programming Contest 1995 Problem #5
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_SouthCen/1995/index.html)

	The ACM ICPC Problem Set Archive
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive.html)

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_404_Radar_Scopes.cpp
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <map>
#include <cfloat>
#include <cmath>
using namespace std;

const double pi = 2.0 * acos(0.0); // 3.14159265358979323846
const double radar_radius = 10.0; // in miles
const double radar_sweep_cycle = 5.0; // inseconds

enum warnings {
	unknown = -2, no_warnings, equipment_warning, new_intrusion, new_aloft, domain_exited, domain_loss
};

const char* warning_messages[] = {
	"equipment warning", "new intrusion", "new aloft", "domain exited", "domain loss"
};

struct airplane {
	string s_squawk; // squawk number in string
	int squawk; // squawk number, between 0 and 32767
	double azimuth; // in degrees between 0 and 360
	double distance; // in miles
	double speed; // in miles/hour
	int warning;
};

bool is_outside_of_radar_scope(const airplane& ap)
{
	return ap.distance + ap.speed * 1.10 * radar_sweep_cycle / 3600.0 >= radar_radius;
}

bool is_equipment_warning(const airplane& first, const airplane& second)
{
	double angle = (first.azimuth - second.azimuth) * pi / 180.0;
	double distance =sqrt(first.distance * first.distance + second.distance * second.distance
		- 2.0 * first.distance * second.distance * cos(angle));
	double measured_speed = distance * 3600.0 / radar_sweep_cycle;
	double average_speed = (first.speed + second.speed) / 2.0;
	return average_speed < measured_speed * 0.90 || average_speed > measured_speed * 1.10;
}

int main(int /* argc */, char** /* argv */)
{
	int senario_nr = 1;
	int n1, n2;
	while (cin >> n1) {
		airplane ap;
		ap.warning = unknown;
		map<int, airplane> airplanes; // indexed by squawk numbers
		for (int i = 0; i < n1; i++) {
			cin >> ap.s_squawk;
			istringstream iss(ap.s_squawk);
			iss >> dec >> ap.squawk;
			cin >> dec >> ap.azimuth >> ap.distance >> ap.speed;
			airplanes.insert(make_pair(ap.squawk, ap));
		}
		cin >> n2;
		for (int i = 0; i < n2; i++) {
			cin >> ap.s_squawk;
			istringstream iss(ap.s_squawk);
			iss >> dec >> ap.squawk;
			cin >> dec >> ap.azimuth >> ap.distance >> ap.speed;
			map<int, airplane>::iterator j = airplanes.find(ap.squawk);
			if (j != airplanes.end())
				j->second.warning = (is_equipment_warning(j->second, ap)) ?
					equipment_warning : no_warnings;
			else { // not found in the first sweep
				ap.warning = (is_outside_of_radar_scope(ap)) ? new_intrusion : new_aloft;
				airplanes.insert(make_pair(ap.squawk, ap));
			}
		}
		cout << "Scenario # " << senario_nr++ << endl;
		for (map<int, airplane>::iterator i = airplanes.begin(); i != airplanes.end(); i++) {
			airplane& ap = i->second;
			if (ap.warning == unknown) // not found in the second sweep
				ap.warning = (is_outside_of_radar_scope(ap)) ? domain_exited : domain_loss;
			if (ap.warning > no_warnings)
				cout << setw(5) << setfill(' ') << ap.s_squawk << " -- " << warning_messages[ap.warning] << endl;
		}
		cout << endl; // after each scenario, print a blank line
	}
	return 0;
}

