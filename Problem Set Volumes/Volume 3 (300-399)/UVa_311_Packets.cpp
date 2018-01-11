
/*
	UVa 311 - Packets

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_311_Packets.cpp

	from ACM Central European Regionals 1996 Problem D
	(http://www.ntnu.edu.tw/acm/ProblemSetArchive/B_EU_CERC/1996/index.html)

	The ACM ICPC Problem Set Archive
		(http://www.ntnu.edu.tw/acm/ProblemSetArchive.html)

*/

#include <iostream>
#include <algorithm>
using namespace std;

const int parcel_size = 6;

void pack_packets_1_2(int nr_squares, int nr_packets_2, int packets[]) // pack a parcel with packets of size 2 x 2 and 1 x 1
{
	if (packets[2]) {
		nr_packets_2 = min(packets[2], nr_packets_2);
		packets[2] -= nr_packets_2;
		nr_squares -= nr_packets_2 * 4;
	}
	if (packets[1])
		packets[1] -= min(packets[1], nr_squares);
}

int main()
{
	int packets[parcel_size + 1]; // packets[i] is the number of packets of size i x i
	while (true) {
		cin >> packets[1] >> packets[2] >> packets[3] >> packets[4] >> packets[5] >> packets[6];
		if (!packets[1] && !packets[2] && !packets[3] && !packets[4] && !packets[5] && !packets[6])
			break;
		int nr_parcels = 0;
		if (packets[6])
			nr_parcels += packets[6]; // A packet of size 6 x 6 occupies the whole parcel on its own.
		if (packets[5]) {
			// A parcel is packed with 1 packet of size 5 x 5 and at most 11 packets of size 1 x 1.
			nr_parcels += packets[5];
			if (packets[1])
				packets[1] -= min(packets[1], packets[5] * 11);
		}
		if (packets[4]) {
			// A parcel is packed with 1 packet of size 4 x 4 and at most 5 packets of size 2 x 2.
			nr_parcels += packets[4];
			do
				pack_packets_1_2(20, 5, packets);
			while (--packets[4]);
		}
		if (packets[3]) {
			for ( ; packets[3] > 3; packets[3] -= 4)
				nr_parcels++; // A  parcel is packed with 4 packets of size 3 x 3.
			if (packets[3] == 3) {
				// A parcel is packed with 3 packets of size 3 x 3 and at most 1 packet of size 2 x 2.
				nr_parcels++;
				pack_packets_1_2(9, 1, packets);
			}
			else if (packets[3] == 2) {
				// A parcel is packed with 2 packets of size 3 x 3 and at most 3 packets of size 2 x 2.
				nr_parcels++;
				pack_packets_1_2(18, 3, packets);
			}
			else if (packets[3] == 1) {
				// A parcel is packed with 1 packet of size 3 x 3 and at most 5 packets of size 2 x 2.
				nr_parcels++;
				pack_packets_1_2(27, 5, packets);
			}
		}
		while (packets[2]) {
			// A parcel is packed with at most 9 packets of size 2 x 2.
			nr_parcels++;
			pack_packets_1_2(36, 9, packets);
		}
		while (packets[1]) {
			// A parcel is packed with 36 packets of size 1 x 1.
			nr_parcels++;
			packets[1] -= min(packets[1], 36);
		}
		cout << nr_parcels << endl;
	}
	return 0;
}

