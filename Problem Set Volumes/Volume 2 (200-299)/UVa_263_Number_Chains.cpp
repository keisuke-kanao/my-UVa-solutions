
/*
	UVa 263 - Number Chains

	To build using Visual Studio 2008:
		cl -EHsc UVa_263_Number_Chains.cpp
*/

#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <functional>
#include <algorithm>
#include <cstdlib>
using namespace std;

int main()
{
	while (true) {
		string s;
		cin >> s;
		int on = atoi(s.c_str());
		if (!on)
			break;
		cout << "Original number was " << on << endl;
		ostringstream ooss;
		ooss << on;
		s = ooss.str();
		set<int> numbers;
		int nr_length = 0;
		while (true) {
			sort(s.begin(), s.end(), greater<char>());
			int i = atoi(s.c_str());
			sort(s.begin(), s.end());
			int j = atoi(s.c_str());
			int k = i - j;
			cout << i << " - " << j << " = " << k << endl;
			nr_length++;
			pair<set<int>::iterator, bool> result = numbers.insert(k);
			if (!result.second)
				break;
			ostringstream oss;
			oss << k;
			s = oss.str();
		}
		cout << "Chain length " << nr_length << endl << endl;
	}
	return 0;
}

