#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

struct bank_account
{
    short player;
    long balance;
    long number;
    char* password;
    struct bank_account* next_account;
};
typedef struct bank_account bank_account;

#endif // BANK_ACCOUNT_H
