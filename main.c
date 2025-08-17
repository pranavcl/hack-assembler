#include<stdio.h>
#include "helpers.h"
#include "mappings.h"

#define MAX_LINE_LENGTH 100
#define MAX_FILENAME_LENGTH 256

FILE* input;
FILE* output;

void handle_instr(char* instr, int n) {
	int i;

	// A instructions
	if(instr[0] == '@') {
		// Get the numeric string of the instruction
		char nstr[10];
		for(i = 1; instr[i]; i++) {
			nstr[i-1] = instr[i];
		}
		nstr[i-1] = '\0';

		// TODO: Handle symbols here

		// Convert numeric string to int
		int nint = 0, length = len(nstr);
		for(i = 0; nstr[i]; i++) {
			nint += (nstr[i]-48) * expo(10,length-i-1);
		}

		char bin[17];
		int_to_binstr(nint, bin, 16);

		fprintf(output, "%s\n", bin);
		return;
	}

	// Labels
	else if(instr[0] == '(') {
		printf("Label\n");
		return;
	}

	// C instructions

	int has_dest = 0;
	int has_jmp = 0;

	char dest[7], cmp[7], jmp[7], outcmp[8], outdest[4], outjmp[4];
	int destc=0,cmpc=0,jmpc=0;

	for(i = 0; i < instr[i]; i++) {
		if(instr[i] == '=') {
			has_dest = 1;
			continue;
		}

		if(instr[i] == ';') {
			has_jmp = 1;
			continue;
		}

		if (!has_dest && !has_jmp) {
			dest[destc++] = instr[i];
		} else if (has_dest && !has_jmp) {
			cmp[cmpc++] = instr[i];
		} else if (has_jmp) {
			jmp[jmpc++] = instr[i];
		}
	}
	dest[destc] = cmp[cmpc] = jmp[jmpc] = '\0';

	if(!has_dest && !has_jmp) {
		fprintf(stderr, 
			"Error on line: %s\n(Neither DEST+CMP, DEST+JMP or DEST+CMP+JMP)\n",
			instr);
		return;
	} 
	
	if(!has_dest && has_jmp) {
		cpystring(cmp, dest);
		cpystring(dest, "");
	}

	fprintf(output, "111");
	fprintf(output, map_cmp(outcmp, cmp));
	fprintf(output, map_dest(outdest, dest));
	fprintf(output, map_jmp(outjmp, jmp));
	fprintf(output, "\n");
}

void parse() {
	char line[MAX_LINE_LENGTH];
	int i, j, n;
	char ch, ch1;

	while(1) {
		// Fill the line array with every character except whitespaces
		for(i=0; (ch = fgetc(input)) != '\n' && i < MAX_LINE_LENGTH; i++) {
			if(ch == EOF) {
				break;
			}
			if(ch != ' ' && ch != '\t') {
				line[i] = ch;
			}
		}
		line[i] = '\0';

		// Get rid of comments
		for(j=0; j < i; j++) {
			if(line[j] == '/' && line[j+1] == '/') {
				line[j] = '\0';
			}
		}

		// Handle the instruction
		n = len(line);
		if(n != 0) {
			handle_instr(line, n);
		}
		// If the file has ended, break out of the loop
		if(ch == EOF) {
			break;
		}
	}
}

int main(int argc, char** argv) {
	int i;

	if(argc < 2) {
		fprintf(stderr, "ERROR: No input file specified.\n");
		return(1);
	}

	input = fopen(argv[1], "r");

	if(input == NULL) {
		fprintf(stderr, "ERROR: Could not open input file.\n");
		return(1);
	}

	char output_fname[MAX_FILENAME_LENGTH];
	cpystring(output_fname, argv[1]);

	int changed_name = 0;

	for(i = 0; output_fname[i]; i++) {
		if(output_fname[i] == '.' && 
		output_fname[i+1] == 'a' && 
		output_fname[i+2] == 's' &&
		output_fname[i+3] == 'm') {
			output_fname[i+1] = 'h';
			output_fname[i+2] = 'a';
			output_fname[i+3] = 'c';
			output_fname[i+4] = 'k';
			output_fname[i+5] = '\0';
			changed_name = 1;
			break;
		}
	}

	if(!changed_name) {
		fprintf(stderr, "ERROR: File is not .asm\n");
		return(1);
	}

	output = fopen(output_fname, "w");

	parse();
	fclose(input);
	fclose(output);

	return(0);
}
