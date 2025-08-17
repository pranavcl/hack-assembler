#ifndef HELPERS_H
#define HELPERS_H

int len(const char* str);
void cpystring(char* str1, char* str2);
int cmpstr(const char* str1, const char* str2);
int expo(int base, int index);
void int_to_binstr(unsigned k, char* out, int width);

#endif