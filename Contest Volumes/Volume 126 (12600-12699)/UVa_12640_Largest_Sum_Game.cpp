
/*
	UVa 12640 - Largest Sum Game

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_12640_Largest_Sum_Game.cpp
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

int main()
{
	string s;
	while (getline(cin, s)) {
		istringstream iss(s);
		int max_ending_here = 0, max_so_far = 0;
		int X;
		while (iss >> X) {
			max_ending_here = max(0, max_ending_here + X);
			max_so_far = max(max_so_far, max_ending_here);
		}
		cout << max_so_far << endl;
	}
	return 0;
}

