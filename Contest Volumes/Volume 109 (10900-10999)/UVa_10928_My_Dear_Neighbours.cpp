
/*
	UVa 10928 - My Dear Neighbours

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10928_My_Dear_Neighbours.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

const int p_max = 1000;
int nr_neighbours[p_max + 1];

int main()
{
	string line;
	istringstream iss;
	getline(cin, line);
	iss.str(line);
	int n;
	iss >> n;
	iss.clear();
	while (n--) {
		getline(cin, line);
		iss.str(line);
		int p;
		iss >> p;
		iss.clear();
		int min_nr_neighbours = p;
		for (int i = 1; i <= p; i++) {
			getline(cin, line);
			iss.str(line);
			int nr = 0, neighbour;
			while (iss >> neighbour)
				nr++;
			iss.clear();
			nr_neighbours[i] = nr;
			if (nr < min_nr_neighbours)
				min_nr_neighbours = nr;
		}
		bool printed = false;
		for (int i = 1; i <= p; i++)
			if (nr_neighbours[i] == min_nr_neighbours) {
				if (printed)
					cout << ' ';
				else
					printed = true;
				cout << i;
			}
		cout << endl;
		if (n)
			getline(cin, line);
	}
	return 0;
}

