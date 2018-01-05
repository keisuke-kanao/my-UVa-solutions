
/*
	UVa 10107 - What is the Median?

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_10107_What_is_the_Median.cpp
*/

#include <iostream>
#include <list>
using namespace std;

int main()
{
	list<unsigned int> above_median, below_median;
	unsigned int n;
	int nr = 0, nr_above_median = 0, nr_below_median = 0;
	while (cin >> n) {
		if (++nr == 1) {
			above_median.push_back(n);
			nr_above_median++;
		}
		else if (nr == 2) {
			if (n > above_median.front()) {
				below_median.push_back(above_median.front());
				above_median.pop_front();
				above_median.push_back(n);
			}
			else
				below_median.push_back(n);
			nr_below_median++;
		}
		else {
			if (n > above_median.front()) {
				list<unsigned int>::iterator i = above_median.begin(), e = above_median.end();
				for (++i; i != e; ++i)
					if (n <= *i)
						break;
				above_median.insert(i, n);
				nr_above_median++;
			}
			else {
				list<unsigned int>::reverse_iterator i = below_median.rbegin(), e = below_median.rend();
				for ( ; i != e; i++)
					if (n >= *i)
						break;
				below_median.insert(i.base(), n);
				nr_below_median++;
			}
			if (nr & 1) {
				if (nr_above_median < nr_below_median) {
					above_median.push_front(below_median.back());
					below_median.pop_back();
					nr_above_median++; nr_below_median--;
				}
			}
			else {
				if (nr_above_median < nr_below_median) {
					above_median.push_front(below_median.back());
					below_median.pop_back();
					nr_above_median++; nr_below_median--;
				}
				else if (nr_above_median > nr_below_median) {
					below_median.push_back(above_median.front());
					above_median.pop_front();
					nr_above_median--; nr_below_median++;
				}
			}
		}
		if (nr & 1)
			cout << above_median.front() << endl;
		else
			cout << (below_median.back() + above_median.front()) / 2 << endl;
	}
	return 0;
}

