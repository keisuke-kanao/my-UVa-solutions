
/*
	UVa 11500 - Vampires

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_11500_Vampires.cpp
*/

/*

Reading Gambler's ruin (https://en.wikipedia.org/wiki/Gambler%27s_ruin)
there are 2 cases to consider. 
  The first case is "fair coin flipping" (AT = 3) and the second case is "unfair coin flipping" (AT != 3). 
  The formula are given in the link to the wiki.
*/

/*
#11500 - Vampires
  (http://www.questtosolve.com/browse.php?pid=11500)

Solved By:	wesley
Theory Difficulty:	medium
Coding Difficulty:	easy
Algorithms Used:	math

Solution Description: 	
This is a gambler's ruin problem. 
The idea behind gambler's ruin is that two people have a certain amount of money, 
and they bet a certain amount each game, with a fixed probability of winning. 
The game might go on infinitely, but there is a closed form for the probability that each wins.

(The proof isn't too hard, but it's not the kind of thing you'd want to derive during a contest. See Wikipedia for more info)

Let p be the probability that player 1 wins, and let q = 1-p be the probability that player 2 wins. 
Let n1 be the amount of money that player 1 starts with, and let n2 be the amount of money that player 2 starts with.

The chance that player 1 wins is:
  (1 - (q/p)^n1) / (1 - (q/p)^(n1 + n2))

And of course the chance that player 2 wins is 1 minus that.

Now, this assumes that each player wins/loses only 1 unit of money. 
In this problem though, the vampires may lose more than 1 health at once. 
So for this case, n1 = ceil(EV1/D), and n2 = ceil(EV2/D). 
That is, the number of hits it would take to kill a particular vampire. 
p of course is (AT / 6).

Note, however, that there is a special case when p = q = 1/2. 
The above formula is undefined for this case, and there is a much simpler closed form for a fair game. 
The probability of player 1 winning is:
  n1 / (n1 + n2)
*/

#include <cstdio>
#include <cmath>

int main()
{
	while (true) {
		double EV1, EV2;
		int AT, D;
		scanf("%lf %lf %d %d", &EV1, &EV2, &AT, &D);
		if (!AT)
			break;
		EV1 = ceil(EV1 / D), EV2 = ceil(EV2 / D);
		double p2; // probability that Vampire 2 loses the combat
		if (AT == 3)
			p2 = EV1 * 100.0 / (EV1 + EV2);
		else {
			double p = (6.0 - static_cast<double>(AT)) / static_cast<double>(AT);
			p2 = (1.0 - pow(p, EV1)) * 100.0 / (1.0 - pow(p, EV1 + EV2));
		}
		printf("%.1lf\n", p2);
	}
	return 0;
}

