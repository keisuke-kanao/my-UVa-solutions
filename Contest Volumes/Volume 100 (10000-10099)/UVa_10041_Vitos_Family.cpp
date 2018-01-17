
/*
	4.6.1 VitoÅfs Family
	PC/UVa IDs: 110401/10041, Popularity: A, Success rate: high Level: 1

	To build using Visucal Studio 2008:
		cl -EHsc UVa_10041_Vitos_Family.cpp
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int /* argc */, char** /* argv */)
{
	// read the number of test cases
	int cases;
	cin >> cases;
	while (cases--) {
		// read the number of relatives
		int relatives;
		cin >> relatives;
		// read the street numbers
		vector<int> street_numbers(relatives);
		for (int i = 0; i < relatives; i++)
			cin >> street_numbers[i];
		// sort the street numbers in ascending order and find the median value of them
		sort(street_numbers.begin(), street_numbers.end());
		int vitos_house = street_numbers[relatives / 2]; // median of street numbers
		// calculate the sum of distances between the street numbers and their median value
		int sum = 0;
		for (int i = 0; i < relatives; i++) {
			int d = vitos_house - street_numbers[i];
			if (d < 0)
				d = -d;
			sum += d;
		}
		cout << sum << endl;
	}
	return 0;
}

