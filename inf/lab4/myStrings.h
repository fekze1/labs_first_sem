#ifndef MYSTRING_H
#define MYSTRING_H

#include <stddef.h>

int findLength(const char *string);

char* copyString(char* stringDest, const char* stringSrc);

int isDel(char string, char *del);

char *getWord(char *string, char *del);

void *copyMemory(void* destination, const void* source, int size);

char *duplicateString(const char *string);

char *spliceStrings(char * str1, const char * str2);

char *inputString(const char *prompt);

#endif
