
/*
	9.6.7 From Dusk Till Dawn
	PC/UVa IDs: 110907/10187, Popularity: B, Success rate: average Level: 3

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10187_From_Dusk_Till_Dawn.cpp
*/

/*
	Generate a DAG (Directed Acyclic Graph) where cities are vertices and edges are routes between them, 
	and each routes has the departure time and the total traveling time in units of hours.
	Apply Dijkstra's shortest path algorithm to calculate the smallest arrival time.
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <climits>
using namespace std;

const int min_departure_time = 18, max_arrival_time = 30, midnight = 24;

int normalize_time(int t) // convert time to a value between min_departure_time and max_arrival_time
{
	t %= 24;
	if (t < 12)
		t += 24;
	return t;
}

struct route {
	int to; // destination city
	int departure_time;
	int traveling_time;

	route(int _to, int _departure_time, int _traveling_time)
		: to(_to), departure_time(_departure_time), traveling_time(_traveling_time) {}
};

struct route_specification {
	string from; // departure city
	string to; // destination city
	int departure_time;
	int traveling_time;
};

int find_route(int nr_cities, int start, int destination, vector< vector<route> >& routes)
{
	// apply Dijkstra's shortest path algorithm
	vector<bool> in_tree(nr_cities, false);
	vector<int> arrival_times(nr_cities, INT_MAX);
	arrival_times[start] = min_departure_time;
	int i = start;
	do {
		in_tree[i] = true;
		for (int j = 0; j < routes[i].size(); j++) {
			int arrival_time = arrival_times[i];
			int at = normalize_time(arrival_time);
			route& r = routes[i][j];
			if (at > r.departure_time) {
				if (at < midnight)
					arrival_time += midnight - at;
				else
					arrival_time -= at - midnight;
				arrival_time += r.departure_time + r.traveling_time;
			}
			else
				arrival_time += (r.departure_time - at) + r.traveling_time;
			int to = routes[i][j].to;
			if (arrival_times[to] == INT_MAX || arrival_times[to] > arrival_time)
				arrival_times[to] = arrival_time;
		}
		i = -1;
		int min_arrival_time = INT_MAX;
		for (int j = 0; j < nr_cities; j++)
			if (!in_tree[j] && arrival_times[j] < min_arrival_time) {
				i = j;
				min_arrival_time = arrival_times[j];
			}
	} while (i != -1);
	if (arrival_times[destination] != INT_MAX) {
#ifdef DEBUG
		cout << "traveling time = " << arrival_times[destination] << endl;
#endif
		return (arrival_times[destination] - min_departure_time) / 24;
	}
	else
		return -1;
}

int main(int /* argc */, char** /* argv */)
{
	int cases;
	cin >> cases;
	for (int c = 0; c < cases; c++) {
		int nr_routes;
		cin >> nr_routes;
		vector<route_specification> specifications;
		set<string> cities;
		while (nr_routes--) {
			route_specification s;
			cin >> s.from >> s.to >> s.departure_time >> s.traveling_time;
			s.departure_time = normalize_time(s.departure_time);
			cities.insert(s.from); cities.insert(s.to);
			specifications.push_back(s);
		}
#ifdef DEBUG
		for (set<string>::iterator i = cities.begin(); i != cities.end(); i++)
			cout << distance(cities.begin(), i) << ':' << *i << ' ';
		cout << endl;
#endif
		vector< vector<route> > routes(cities.size());
		for (vector<route_specification>::const_iterator i = specifications.begin(); i != specifications.end(); i++) {
			if (i->departure_time < min_departure_time || i->departure_time + i->traveling_time > max_arrival_time)
				continue; // exclude the routes departing earlier than 18:00 or arriving later than 6:00
			int from = distance(cities.begin(), cities.find(i->from)), to = distance(cities.begin(), cities.find(i->to));
			routes[from].push_back(route(to, i->departure_time, i->traveling_time));
		}
		string start_city, destination_city;
		cin >> start_city >> destination_city;
		int start = distance(cities.begin(), cities.find(start_city)),
			destination = distance(cities.begin(), cities.find(destination_city));
		int blood = find_route(cities.size(), start, destination, routes);
		cout << "Test Case " << c + 1 << ".\n";
		if (blood != -1)
			cout << "Vladimir needs " << blood << " litre(s) of blood.\n";
		else
			cout << "There is no route Vladimir can take.\n";
	}
	return 0;
}

