#include "helpers.h"

int len(const char* str) {
	int i = 0;
	for(; str[i]; i++);
	return(i);
}

int cmpstr(const char* str1, const char* str2) {
	int n1 = len(str1), n2 = len(str2), i = 0;

	if(n1 != n2) {
		return 0;
	}

	for(; i < n1; i++) {
		if(str1[i] != str2[i]) {
			return 0;
		}
	}

	return 1;
}

void cpystring(char* dest, char* source) {
	int i = 0;
	for(; source[i]; i++) {
		dest[i] = source[i];
	}
	dest[i]='\0';
}

int expo(int base, int index) {
	if(index == 0) {
		return 1;
	}
	else {
		return(base*expo(base,index-1));
	}
}

void int_to_binstr(unsigned k, char* out, int width) {
    for (int i = width - 1; i >= 0; i--) {
        out[width - 1 - i] = ((k >> i) & 1) ? '1' : '0';
    }
    out[width] = '\0';
}
