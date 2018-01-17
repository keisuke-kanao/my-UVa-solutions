
/*
	4.6.7 ShellSort
	PC/UVa IDs: 110407/10152, Popularity: B, Success rate: average Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10152_ShellSort.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct turtle {
	string name;
	int desired_order; // desired order (0 for the top of stack)
};

bool compare_desired_order(const turtle& i, const turtle& j)
{
	return i.desired_order < j.desired_order;
}

int main(int /* argc */, char ** /* argv */)
{
	string line;
	istringstream iss;

	// read the number of test cases
	getline(cin, line);
	iss.str(line);
	int cases;
	iss >> cases;
	iss.clear();
	while (cases--) {
		// read the number of turtles
		getline(cin, line);
		iss.str(line);
		int n;
		iss >> n;
		iss.clear();
		vector<turtle> turtles;
		map<string, int> original_orders; // key is a turtle's name, value is its original order
		for (int i = 0; i < n; i++) { // read the original ordering of the turtle stack (from top to bottom)
			turtle t;
			getline(cin, t.name);
			turtles.push_back(t);
			original_orders.insert(make_pair(t.name, i));
		}
		for (int i = 0; i < n; i++) { // read the desired ordering of the stack
			string name;
			getline(cin, name);
			turtles[original_orders[name]].desired_order = i;
		}
		int lowest_order_found = -1; // the lowest desired order found so far
		int lowest_order_to_be_climbed = -1; // the lowest desired order from which a turtle should be climbed up
		for (int i = 0; i < turtles.size(); i++) {
			int desired_order = turtles[i].desired_order;
			if (lowest_order_found > desired_order)
				// the turtle should be climbed up, since there are some other turtles that should be below it
				lowest_order_to_be_climbed = max(lowest_order_to_be_climbed, desired_order);
			lowest_order_found = max(lowest_order_found, desired_order);
		}
		if (lowest_order_to_be_climbed != -1) { // some turtules should be climbed up
			// sort the vector of turtles by their desired orders
			sort(turtles.begin(), turtles.end(), compare_desired_order);
			for (int i = lowest_order_to_be_climbed; i >= 0; i--)
				cout << turtles[i].name << endl;
		}
		cout << endl; // print a blank line after each test case
	}
	return 0;
}

