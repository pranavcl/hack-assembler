#include "helpers.h"
#include "mappings.h"

char* map_cmp(char mapping[8], char* cmp) {
	// When a = 0

	if(cmpstr(cmp, "0")) {
		cpystring(mapping, "0101010");
	} else if(cmpstr(cmp, "1")) {
		cpystring(mapping, "0111111");
	} else if(cmpstr(cmp, "-1")) {
		cpystring(mapping, "0111010");
	} else if(cmpstr(cmp, "D")) {
		cpystring(mapping, "0001100");
	} else if(cmpstr(cmp, "A")) {
		cpystring(mapping, "0110000");
	} else if(cmpstr(cmp, "!D")) {
		cpystring(mapping, "0001101");
	} else if(cmpstr(cmp, "!A")) {
		cpystring(mapping, "0110001");
	} else if(cmpstr(cmp, "-D")) {
		cpystring(mapping, "0001111");
	} else if(cmpstr(cmp, "-A")) {
		cpystring(mapping, "0110011");
	} else if(cmpstr(cmp, "D+1")) {
		cpystring(mapping, "0011111");
	} else if(cmpstr(cmp, "A+1")) {
		cpystring(mapping, "0110111");
	} else if(cmpstr(cmp, "D-1")) {
		cpystring(mapping, "0001110");
	} else if(cmpstr(cmp, "A-1")) {
		cpystring(mapping, "0110010");
	} else if(cmpstr(cmp, "D+A")) {
		cpystring(mapping, "0000010");
	} else if(cmpstr(cmp, "D-A")) {
		cpystring(mapping, "0010011");
	} else if(cmpstr(cmp, "A-D")) {
		cpystring(mapping, "0000111");
	} else if(cmpstr(cmp, "D&A")) {
		cpystring(mapping, "0000000");
	} else if(cmpstr(cmp, "D|A")) {
		cpystring(mapping, "0010101");
	}

	// When a = 1

	else if(cmpstr(cmp, "M")) {
		cpystring(mapping, "1110000");
	} else if(cmpstr(cmp, "!M")) {
		cpystring(mapping, "1110001");
	} else if(cmpstr(cmp, "-M")) {
		cpystring(mapping, "1110011");
	} else if(cmpstr(cmp, "M+1")) {
		cpystring(mapping, "1110111");
	} else if(cmpstr(cmp, "M-1")) {
		cpystring(mapping, "1110010");
	} else if(cmpstr(cmp, "D+M")) {
		cpystring(mapping, "1000010");
	} else if(cmpstr(cmp, "D-M")) {
		cpystring(mapping, "1010011");
	} else if(cmpstr(cmp, "M-D")) {
		cpystring(mapping, "1000111");
	} else if(cmpstr(cmp, "D&M")) {
		cpystring(mapping, "1000000");
	} else if(cmpstr(cmp, "D|M")) {
		cpystring(mapping, "1010101");
	}

	return mapping;
}

char* map_dest(char mapping[4], char* dest) {
	int i;
	mapping[0] = mapping[1] = mapping[2] = '0';
	for(i = 0; dest[i]; i++) {
		if(dest[i] == 'M') {
			mapping[2] = '1';
		} else if(dest[i] == 'D') {
			mapping[1] = '1';
		} else if(dest[i] == 'A') {
			mapping[0] = '1';
		}
	}
	mapping[3] = '\0';
	return mapping;
}

char* map_jmp(char mapping[4], char* jmp) {
	if(cmpstr(jmp, "null") || cmpstr(jmp, "")) {
		cpystring(mapping, "000");
	} else if(cmpstr(jmp, "JGT")) {
		cpystring(mapping, "001");
	} else if(cmpstr(jmp, "JEQ")) {
		cpystring(mapping, "010");
	} else if(cmpstr(jmp, "JGE")) {
		cpystring(mapping, "011");
	} else if(cmpstr(jmp, "JLT")) {
		cpystring(mapping, "100");
	} else if(cmpstr(jmp, "JNE")) {
		cpystring(mapping, "101");
	} else if(cmpstr(jmp, "JLE")) {
		cpystring(mapping, "110");
	} else if(cmpstr(jmp, "JMP")) {
		cpystring(mapping, "111");
	}
	return mapping;
}
