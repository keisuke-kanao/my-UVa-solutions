
/*
	6.6.8 Steps
	PC/UVa IDs: 110608/846, Popularity: A, Success rate: high Level: 2

	To build using Visucal Studio 2008:
		cl -EHsc UVa_846_Steps.cpp
*/

#include <iostream>
using namespace std;

int number_of_steps(int previous_step, int distance)
{
	if (!distance)
		return 0;
	if (!previous_step) {
#ifdef DEBUG
		cout << previous_step << ' ' << 0 << ' ' << distance << endl;
#endif
		return 1 + number_of_steps(1, distance - 1);
	}
	else {
		int steps = previous_step * (previous_step + 1) / 2;
#ifdef DEBUG
		cout << previous_step << ' ' << steps << ' ' << distance << endl;
#endif
		if (steps > distance)
			return 1 + number_of_steps(previous_step - 1, distance - previous_step + 1);
		else if (steps + previous_step < distance)
			return 1 + number_of_steps(previous_step + 1, distance - previous_step - 1);
		else
			return 1 + number_of_steps(previous_step, distance - previous_step);
	}
}

int main(int /* argc */, char ** /* argv */)
{
	int cases;
	cin >> cases;
	while (cases--) {
		int x, y;
		cin >> x >> y;
		cout << number_of_steps(0, y - x) << endl;
	}
}

