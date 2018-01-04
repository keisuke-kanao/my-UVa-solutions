
/*
	UVa 11491 - Erasing and Winning

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11491_Erasing_and_Winning.cpp
*/

#include <cstdio>
#include <list>
using namespace std;

int main()
{
	const int N_max = 100000;
	while (true) {
		int N, D;
		scanf("%d %d", &N, &D);
		if (!N)
			break;
		char s[N_max + 1];
		scanf("%s", s);
		list<int> numbers;
		numbers.push_back(10); // sentinel
		for (int i = 0; i < N; i++)
			numbers.push_back(s[i] - '0');
		numbers.push_back(10); // sentinel
		list<int>::iterator tail = numbers.begin(), head = numbers.begin();
        ++tail;
		while (D) {
			if (*head < *tail) {
				numbers.erase(head);
				--tail;
				head = tail;
				++tail;
				D--;
			}
			else {
				++tail;
				++head;
			}
        }
		numbers.pop_front(); numbers.pop_back(); // remove sentinels
		for (tail = numbers.begin(); tail != numbers.end(); ++tail)
            printf("%d", *tail);
		putchar('\n');
	}
	return 0;
}
