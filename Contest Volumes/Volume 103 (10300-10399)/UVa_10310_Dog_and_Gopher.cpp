
/*
	13.6.1 Dog and Gopher
	PC/UVa IDs: 111301/10310, Popularity: A, Success rate: average Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10310_Dog_and_Gopher.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <cstdio>
using namespace std;

inline double square_distance(double dx, double dy)
{
	return dx * dx + dy * dy;
}

int main(int /* argc */, char** /* argv */)
{
	string line;
	istringstream iss;
	while (getline(cin, line)) {
		if (line.empty())
			continue; // ignore a blank line between two consecutive sets
		iss.str(line);
		int nr_holes;
		pair<double, double> gopher, dog;
		iss >> nr_holes >> gopher.first >> gopher.second >> dog.first >> dog.second;
		iss.clear();
		bool escaped = false;
		pair<double, double> escape_hole;
		while (nr_holes--) {
			getline(cin, line);
			if (!escaped) {
				iss.str(line);
				pair<double, double> hole;
				iss >> hole.first >> hole.second;
				iss.clear();
				// see if the distance from the dog to a gopher hole is at least twice longer than the distance from the gopher
				double d_gopher = square_distance(hole.first - gopher.first, hole.second - gopher.second);
				double d_dog = square_distance(hole.first - dog.first, hole.second - dog.second);
				if (d_dog >= d_gopher * 4.0) {
					escaped = true; escape_hole = hole;
				}
			}
		}
		if (escaped)
			printf("The gopher can escape through the hole at (%.3f,%.3f).\n", escape_hole.first, escape_hole.second);
		else
			printf("The gopher cannot escape.\n");
	}
	return 0;
}

