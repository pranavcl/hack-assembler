#include "constants.h"

#ifndef RESOLVER_H
#define RESOLVER_H

typedef struct {
    char name[MAX_SYMBOL_LENGTH];
    int address;
} symbol;

extern int table_len;
extern symbol symbol_table[MAX_SYMBOL_TABLE_LENGTH];

void resolve_sym(FILE* input);

#endif