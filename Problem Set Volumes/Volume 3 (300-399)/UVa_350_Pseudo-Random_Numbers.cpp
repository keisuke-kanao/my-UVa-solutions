
/*
	UVa 350 - Pseudo-Random Numbers

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_350_Pseudo-Random_Numbers.cpp

	from 1996 ACM North Central Programming Contest November 9, 1996 Problem F
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_US_NorthCen/1996/index.html)
*/

#include <iostream>
#include <map>
using namespace std;

int main()
{
	for (int c = 1; ; c++) {
		long long z;
		int i, m, l;
		cin >> z >> i >> m >> l;
		if (!z && !i && !m && !l)
			break;
		map<int, int> numbers;
			// key is a number, value is the order when the number is generated
		int n = 0;
		numbers.insert(make_pair(l, n));
		while (true) {
			l = static_cast<int>((z * l + i) % m);
			n++;
			pair<map<int, int>::iterator, bool> result = numbers.insert(make_pair(l, n));
			if (!result.second) {
				n -= result.first->second;
				break;
			}
		}
		cout << "Case " << c << ": " << n << endl;
	}
	return 0;
}

