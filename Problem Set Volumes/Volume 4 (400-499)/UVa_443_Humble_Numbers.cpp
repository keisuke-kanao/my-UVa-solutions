
/*
	UVa 443 - Humble Numbers

	To build using Visucal Studio 2008:
		cl -EHsc -O2 UVa_443_Humble_Numbers.cpp

	from University of Ulm Local Contest 1996 Problem E
		(http://www.informatik.uni-ulm.de/acm/Locals/1996/)
*/

#include <iostream>
#include <queue>
#include <functional>
using namespace std;

const int nr_humble_numbers = 5842;
int humble_numbers[nr_humble_numbers + 1]; // humble_numbers[i] is the i-th humble number

int main()
{
	priority_queue< long long, vector<long long>, greater<long long> > pq;
	pq.push(1);
	int nr = 0;
	long long pn = -1, cn;
	while (true) {
		do {
			cn = pq.top();
			pq.pop();
		} while (cn == pn);
		humble_numbers[++nr] = static_cast<int>(cn);
		if (nr == nr_humble_numbers)
			break;
		pq.push(cn * 2);
		pq.push(cn * 3);
		pq.push(cn * 5);
		pq.push(cn * 7);
		pn = cn;
	}
#ifdef DEBUG
	cout << humble_numbers[nr_humble_numbers] << endl;
#endif
	while (true) {
		int i;
		cin >> i;
		if (!i)
			break;
		switch (i % 10) {
		case 1:
			if ((i % 100) == 11)
				cout << "The " << i << "th humble number is " << humble_numbers[i] << ".\n";
			else
				cout << "The " << i << "st humble number is " << humble_numbers[i] << ".\n";
			break;
		case 2:
			if ((i % 100) == 12)
				cout << "The " << i << "th humble number is " << humble_numbers[i] << ".\n";
			else
				cout << "The " << i << "nd humble number is " << humble_numbers[i] << ".\n";
			break;
		case 3:
			if ((i % 100) == 13)
				cout << "The " << i << "th humble number is " << humble_numbers[i] << ".\n";
			else
				cout << "The " << i << "rd humble number is " << humble_numbers[i] << ".\n";
			break;
		default:
			cout << "The " << i << "th humble number is " << humble_numbers[i] << ".\n";
			break;
		}
	}
	return 0;
}

