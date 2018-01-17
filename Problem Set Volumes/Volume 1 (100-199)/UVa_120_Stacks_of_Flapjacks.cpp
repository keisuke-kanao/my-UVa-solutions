
/*
	4.6.2 Stacks of Flapjacks
	PC/UVa IDs: 110402/120, Popularity: B, Success rate: high Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_120_Stacks_of_Flapjacks.cpp
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
	generate the vector of pancakes and sort it in the ascending order of their diameters
	for each slot in the vector of pancakes from the one of biggest diameter to the one of smallest diameter:
		remove a pancake

		decide a flipping position so that the just removed pancake is to be moved to its final position
		(i.e., the i-th smallest pancake is to be moved to the i-th position)

		if the pancake has been already located at its final position, no flipping for the current pancake is needed.
		else, do the flipping.

		during the flipping, the positions of the pancakes involved in the flipping are modified to the specify the 
		corresponsing moved position.

		print the flipping position

	repeat until the vector becomes empty
*/

typedef pair<int, int> pancake; // first is the diameter of a pancake, second is the original position of a pancake

bool compare_diameter(const pancake& i, const pancake& j)
{
	return i.first < j.first;
}

#ifdef DEBUG
void print_pancakes(const vector<pancake>& pancakes)
{
	for (int i = 0; i < pancakes.size(); i++)
		cout << pancakes[i].first << '@' << pancakes[i].second << ((i == pancakes.size() - 1) ? '\n' : ' ');
}
#endif

int main(int /* argc */, char ** /* argv */)
{
	string line;
	while (getline(cin, line)) {
		istringstream iss(line);
		vector<pancake> pancakes;
		for (int i = 0; ; i++) {
			int diameter;
			if (!(iss >> diameter))
				break;
			pancakes.push_back(pancake(diameter, i));
		}
		int count = pancakes.size(); // number of pancakes in the stack
		// print the original stack of pancakes
		for (int i = 0; i < count; i++)
			cout << pancakes[i].first << ((i == pancakes.size() - 1) ? '\n' : ' ');
		// sort the vector of pancakes in the ascending order of their diameters
		sort(pancakes.begin(), pancakes.end(), compare_diameter);
#ifdef DEBUG
		print_pancakes(pancakes);
#endif
		for(int i = 0; i < count; ) {
			pancake& pc = pancakes.back();
			int flip_pos = 0;
			if (pc.second != count - i - 1) {
				// decide a flip position such that the i-th smallest pancake is to be moved to the i-th position
				flip_pos = pc.second;
				// print the flip position
				cout << ((flip_pos) ? count - flip_pos : flip_pos + i + 1) << ' ';
				for (vector<pancake>::iterator it = pancakes.begin(); it != pancakes.end(); it++) {
					// for the cases when the flip position is not the last, reverse the position field of pancakes 
					// whose original posiion field are between the first and the flip position
					if (flip_pos) {
						if (it->second <= flip_pos)
							it->second = flip_pos - it->second;
					}
					// for the cases when the flip position is the last, reverse the position field of pancakes 
					// whose original position field are between the flip position and the last
					else
						it->second = flip_pos + (count - i) - it->second - 1;
				}
#ifdef DEBUG
				print_pancakes(pancakes);
#endif
			}
			if (!flip_pos) {
				pancakes.pop_back();
				i++;
			}
		}
		cout << "0\n";
	}
	return 0;
}

