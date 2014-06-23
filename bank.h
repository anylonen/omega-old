#ifndef BANK_H
#define BANK_H

#include "bank_account.h"

/* bank.c functions */

struct object* bank_create_card (int, int);
bank_account* bank_create_account (int, int, char*);
bank_account* bank_index_password (char*);
bank_account* bank_index_number (int);
int bank_random_account_number (void);
void bank_init(void);
void l_bank (void);

#endif
