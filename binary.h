#ifndef BINARY_H
#define BINARY_H

#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MEMORY_SIZE 33

char* padBinary(char* binary);
char* negateString(char* binString);
char* reverseString(char* binary);
int binToDecCompliment(char* binary);
int binToDec(char* binary);
char* addStrings(char* string1, char* string2);
char* subStrings(char* string1, char* string2);

#endif 
