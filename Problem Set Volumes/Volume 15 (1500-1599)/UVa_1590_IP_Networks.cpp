
/*
	UVa 1590 - IP Networks

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_1590_IP_Networks.cpp
*/

/*
	Network_address = IP_address & Network_mask.
	And for all IP addresses, Network address should be the same.
*/

#include <cstdio>

const int m_max = 1000;
unsigned int ip_addresses[m_max];

void print_address(unsigned int address)
{
	printf("%u.%u.%u.%u\n", (address & 0xff000000) >> 24, (address & 0x00ff0000) >> 16,
		(address & 0x0000ff00) >> 8, address & 0x000000ff);
}

int main()
{
	const int nr_bits = 32;
	int m;
	while (scanf("%d", &m) != EOF) {
		for (int i = 0; i < m;i++) {
			int b0, b1, b2, b3;
			scanf("%d.%d.%d.%d", &b0, &b1, &b2, &b3);
			ip_addresses[i] = b0 << 24 | b1 << 16 | b2 << 8 | b3;
		}
		unsigned int mask = 0xffffffff, b = 1, address;
		for (int i = 0; i <= nr_bits; i++, mask &= ~b, b <<= 1) {
			address = ip_addresses[0] & mask;
			int j;
			for (j = 1; j < m; j++)
				if ((ip_addresses[j] & mask) != address)
					break;
			if (j == m)
				break;
		}
		print_address(address);
		print_address(mask);
	}
	return 0;
}

