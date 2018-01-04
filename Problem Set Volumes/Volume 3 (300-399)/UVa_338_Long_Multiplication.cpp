
/*
	UVa 338 - Long Multiplication

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_338_Long_Multiplication.cpp

	from ACM North Central Regional Programming Contest 1995-96, Problem 1
		(http://www.cs.nthu.edu.tw/~progcont/ACM/ProblemSetArchive/B_US_NorthCen/1995/index.html)
*/

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int nr_digits_max = 10, nr_chars_max = nr_digits_max * 2;

struct line {
	bool zero_;
	int start_, end_;
	char buff_[nr_chars_max + 1];
} x_line, y_line, horizontal_line, lines[nr_digits_max + 1];

void print_line(line& l, int min_start)
{
	memset(l.buff_ + min_start, ' ', l.start_ - min_start);
	puts(&l.buff_[min_start]);
}

void print_horizontal_line(int length, int min_start)
{
	horizontal_line.start_ = nr_chars_max - length;
	horizontal_line.end_ = nr_chars_max;
	memset(&horizontal_line.buff_[horizontal_line.start_], '-', length);
	print_line(horizontal_line, min_start);
}

int main()
{
	long long x, y;
	while (scanf("%lld %lld", &x, &y) == 2) {
		int min_start = nr_chars_max;
		// x
		x_line.zero_ = !x, x_line.start_ = x_line.end_ = nr_chars_max;
		do {
			x_line.buff_[--x_line.start_] = x % 10 + '0';
			x /= 10;
		} while (x);
#ifdef DEBUG
		puts(&x_line.buff_[x_line.start_]);
#endif
		min_start = min(min_start, x_line.start_);
		// y
		y_line.zero_ = !y, y_line.start_ = y_line.end_ = nr_chars_max;
		do {
			y_line.buff_[--y_line.start_] = y % 10 + '0';
			y /= 10;
		} while (y);
#ifdef DEBUG
		puts(&y_line.buff_[y_line.start_]);
#endif
		min_start = min(min_start, y_line.start_);

		if (x_line.zero_ || y_line.zero_) {
			print_line(x_line, min_start);
			print_line(y_line, min_start);
			print_horizontal_line(nr_chars_max - min_start, min_start);
			lines[0].start_ = nr_chars_max - 1, lines[0].end_ = nr_chars_max;
			lines[0].buff_[nr_chars_max - 1] = '0';
			print_line(lines[0], min_start);
			putchar('\n');
			continue;
		}

		int nr_lines = 0, nr_shift = 0;
		for (int i = y_line.end_ - 1; i >= y_line.start_; i--, nr_shift++) {
			line& l = lines[nr_lines];
			l.zero_ = true;
			l.start_ = l.end_ = nr_chars_max - nr_shift;
			l.buff_[l.end_] = '\0';
			int d = 0, dy = y_line.buff_[i] - '0';
			for (int j = x_line.end_ - 1; j >= x_line.start_; j--) {
				d += dy * (x_line.buff_[j] - '0');
				if ((l.buff_[--l.start_] = d % 10 + '0') != '0')
					l.zero_ = false;
				d /= 10;
			}
			while (d) {
				if ((l.buff_[--l.start_] = d % 10 + '0') != '0')
					l.zero_ = false;
				d /= 10;
			}
			if (!l.zero_) {
#ifdef DEBUG
				puts(&l.buff_[l.start_]);
#endif
				nr_lines++;
				min_start = min(min_start, l.start_);
			}
		}
		if (nr_lines > 1) {
			line& l = lines[nr_lines];
			l.start_ = l.end_ = nr_chars_max;
			int d = 0;
			for (int i = nr_chars_max - 1; i >= min_start; i--) {
				for (int j = 0; j < nr_lines; j++)
					if (!lines[j].zero_ && i >= lines[j].start_ && i < lines[j].end_)
						d += lines[j].buff_[i] - '0';
				l.buff_[--l.start_] = d % 10 + '0';
				d /= 10;
			}
			while (d) {
				l.buff_[--l.start_] = d % 10 + '0';
				d /= 10;
			}
#ifdef DEBUG
			puts(&l.buff_[l.start_]);
#endif
			min_start = min(min_start, l.start_);
			nr_lines++;
		}
		print_line(x_line, min_start);
		print_line(y_line, min_start);
		print_horizontal_line(max(x_line.end_ - x_line.start_, y_line.end_ - y_line.start_), min_start);
		if (nr_lines > 1) {
			for (int i = 0; i < nr_lines - 1; i++)
				if (!lines[i].zero_)
					print_line(lines[i], min_start);
			print_horizontal_line(nr_chars_max - min_start, min_start);
		}
		else {
			line& l = lines[0];
			memset(&l.buff_[l.end_], '0', nr_chars_max - l.end_);
		}
		print_line(lines[nr_lines - 1], min_start);
		putchar('\n');
	}
	return 0;
}

