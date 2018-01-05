
/*
	UVa 10400 - Game Show Math

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_10400_Game_Show_Math.cpp
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

const int p_max = 100, result_min = -32000, result_max = 32000;
char operators[p_max][result_max - result_min + 1];
int p, numbers[p_max], target;

bool game(int pi, int result)
{
	if (pi < p) {
		int r;
		if ((r = result + numbers[pi]) <= result_max && !operators[pi][r]) {
			operators[pi][r] = '+';
#ifdef DEBUG
			printf("[%d][%d]: %c\n", pi, r, operators[pi][r]);
#endif
			if (game(pi + 1, r))
				return true;
		}
		if ((r = result - numbers[pi]) >= result_min && !operators[pi][r]) {
			operators[pi][r] = '-';
#ifdef DEBUG
			printf("[%d][%d]: %c\n", pi, r, operators[pi][r]);
#endif
			if (game(pi + 1, result - numbers[pi]))
				return true;
		}
		if (abs(r = result * numbers[pi]) <= result_max && !operators[pi][r]) {
			operators[pi][r] = '*';
#ifdef DEBUG
			printf("[%d][%d]: %c\n", pi, r, operators[pi][r]);
#endif
			if (game(pi + 1, r))
				return true;
		}
		if (numbers[pi] && !(result % numbers[pi]) && !operators[pi][r = result / numbers[pi]]) {
			operators[pi][r] = '/';
#ifdef DEBUG
			printf("[%d][%d]: %c\n", pi, r, operators[pi][r]);
#endif
			if (game(pi + 1, r))
				return true;
		}
		return false;
	}
	else
		return result == target;
}

void print_expression(int pi, int result)
{
	if (!pi)
		printf("%d", numbers[pi]);
	else {
		int r = result;
		switch (operators[pi][r]) {
		case '+':
			r -= numbers[pi]; break;
		case '-':
			r += numbers[pi]; break;
		case '*':
			r /= numbers[pi]; break;
		case '/':
			r *= numbers[pi]; break;
		}
		print_expression(pi - 1, r);
		printf("%c%d", operators[pi][result], numbers[pi]);
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	while (n--) {
		scanf("%d", &p);
		for (int i = 0; i < p; i++)
			scanf("%d", &numbers[i]);
		scanf("%d", &target);
		if (p > 1) {
			memset(operators, 0, sizeof(operators));
			game(1, numbers[0]);
			if (operators[p - 1][target]) {
				print_expression(p - 1, target);
				printf("=%d\n", target);
			}
			else
				puts("NO EXPRESSION");
		}
		else {
			if (numbers[0] == target)
				printf("%d=%d\n", numbers[0], target);
			else
				puts("NO EXPRESSION");
		}
	}
	return 0;
}

