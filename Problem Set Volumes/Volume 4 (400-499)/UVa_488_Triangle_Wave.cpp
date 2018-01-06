
/*
	UVa 488 - Triangle Wave

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_488_Triangle_Wave.cpp
*/

#include <iostream>
using namespace std;

const char* waves[] = {
	"",
	"1\n",
	"1\n22\n1\n",
	"1\n22\n333\n22\n1\n",
	"1\n22\n333\n4444\n333\n22\n1\n",
	"1\n22\n333\n4444\n55555\n4444\n333\n22\n1\n",
	"1\n22\n333\n4444\n55555\n666666\n55555\n4444\n333\n22\n1\n",
	"1\n22\n333\n4444\n55555\n666666\n7777777\n666666\n55555\n4444\n333\n22\n1\n",
	"1\n22\n333\n4444\n55555\n666666\n7777777\n88888888\n7777777\n666666\n55555\n4444\n333\n22\n1\n",
	"1\n22\n333\n4444\n55555\n666666\n7777777\n88888888\n999999999\n88888888\n7777777\n666666\n55555\n4444\n333\n22\n1\n"
};

int main()
{
	int nr_cases;
	cin >> nr_cases;
	while (nr_cases--) {
		int amplitude, frequency;
		cin >> amplitude >> frequency;
		if (amplitude < 0)
			amplitude = 0;
		const char* w = waves[amplitude];
		for (int f = 0; f < frequency; f++) {
			if (f)
				cout << endl;
			cout << w;
		}
		if (nr_cases)
			cout << endl; // outputs of two consecutive cases will be separated by a blank line
	}
	return 0;
}

