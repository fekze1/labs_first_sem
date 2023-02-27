#include "myStrings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findLength(const char *string) {

    int length = 0;

    while (*string) {
        ++string, ++length;
    }

    return length;
}

char *spliceStrings(char * str1, const char * str2) {

    int strLen1, i;
    for (strLen1 = 0; str1[strLen1] != '\0'; ++strLen1);
        for (i = strLen1; str2[i - strLen1] != '\0'; ++i) {
             str1[i] = str2[i - strLen1];
        }
	str1[i] = '\0';

    return str1;

}

int isDel(char string, char *del){
    while(*del != '\0'){
        if(string == *del){
            return 1;
        }
        del++;
    }
    return 0;
}

char *getWord(char *string, char *del) {
    static char *prev_str; 
    
    if(!string) string = prev_str;
    if(!string) return NULL;
    
    while(1){
    
        if(isDel(*string, del)){
            string++;
            continue;
        }
        
        if(*string == '\0') return NULL;
        
        break;
    }
    
    char *result = string;
    
    while(1){
    
        if(*string == '\0'){
            prev_str = string;
            return result;
        }
        if(isDel(*string, del)){
            *string = '\0';
            prev_str = string + 1;
            return result;
        }
        
        string++;
    }
}

void *copyMemory(void* destination, const void* source, int size){
    char *dest_copy = (char *)destination;
    
    const char *src_copy =( const char*)source;
    
    if(dest_copy && src_copy){
        while(size){
            *(dest_copy++)= *(src_copy++);
            --size;
        }
    }
    
    return destination;
}

char *duplicateString(const char *string){
  int len = findLength(string) + 1;
  void *new = malloc(len);

  if (!new) return NULL;

  return (char *)copyMemory(new, string, len);
}

char *inputString(const char *prompt) {
	printf("%s", prompt);
	char *string = (char *)malloc(1);
	char buffer[81];
	int n, str_length = 0;
	*string = '\0';
	
	do{
		n = scanf("%80[^\n]", buffer);
		
		if(n < 0){

		free(string);
		string = NULL;
		continue;

		}

		if(n == 0){

			scanf("%*c");

		}else {

			str_length += findLength(buffer);
			string = (char *)realloc(string, str_length + 1);
			string = spliceStrings(string, buffer);

		}	
	}while(n > 0);
	
	return string;
}
