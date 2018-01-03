
/*
	UVa 1064 - Network

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1064_Network.cpp

	UVa_1064_Network.ac.*.cpp are another solutions based on the 1064.cpp.
	Of those, UVa_1064_Network.ac.7.cpp is the last one.
	This solution is different from them and the one submitted very last.
*/

#include <set>
#include <algorithm>
#include <limits>
#include <cstdio>
using namespace std;

const int nr_messages_max = 5, nr_packets_max = 1000;

struct packet {
	int mn_, sn_, en_;
} packets[nr_packets_max];

struct packet_comparator {
	bool operator()(int i, int j) {
		return packets[i].sn_ < packets[j].sn_;
	}
};

struct message {
	int nr_data_, out_n_; // next byte numbet to be output
	set<int, packet_comparator> packets_;
} messages[nr_messages_max];

int remove_packet_buffers(message& m, int& out_n)
{
	int nr_data = 0;
	set<int, packet_comparator>::iterator pi = m.packets_.begin(), pe = m.packets_.end();
	for ( ; pi != pe; ++pi) {
		if (out_n < packets[*pi].sn_)
			break;
		nr_data += packets[*pi].en_ - packets[*pi].sn_ + 1;
		out_n = packets[*pi].en_ + 1;
	}
	if (nr_data)
		m.packets_.erase(m.packets_.begin(), pi);
	return nr_data;
}

int main()
{
	for (int case_nr = 1; ; case_nr++) {
		int N, M;
		scanf("%d %d", &N, &M);
		if (!N)
			break;
		for (int i = 0; i < N; i++)
			scanf("%d", &messages[i].nr_data_);
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &packets[i].mn_, &packets[i].sn_, &packets[i].en_);
			packets[i].mn_--;
		}
		int order[nr_messages_max]; // order in which messages will be out
		for (int i = 0; i < N; i++)
			order[i] = i;
		int buff_max = numeric_limits<int>::max();
		do {
#ifdef DEBUG
		for (int i = 0; i < N; i++)
			printf("%d%c", order[i], ((i < N - 1) ? ' ' : '\n'));
#endif
			int b = 0, b_max = 0, nr_out = 0;
			for (int i = 0; i < N; i++) {
				messages[i].out_n_ = 1;
				messages[i].packets_.clear();
			}
			for (int i = 0; i < M; i++) {
				const packet& p = packets[i];
				message& m = messages[p.mn_];
				if (p.mn_ == order[nr_out] && m.out_n_ == p.sn_) {
					m.out_n_ = p.en_ + 1;
					int nr_data = remove_packet_buffers(m, m.out_n_);
					if (nr_data)
						b -= nr_data;
					if (m.out_n_ == m.nr_data_ + 1) { // a message is complete
						for (nr_out++; nr_out < N; nr_out++) {
							message& mm = messages[order[nr_out]];
							if (nr_data = remove_packet_buffers(mm, mm.out_n_))
								b -= nr_data;
							if (mm.out_n_ < mm.nr_data_ + 1)
								break;
						}
					}
				}
				else {
					m.packets_.insert(i);
					b += p.en_ - p.sn_ + 1;
				}
				b_max = max(b_max, b);
#ifdef DEBUG
				printf("%d %d %d,  b: %d, b_max: %d\n", p.mn_, p.sn_, p.en_, b, b_max);
#endif
#ifndef DEBUG
				if (buff_max != numeric_limits<int>::max() && b_max >= buff_max)
					break;
#endif
			}
			buff_max = min(buff_max, b_max);
#ifdef DEBUG
			printf("buff_max: %d, buff_max_min: %d\n", b_max, buff_max);
#endif
		} while (next_permutation(order, order + N));
		printf("Case %d: %d\n\n", case_nr, buff_max);
	}
	return 0;
}

