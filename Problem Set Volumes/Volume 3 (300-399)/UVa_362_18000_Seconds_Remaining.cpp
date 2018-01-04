
/*
	UVa 362 - 18,000 Seconds Remaining

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_362_18000_Seconds_Remaining.cpp
*/

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	for (int nr_ds = 1; ; nr_ds++) {
		int nr_bytes_left;
		cin >> nr_bytes_left;
		if (!nr_bytes_left)
			break;
		cout << "Output for data set "<< nr_ds << ", " << nr_bytes_left << " bytes:\n";
		int nr_seconds = 0, nr_bytes_transferred = 0;
		while (true) {
			int nr_bytes;
			cin >> nr_bytes;
			nr_seconds++;
			nr_bytes_left -= nr_bytes;
			nr_bytes_transferred += nr_bytes;
			if (!(nr_seconds % 5)) {
				cout << "   Time remaining: ";
				if (nr_bytes_transferred) {
					int nr_seconds_remaing = (nr_bytes_left * 5) / nr_bytes_transferred;
					if ((nr_bytes_left * 5) % nr_bytes_transferred)
						nr_seconds_remaing++;
					cout << nr_seconds_remaing << " seconds\n";
					nr_bytes_transferred = 0;
				}
				else
					cout << "stalled\n";
			}
			if (!nr_bytes_left)
				break;
		}
		cout << "Total time: " << nr_seconds <<" seconds\n\n";
	}
	return 0;
}

