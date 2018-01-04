
/*
	UVa 187 - Transaction Processing

	To build using Visual Studio 2012:
		cl -EHsc -O2 UVa_187_Transaction_Processing.cpp
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

const int nr_chars_max = 32, nr_accounts_max = 100, nr_transactions_max = 10;

struct account {
	int nr_;
	char name_[nr_chars_max];
} accounts[nr_accounts_max + 1];

struct transaction {
	int account_nr_;
	int amount_;
} transactions[nr_transactions_max + 1];

int compare_account(const void* i, const void* j)
{
	return reinterpret_cast<const account*>(i)->nr_ - reinterpret_cast<const account*>(j)->nr_;
}

int main()
{
	char s[nr_chars_max * 2];
	int nr_accounts = 0;
	while (true) {
		gets(s);
		strcpy(accounts[nr_accounts].name_, s + 3);
		s[3] = '\0';
		if (!(accounts[nr_accounts].nr_ = atoi(s)))
			break;
		nr_accounts++;
	}
	qsort(accounts, nr_accounts, sizeof(account), compare_account);

	int snr = -1, psnr = -1, nr_transactions = 0;
	while (true) {
		gets(s);
		transactions[nr_transactions].amount_ = atoi(s + 6);
		s[6] = '\0';
		transactions[nr_transactions].account_nr_ = atoi(s + 3);
		s[3] = '\0';
		if (!(snr = atoi(s)) || psnr != -1 && snr != psnr) {
			int balance = 0;
			for (int i = 0; i < nr_transactions; i++)
				balance += transactions[i].amount_;
			if (balance) {
				printf("*** Transaction %03d is out of balance ***\n", psnr);
				for (int i = 0; i < nr_transactions; i++) {
					account a;
					a.nr_ = transactions[i].account_nr_; a.name_[0] = '\0';
					account* pa = reinterpret_cast<account*>(bsearch(&a, accounts, nr_accounts, sizeof(account),
						compare_account));
					if (!pa)
						pa = &a;
					int dollar = abs(transactions[i].amount_ / 100), cent = abs(transactions[i].amount_) % 100;
					if (transactions[i].amount_ < 0) {
						if (dollar)
							printf("%3d %-30s %7d.%02d\n", pa->nr_, pa->name_, -dollar, cent);
						else
							printf("%3d %-30s      -0.%02d\n", pa->nr_, pa->name_, cent);
					}
					else
						printf("%3d %-30s %7d.%02d\n", pa->nr_, pa->name_, dollar, cent);
				}
				balance = abs(balance);
				printf("999 Out of Balance                 %7d.%02d\n\n", balance / 100, balance % 100);
			}
			if (!snr)
				break;
			else {
				transactions[0].account_nr_ = transactions[nr_transactions].account_nr_;
				transactions[0].amount_ = transactions[nr_transactions].amount_;
				nr_transactions = 0;
			}
		}
		nr_transactions++;
		psnr = snr;
	}
	return 0;
}

