
/*
	UVa 10055 - Hashmat the Brave Warrior

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_10055_Hashmat_the_Brave_Warrior.cpp
*/


#include <iostream>
using namespace std;

int main(int /* argc */, char** /* argv */)
{
	long long i, j;
	while (cin >> i >> j) {
		long long diff = i - j;
		if (diff < 0)
			diff = -diff;
		cout << diff << endl;
	}
	return 0;
}

