
/*
	UVa 10281 - Average Speed

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10281_Average_Speed.cpp
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	int h, m, s, start = 0, current;
	double new_speed, speed = 0.0;
	double distance_travelled = 0.0;
	string line;
	while (getline(cin, line)) {
		istringstream iss(line);
		char c, d;
		if (iss >> h >> c >> m >> d >> s) {
			current = h * 3600 + m * 60 + s;
			if (iss >> new_speed) {
				current -= start;
				if (current < 0)
					current += 86400;
				distance_travelled += speed * current / 3600.0;
				start = h * 3600 + m * 60 + s;
				speed = new_speed;
			}
			else {
				current -= start;
				if (current < 0)
					current += 86400;
				cout << setfill('0') << setw(2) << h << ':' << setw(2) << m << ':' << setw(2) << s << ' ' <<
					fixed << setprecision(2) << distance_travelled + speed * current / 3600.0 << " km\n";
			}
		}
	}
	return 0;
}

