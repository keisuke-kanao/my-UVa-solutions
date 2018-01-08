
/*
	UVa 442 - Matrix Chain Multiplication

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_442_Matrix_Chain_Multiplication.cpp

	from ACM University of Ulm Local Contest 1996 Problem G
		(http://www.informatik.uni-ulm.de/acm/Locals/1996/)
*/

#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <utility>
using namespace std;

int main()
{
	const int nr_matrices_max = 'Z' - 'A' + 1;
	pair<int, int> matrices[nr_matrices_max]; //matrices[i].first is a row, matrices[i].second is a column
	string s;
	istringstream iss;
	getline(cin, s);
	iss.str(s);
	int n;
	iss >> n;
	iss.clear();
	for (int i = 0; i < n; i++) {
		getline(cin, s);
		iss.str(s);
		char c;
		iss >> c;
		int j = c - 'A';
		iss >> matrices[j].first >> matrices[j].second;
		iss.clear();
	}
	while (getline(cin, s)) {
		int nr_multiplications = 0;
		stack< pair<int, int> > st;
		bool error = false;
		for (const char* p = s.c_str(); *p && !error; p++) {
			if (*p >= 'A' && *p <= 'Z')
				st.push(matrices[*p - 'A']);
			else if (*p == ')') {
				if (st.size() < 2)
					error = true;
				else {
					pair<int, int> right = st.top();
					st.pop();
					pair<int, int> left = st.top();
					st.pop();
					if (left.second != right.first)
						error = true;
					else {
						nr_multiplications += left.first * left.second * right.second;
						st.push(make_pair(left.first, right.second));
					}
				}
			}
		}
		if (error)
			cout << "error\n";
		else
			cout << nr_multiplications << endl;

	}
	return 0;
}

