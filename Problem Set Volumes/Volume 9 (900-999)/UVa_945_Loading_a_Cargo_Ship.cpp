
/*
	UVa 945 - Loading a Cargo Ship

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_945_Loading_a_Cargo_Ship.cpp
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int c_max = 9, p_max = 999;

struct container {
	int weight_;
	int nr_packages_;
	int packages_[p_max];
} containers[c_max];

int main()
{
	bool printed = false;
	int c;
	while (scanf("%d", &c) != EOF) {
		if (printed)
			putchar('\n');
		else
			printed = true;
		for (int i = 0; i < c; i++) {
			scanf("%d", &containers[i].weight_);
			containers[i].nr_packages_ = 0;
		}
		int p;
		scanf("%d", &p);
		int min_nr_packages = 0, unloaded = 0;
		for (int i = 0; i < p; i++) {
			int weight;
			scanf("%d", &weight);
			if (unloaded) {
				unloaded += weight;
				continue;
			}
			int ci = -1;
			for (int j = 0; j < c; j++)
				if (containers[j].nr_packages_ == min_nr_packages) {
					if (ci == -1 || containers[j].weight_ > containers[ci].weight_)
						ci = j;
				}
			if (ci == -1 || containers[ci].weight_ < weight)
				unloaded += weight;
			else {
				containers[ci].weight_ -= weight;
				containers[ci].packages_[containers[ci].nr_packages_++] = weight;
				min_nr_packages = i + 1;
				for (int j = 0; j < c; j++)
					min_nr_packages = min(min_nr_packages, containers[j].nr_packages_);
			}
		}
		int cargo = 0, unused = 0, max_nr_packages = 0;
		for (int i = 0; i < c; i++) {
			max_nr_packages = max(max_nr_packages, containers[i].nr_packages_);
			unused += containers[i].weight_;
			for (int j = 0; j < containers[i].nr_packages_; j++)
				cargo += containers[i].packages_[j];
		}
		for (int i = max_nr_packages; i > 0; i--)
			for (int j = 0; j < c; j++) {
				if (containers[j].nr_packages_ >= i)
					printf("%d", containers[j].packages_[i - 1]);
				else
					putchar(':');
				printf("%c", (j < c - 1) ? ' ' : '\n');
			}
		for (int i = 0; i < c * 2 - 1; i++)
			putchar('=');
		putchar('\n');
		for (int i = 1; i <= c; i++)
			printf("%d%c", i, ((i < c) ? ' ' : '\n'));
		printf("\ncargo weight: %d\n", cargo);
		printf("unused weight: %d\n", unused);
		printf("unloaded weight: %d\n", unloaded);
	}
	return 0;
}

