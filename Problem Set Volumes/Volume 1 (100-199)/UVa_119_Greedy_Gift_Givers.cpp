
/*
	UVa 119 - Greedy Gift Givers

	To build using Visual Studio 2008:
		cl -EHsc -O2 UVa_119_Greedy_Gift_Givers.cpp
*/

#include <cstdio>
#include <cstring>
using namespace std;

const int nr_people_max = 10, name_length_max = 12;
char persons[nr_people_max][name_length_max + 1];
int nr_people;
int gifts[nr_people_max];

int get_person(const char* s)
{
	for (int i = 0; i < nr_people; i++)
		if (!strcmp(s, persons[i]))
			return i;
	return -1;
}

int main()
{
	bool printed = false;
	while (scanf("%d", &nr_people) != EOF) {
		if (printed)
			putchar('\n');
		else
			printed = true;
		for (int i = 0; i < nr_people; i++)
			scanf("%s", persons[i]);
		memset(gifts, 0, sizeof(gifts));
		for (int i = 0; i < nr_people; i++) {
			char giver[name_length_max];
			int amount, nr_receivers;
			scanf("%s %d %d", giver, &amount, &nr_receivers);
			if (nr_receivers) {
				int gift = amount / nr_receivers;
				gifts[get_person(giver)] -= amount;
				gifts[get_person(giver)] += amount - gift * nr_receivers;
				for (int j = 0; j < nr_receivers; j++) {
					char receiver[name_length_max];
					scanf("%s", receiver);
					gifts[get_person(receiver)] += gift;
				}
			}
/*
			else
				gifts[get_person(giver)] += amount;
*/
#ifdef DEBUG
			for (int i = 0; i < nr_people; i++)
				printf("%s %d\n", persons[i], gifts[i]);
#endif
		}
		for (int i = 0; i < nr_people; i++)
			printf("%s %d\n", persons[i], gifts[i]);
	}
	return 0;
}

