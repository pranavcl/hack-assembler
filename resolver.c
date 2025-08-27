#include<stdio.h>
#include "helpers.h"
#include "resolver.h"
#include "constants.h"

symbol symbol_table[MAX_SYMBOL_TABLE_LENGTH] = {
	{"R0", 0},
	{"R1", 1},
	{"R2", 2},
	{"R3", 3},
	{"R4", 4},
	{"R5", 5},
	{"R6", 6},
	{"R7", 7},
	{"R8", 8},
	{"R9", 9},
	{"R10", 10},
	{"R11", 11},
	{"R12", 12},
	{"R13", 13},
	{"R14", 14},
	{"R15", 15},
	{"SCREEN", 16384},
	{"KBD", 24576},
	{"SP", 0},
	{"LCL", 1},
	{"ARG", 2},
	{"THIS", 3},
	{"THAT", 4}
};

int pc, table_len=23;

void resolve_sym(FILE* input) {
	char line[MAX_LINE_LENGTH];
	int i, j, n;
	char ch;
	int labelflag=0;

	for(pc=0;ch!=EOF;) {
		cpystring(line, "");
		// Fill the line array with every character except whitespaces
		for(i=0; (ch = fgetc(input)) != '\n' && i < MAX_LINE_LENGTH;) {
			if(ch == EOF) {
				break;
			}
			if(i == 0 && ch == '(') {
				labelflag=1;
				continue;
			}
			if(ch != ' ' && ch != '\t' && ch != ')') {
				line[i++] = ch;
			}
		}
		line[i] = '\0';

		// Get rid of comments
		for(j=0; j < i; j++) {
			if(line[j] == '/' && line[j+1] == '/') {
				line[j] = '\0';
			}
		}

		n = len(line);

		if(n == 0) continue;

		if(labelflag) {
			symbol sym;
			cpystring(sym.name, line);
			sym.address = pc;
			symbol_table[table_len++] = sym;
			labelflag = 0;
			continue;
		}

		pc++;
	}
}
