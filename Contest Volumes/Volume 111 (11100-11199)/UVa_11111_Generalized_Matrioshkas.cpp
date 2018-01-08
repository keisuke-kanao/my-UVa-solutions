
/*
	UVa 11111 - Generalized Matrioshkas

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_11111_Generalized_Matrioshkas.cpp

	from XX National Programming Contest ACIS REDIS / ACM ICPC 2006 Problem B
		(http://www.acis.org.co/index.php?id=828)
*/

#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <utility>
#include <cstdlib>
using namespace std;

int main(int /* argc */, char** /* argv */)
{
	string line;
	while (getline(cin, line)) {
		istringstream iss(line);
		stack< pair<int, int> > st;
			// first is the original capacity, second is the remaining capacity
		bool toys = false, valid = true;
		int n;
		while (iss >> n && valid) {
			toys = true;
			if (n < 0) { // start of a new toy
				n = labs(n);
				if (!st.empty()) {
					if (st.top().second <= n)
						valid = false;
					else
						st.top().second -= n;
				}
				st.push(make_pair(n, n));
			}
			else { // end of the toy
				if (st.empty() || st.top().first != n)
					valid = false;
				else
					st.pop();
			}
		}
		if (!toys || !st.empty())
			valid = false;
		cout << ((valid) ? ":-) Matrioshka!\n" : ":-( Try again.\n");
	}
	return 0;
}

