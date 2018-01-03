
/*
	UVa 514 - Rails

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_514_Rails.cpp

	from ACM Central European Regionals 1997
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_CERC/1997/index.html)
*/

/*
Our Quest to Solve the UVa ICPC Online Problem Set :: UVa Solutions:
	(http://www.questtosolve.com/browse.php?vol=5)

Keep a stack of integers that represents the station, 
and a list of integers that has all the trains in order on side A.

Iterate through the input. For each train, 
if it's on top of the stack, then pop it off, 
and if it's somewhere in the list, then push all the trains in front of it onto the stack, then discard the train. 
If the train isn't in either location, then it must be buried in the stack and is therefore unreachable, 
so the arrangement can't be made.
*/

#include <iostream>
#include <vector>
#include <stack>
#ifdef __ELAPSED_TIME__
#include <ctime>
#endif
using namespace std;

int main()
{
#ifdef __ELAPSED_TIME__
	clock_t start = clock();
#endif
	while (true) {
		int n;
		cin >> n;
		if (!n)
			break;
		while (true) {
			int cn;
			cin >> cn;
			if (!cn)
				break;
			vector<bool> pushed(n + 1, false);
			stack<int> st;
			for (int j = 1; j < cn; j++) {
				pushed[j] = true;
				st.push(j);
			}
			pushed[cn] = true;
			bool possible = true;
			for (int i = 1; i < n; i++) {
				cin >> cn;
				if (!possible)
					continue;
				if (!st.empty() && st.top() == cn)
					st.pop();
				else if (!pushed[cn]) {
					for (int j = 1; j < cn; j++)
						if (!pushed[j]) {
							pushed[j] = true;
							st.push(j);
						}
					pushed[cn] = true;
				}
				else
					possible = false;
			}
			cout << ((possible) ? "Yes\n" : "No\n");
		}
		cout << endl;
	}
#ifdef __ELAPSED_TIME__
	cerr << "elapsed time = " << static_cast<double>(clock() - start) / CLOCKS_PER_SEC << " sec.\n";
#endif
	return 0;
}

