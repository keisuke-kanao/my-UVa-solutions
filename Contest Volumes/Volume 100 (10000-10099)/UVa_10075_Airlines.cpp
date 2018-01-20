
/*
	12.6.8 Airlines
	PC/UVa IDs: 111208/10075, Popularity: C, Success rate: high Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10075_Airlines.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <climits>
#include <cfloat>
#include <cmath>
using namespace std;

const double pi = 3.141592653589793;
const double sphere_radius  = 6378.0;

#if 0
double great_circle_distance(double radius, double latitude_s, double longitude_s, double latitude_f, double longitude_f)
{
/*
	latitude_s/_f and longitude_s/_f are in units of radian (radian = (pi / 180) * degree)
*/
	double lambda = longitude_f - longitude_s;
	double delta = acos(sin(latitude_s) * sin(latitude_f) + cos(latitude_s) * cos(latitude_f) * cos(lambda));
	return radius * delta;
}
#else
double great_circle_distance(double radius, double latitude_s, double longitude_s, double latitude_f, double longitude_f)
{
/*
	latitude_s/_f and longitude_s/_f are in units of radian (radian = (pi / 180) * degree)
*/
	double phi = latitude_f - latitude_s, lambda = longitude_f - longitude_s;
	double delta = pow(sin(phi / 2.0), 2) + cos(latitude_s) * cos(latitude_f) * pow(sin(lambda / 2.0), 2);
	delta = 2 * asin(sqrt(delta));
	return radius * delta;
}
#endif

void floyd_warshall_with_paths_reconstruction(int n, vector < vector<int> >& paths)
{
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (paths[i][k] != INT_MAX && paths[k][j] != INT_MAX) {
					int through_k = paths[i][k] + paths[k][j]; // distance through vertex k
 					if (through_k < paths[i][j])
						paths[i][j] = through_k;
				}
}

int main(int /* argc */, char** /* argv */)
{
	for (int nr_case = 0; ; nr_case++) {
		int nr_cities, nr_flights, nr_queries;
		cin >> nr_cities >> nr_flights >> nr_queries;
		if (!nr_cities && !nr_flights && !nr_queries)
			break;
		if (nr_case)
			cout << endl; // print a blank line between two consecutive test cases
		map<string, pair<double, double> > cities; // key is a name, 
			// value is a location (latitude and longitude in units of radian)
		for (int i = 0; i < nr_cities; i++) {
			string name;
			double latitude, longitude;
			cin >> name >> latitude >> longitude;
			pair<double, double> location = pair<double, double>(latitude * pi / 180.0, longitude * pi / 180.0);
			cities.insert(pair<string, pair<double, double> >(name, location));
		}
		vector< vector<int> > flights(nr_cities, vector<int>(nr_cities, INT_MAX));
		for (int i = 0; i < nr_flights; i++) {
			string cs, cf;
			cin >> cs >> cf;
			size_t city_s = distance(cities.begin(), cities.find(cs)), city_f = distance(cities.begin(), cities.find(cf));
			map<string, pair<double, double> >::iterator s = cities.begin(), f = cities.begin();
			advance(s, city_s); advance(f, city_f);
			pair<double, double>& location_s = s->second, location_f = f->second;
			double gcd = great_circle_distance(sphere_radius,
				location_s.first, location_s.second, location_f.first, location_f.second);
			flights[city_s][city_f] = static_cast<int>(gcd + 0.5); // round to the nearest integer
		}
		floyd_warshall_with_paths_reconstruction(nr_cities, flights);
		cout << "Case #" << nr_case + 1 << endl;
		for (int i = 0; i < nr_queries; i++) {
			string cs, cf;
			cin >> cs >> cf;
			size_t city_s = distance(cities.begin(), cities.find(cs)), city_f = distance(cities.begin(), cities.find(cf));
			if (flights[city_s][city_f] != INT_MAX)
				cout << flights[city_s][city_f] << " km\n";
			else
				cout << "no route exists\n";
		}
	}
	return 0;
}

