
/*
	UVa 10268 - 498-bis

	To build using Visucal Studio 2012:
		cl -EHsc -O2 UVa_10268_498_bis.cpp
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	string line;
	istringstream iss;
	while (getline(cin, line)) {
		iss.str(line);
		int x;
		iss >> x;
		iss.clear();
		getline(cin, line);
		iss.str(line);
		int c;
		vector<long long> coefficients;
		while (iss >> c)
			coefficients.push_back(c);
		iss.clear();
		int n = static_cast<int>(coefficients.size()) - 1;
		long long result = 0;
		if (n > 0) {
			result = n * coefficients[0];
			for (int i = 1, d = n - 1; i < n; i++, d--) {
				result *= x;
				result += d * coefficients[i];
			}
		}
		cout << result << endl;
	}
	return 0;
}

